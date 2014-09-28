#include "AssetsUpdateMgr.h"
#include "Base64.h"
#include "zlib.h"

#include <pthread.h>
#include <sstream>
#include <fstream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "gnproto.h"
#include "gnsecure.h"
#include <direct.h>
#else
#include "protocol.h"
#include "security.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <iconv.h>
#endif

namespace 
{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	static const int CHUNK = 16384;
	static const int VERSION = (1 << 24) | (1 << 16) | (1 << 8) | 1 ;

	static string& _replace_all(string& str,const string& old_value,const string& new_value)
	{
		while(true)
		{
			string::size_type pos(0);
			if((pos=str.find(old_value))!=string::npos)
				str.replace(pos,old_value.length(),new_value);
			else
				break;
		}

		return str;
	}

	static bool _copyfile(const char* src,const char* des)
	{
		if(!src || !des) return false;

		unsigned long len=0;
		FILE* file = fopen(src,"rb");
		if(!file)
			return false;
		fseek(file,0,SEEK_END);

		len = ftell(file);
		if(len<1) 
		{
			fclose(file);
			return false;
		}
		fseek(file,0,SEEK_SET);

		unsigned char* buf = new unsigned char[len];

		fread(buf,sizeof(unsigned char),len,file);

		fclose(file);

		FILE* fp = fopen(des,"wb");
		fwrite(buf,len,1,fp);
		fclose(fp);
		delete [] buf;
		return true;
	}

	static bool _calc_file_md5(const char* szFile, unsigned char md5[16])
	{
		FILE * file = fopen(szFile,"rb");
		if (!file)
			return false;

		fseek(file,0,SEEK_END);
		int len = (int)ftell(file);
		if (len < 1)
		{
			fclose(file);
			return false;
		}

		fseek(file,0,SEEK_SET);

		unsigned char * buf = new unsigned char[len];
		
		fread(buf,sizeof(unsigned char),len,file);
		fclose(file);

		memset(md5,0,16);

		GNET::Octets input(buf,len);
		GNET::Octets output = GNET::MD5Hash::Digest(input);

        len = output.size() < 16 ? output.size() : 16;
		memcpy(md5,output.begin(), len);

		delete [] buf;

		return true;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static wchar_t * _ansi_to_unicode(const char * str, int & len)
	{
		int textlen=0;
		wchar_t * result=NULL;
		textlen = MultiByteToWideChar(CP_ACP,0,str,-1,NULL,0);
		result = new wchar_t[textlen+1];
		memset(result,0,sizeof(wchar_t)*(textlen+1));
		MultiByteToWideChar(CP_ACP,0,str,-1,result,textlen);
		len=textlen;
		return result;
	}

	static char * _unicode_to_utf8(const wchar_t * str, int & len)
	{
		int textlen=0;
		char * result=NULL;
		textlen = WideCharToMultiByte(CP_UTF8,0,str,-1,NULL,0,NULL,NULL);
		result = new char[textlen+1];
		memset(result,0,sizeof(char)*(textlen+1));
		WideCharToMultiByte(CP_UTF8,0,str,-1,result,textlen,NULL,NULL);
		len=textlen;
		return result;
	}
#endif
    
	static int _inf(FILE *source, FILE *dest)
	{
		int ret;
		unsigned have;
		z_stream strm;
		unsigned char in[CHUNK];
		unsigned char out[CHUNK];

		/* allocate inflate state */
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = inflateInit(&strm);
		if (ret != Z_OK)
			return ret;

		/* decompress until deflate stream ends or end of file */
		do {
			strm.avail_in = fread(in, 1, CHUNK, source);
			if (ferror(source)) {
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
			if (strm.avail_in == 0)
				break;
			strm.next_in = in;

			/* run inflate() on input until output buffer not full */
			do {
				strm.avail_out = CHUNK;
				strm.next_out = out;
				ret = inflate(&strm, Z_NO_FLUSH);
				assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
				switch (ret) {
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;     /* and fall through */
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return ret;
				}
				have = CHUNK - strm.avail_out;
				if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
					(void)inflateEnd(&strm);
					return Z_ERRNO;
				}
			} while (strm.avail_out == 0);

			/* done when inflate() says it's done */
		} while (ret != Z_STREAM_END);

		/* clean up and return */
		(void)inflateEnd(&strm);
		return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
	}

	static size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream) 
	{
		int r;
		int len = 0;
		/* _snscanf() is Win32 specific */
		// r = _snscanf(ptr, size * nmemb, "Content-Length: %ld\n", &len);
		char* p = (char*)ptr;
		r = sscanf(p, "Content-Length: %d\n", &len);
		if (r) /* Microsoft: we don't read the specs */
			*((int *) stream) = len;
		return size * nmemb;
	}

	static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
	{
		FILE *fp = (FILE*)userdata;
		size_t written = fwrite(ptr, size, nmemb, fp);
		return written;
	}

	static int progressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
	{
		//   total_downloaded = (int)(nowDownloaded) + pre_downloaded;

		CCLOG("downloading... %d %d", (int)nowDownloaded, (int)totalToDownload);

		return 0;
	}

	static void* glb_downLoad(void* pArg)
	{
		if(!pArg)
			return NULL;

		pthread_mutex_lock(&mutex);
		pthread_detach(pthread_self());

		download_param * pdp = (download_param*)pArg; 
		AssetsUpdateManager::GetInstance()->downLoad(pdp);

		pthread_mutex_unlock(&mutex);

		if (pdp->download_finish_func)
			pdp->download_finish_func(pArg);

		if (pdp->script_download_finish_func)
			pdp->script_download_finish_func->execute();

		return NULL;
	}
}

std::string AssetsUpdateManager::GetDocumentPath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return CCFileUtils::sharedFileUtils()->getWritablePath();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    std::string documents_path = CCFileUtils::sharedFileUtils()->getWritablePath() + "../Documents/";
    MakeDir(documents_path.c_str(),documents_path.size());
    return documents_path;
#endif
}

std::string AssetsUpdateManager::GetTmpPath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return CCFileUtils::sharedFileUtils()->getWritablePath() + "../tmp/";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    std::string tmp_path = CCFileUtils::sharedFileUtils()->getWritablePath() + "../tmp/";
    MakeDir(tmp_path.c_str(),tmp_path.size());
    return tmp_path;
#endif
}

std::string AssetsUpdateManager::GetCachePath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return CCFileUtils::sharedFileUtils()->getWritablePath() + "../Library/Caches/";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    std::string caches_path = CCFileUtils::sharedFileUtils()->getWritablePath() + "../Library/Caches/";
    MakeDir(caches_path.c_str(),caches_path.size());
    return caches_path;
#endif
}

void AssetsUpdateManager::downLoad(download_param * pdp)
{
	if (!pdp) return;
	download_param & dp = *((download_param*)pdp); 
	if(dp.src.empty() || dp.des.empty() || dp.filename.empty() || dp.timeout < 1 || 
		dp.trytime < 1 || dp.ret || !dp.download_finish_func) 
		return ;

	std::string filename = dp.filename;
    //CCLOG("download file %s", filename.c_str());

	if (dp.use_base64)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int len = 0;
		wchar_t * p = _ansi_to_unicode(filename.c_str(),len);
		char * pRet = _unicode_to_utf8(p,len);
		delete [] p;
	
		len = len*4+1;
		char * des = new char[len];
		memset(des,0,sizeof(char)*len);
#else
        int len = (int)filename.size();
        char * pRet = new char[len+1];
        memcpy(pRet,filename.c_str(), len);
        pRet[len] = '\0';
        len = 2*len;
        char * des = new char[len];
        memset(des,0,sizeof(char)*len);
        //CCLOG("filename pRet= %s", pRet);
#endif
		Base64Code base64;
		base64.Encode(pRet,des);
		delete [] pRet;
        //CCLOG("filename des= %s", des);

		filename = des;
		filename += ".enc";

		delete [] des;
	}

	std::string urlpath = dp.src + dp.sub_path + filename;
	std::string destpath = dp.des + dp.sub_path + dp.filename;	//使用原来的名字保存，这时候里边是压缩过的

	const char* remotepath = urlpath.c_str();
	const char* localpath = destpath.c_str();
	int timeout = dp.timeout;
	int trytime = dp.trytime;

	string resumefile = localpath;
	resumefile = resumefile + ".resume";

	do {
	CCLOG("begin download file %s", localpath);
	try{
		FILE *f;
		curl_off_t local_file_len = -1;
		//  long filesize =0;
		CURLcode r = CURLE_GOT_NOTHING;      

		MakeDir(localpath,strlen(localpath));

		//do {                        
		struct stat file_info, resuem_info;
		int use_resume = 0;

		if(dp.use_resume && (stat(localpath, &file_info) == 0) && (stat(resumefile.c_str(), &resuem_info) == 0 ))
		{
			local_file_len =  file_info.st_size;
			use_resume  = 1;
		}

		FILE* ferr = NULL;

		if(use_resume==1)
		{
			f = fopen(localpath, "ab+");
			ferr = fopen(resumefile.c_str(),"a+");
		}
		else
		{                
			f = fopen(localpath,"wb");
			ferr = fopen(resumefile.c_str(),"wb");
		}            

		if (f == NULL || ferr == NULL)
		{
			//    perror(NULL);
			throw 2;
		}
		int filesize;            

		CURL* curlhandle = curl_easy_init();

		//curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);

		//	curl_easy_setopt(curlhandle, CURLOPT_FOLLOWLOCATION,1L); // nginx response code 302
		//	curl_easy_setopt(curlhandle, CURLOPT_MAXREDIRS,3);

		curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);
		curl_easy_setopt(curlhandle, CURLOPT_TIMEOUT, timeout);
		curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
		curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &filesize); // cannot remove this line
		curl_easy_setopt(curlhandle, CURLOPT_RESUME_FROM_LARGE, use_resume?local_file_len:0);
		curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, f);
		curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, downLoadPackage);
		//curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
		//curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);
		curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, false);
		//    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);
		//    curl_easy_setopt(curlhandle, CURLOPT_STDERR, ferr);
		curl_easy_setopt(curlhandle, CURLOPT_PROGRESSFUNCTION, progressFunc);

		//   curl_easy_setopt(curlhandle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

		r = curl_easy_perform(curlhandle);

		int retcode = 0;
		CURLcode retResponse = curl_easy_getinfo(curlhandle,CURLINFO_RESPONSE_CODE,&retcode);

		fclose(f);            
		fclose(ferr);

		/* bool bRemove = true;
		if( (retResponse==CURLE_OK) && (retcode == 302 || retcode == 404))
		{
		remove(resumefile.c_str());
		bRemove = false;
		}*/
		curl_easy_cleanup(curlhandle);

		if((retResponse==CURLE_OK)&& ((retcode !=200) &&(retcode !=206) ))
		{
            CCLOG("retcode %d", retcode);
			throw 4;
		}

		if(r == CURLE_OPERATION_TIMEDOUT || r == CURLE_ABORTED_BY_CALLBACK)
		{                
			continue;
		}

		if (r != CURLE_OK)
		{                
			throw 3;
		}            

		remove(resumefile.c_str());
		dp.ret = true;

		//} while (!dp.ret && --trytime > 0);

		//CCLOG("succeed download file %s", localpath);
	}
	catch(int ret)
	{
		CCLOG("try download file %s failed. ret=%d", localpath, ret);
		//remove(resumefile.c_str());
		dp.ret = false;
	}	

	}while(!dp.ret && --trytime > 0);

	if (dp.ret)
		CCLOG("succeed download file %s", localpath);
	else
		CCLOG("download file %s failed.", localpath);
}

void AssetsUpdateManager::newThreadDownLoad(download_param * pdp)
{
	if (!pdp)
		return;

	pthread_t ntid;
	pthread_create(&ntid,NULL,glb_downLoad,pdp);
}

void Finish(void * p)
{
	AssetsUpdateManager::GetInstance()->onFileDownLoadFinish(p);
}

download_param* p_dp = NULL;

bool AssetsUpdateManager::CheckUpdate(update_param * pup)
{
	update_param & up = *((update_param*)pup);
	p_dp = download_param::create();
	p_dp->retain();
	download_param & g_dp = *p_dp;
	switch(m_stat)
	{
	case AUMS_INIT:
		{
			//先做一下初始化和创建路径
			if (up.resource_path.size() > 0 && up.resource_path[up.resource_path.size() - 1] != '/')
			{
				up.resource_path.append("/");
			}
			if (up.download_path.size() > 0 && up.download_path[up.download_path.size() - 1] != '/')
			{
				up.download_path.append("/");
			}
			if (up.src.size() > 0 && up.src[up.src.size() - 1] != '/')
			{
				up.src.append("/");
			}
			MakeDir(up.resource_path.c_str(),up.resource_path.size());

			//更新md5文件
			g_dp.des = up.download_path;
			g_dp.sub_path = "";
			g_dp.filename = up.md5_file;
			g_dp.src = up.src;
			g_dp.timeout = up.timeout;
			g_dp.trytime = up.trytime;
			g_dp.download_finish_func = &Finish;
			g_dp.use_base64 = true;
			g_dp.use_resume = false;	//md5 文件不使用断点续传，否则跨越2个版本更新可能出问题
			g_dp.ret = false;

			newThreadDownLoad(&g_dp);
			m_stat = AUMS_UPDATE_MD5FILE;
		}
		break;
	case AUMS_UPDATE_MD5FILE:
		break;
	case AUMS_UPDATE_MD5FILE_OK:
		{
			if (CheckMD5(pup))
			{
				//有文件需要更新
				int n = up.des[0].find_last_of("/");
				std::string sub_path = n >= 0 ? up.des[0].substr(0,n+1) : "";
				std::string filename = n >= 0 ? up.des[0].substr(n+1,up.des[0].size()-n-1) : up.des[0];
				
				g_dp.des = up.download_path;
				g_dp.sub_path = sub_path;
				g_dp.filename = filename;
				g_dp.src = up.src;
				g_dp.timeout = up.timeout;
				g_dp.trytime = up.trytime;
				g_dp.download_finish_func = &Finish;
				g_dp.use_base64 = true;
				g_dp.use_resume = true;
				g_dp.ret = false;

				newThreadDownLoad(&g_dp);

				m_stat = AUMS_UPDATE_ONE_FILE;
			}
			else
			{
				//所有文件都不需要更新
				m_stat = AUMS_UPDATE_OK;
			}
		}
		break;
	case AUMS_UPDATE_ONE_FILE:
		break;
	case AUMS_UPDATE_ONE_FILE_OK:
		{
			//把下载完的压缩文件解压缩并拷贝到资源目录
			std::string from_path = up.download_path + up.des[0];
			std::string to_path = up.resource_path + up.des[0];
			std::string uncompress_path = from_path + ".unc";
			UnCompressFile(from_path,uncompress_path);
			MakeDir(to_path.c_str(),to_path.size());
			_copyfile(uncompress_path.c_str(),to_path.c_str());

			//从待更新的列表里删除更新完的文件
			std::vector<std::string>::iterator it = up.des.begin();
			up.des.erase(it);

			//看看是不是还需要继续更新
			if (up.des.empty())
			{
				m_stat = AUMS_UPDATE_OK;
			}
			else
			{
				//还有文件需要更新，继续更新
				int n = up.des[0].find_last_of("/");
				std::string sub_path = n >= 0 ? up.des[0].substr(0,n+1) : "";
				std::string filename = n >= 0 ? up.des[0].substr(n+1,up.des[0].size()-n-1) : up.des[0];

				g_dp.des = up.download_path;
				g_dp.filename = filename;
				g_dp.sub_path = sub_path;
				g_dp.src = up.src;
				g_dp.timeout = up.timeout;
				g_dp.trytime = up.trytime;
				g_dp.download_finish_func = &Finish;
				g_dp.use_base64 = true;
				g_dp.use_resume = true;
				g_dp.ret = false;

				newThreadDownLoad(&g_dp);

				m_stat = AUMS_UPDATE_ONE_FILE;
			}
		}
		break;
	case AUMS_UPDATE_OK:
		{
			if (!up.ret)
			{
				//copyFiles(up.download_path,up.resource_path);
				deleteDir(up.download_path);
				p_dp->release();
				p_dp = NULL;
				up.ret = true;
			}
		}
		return true;	//更新成功结束
	case AUMS_UPDATE_FAILED:
		{
			p_dp->release();
			p_dp = NULL;
			//先把更新完的那些文件全拷贝过去吧，resume文件也过去了，下次更新的时候删除
			//copyFiles(up.download_path,up.resource_path);
		}
		return true;	//更新失败结束
	default:
		break;
	}

	return false;
}

void AssetsUpdateManager::onFileDownLoadFinish(void * p)
{
	download_param * pdp = (download_param*)p; 
	switch(m_stat)
	{
	case AUMS_UPDATE_MD5FILE:
		{
			if (pdp->ret)
			{
				m_stat = AUMS_UPDATE_MD5FILE_OK;
			}
			else
			{
				m_stat = AUMS_UPDATE_FAILED;
			}
		}
		break;
	case AUMS_UPDATE_ONE_FILE:
		{
			if (pdp->ret)
			{
				m_stat = AUMS_UPDATE_ONE_FILE_OK;
			}
			else
			{
				m_stat = AUMS_UPDATE_FAILED;
			}
		}
		break;
	default:
		break;
	}
}

//判断是否有文件需要更新
bool AssetsUpdateManager::CheckMD5(update_param * pup)
{
	update_param & up = *((update_param*)pup); 

	//先生成本地资源的md5列表
	map<string,string> localMD5;
	if(!generateLocalMd5List(up.resource_path,localMD5,up.resource_path))
	{
		CCLOG("fail to generate md5 file for local resource");
		return false;
	}
	//和服务器取下来的新的md5列表做比对
	std::string md5_file = up.download_path + up.md5_file;
	map<string,string> mapSevMD5;
	ifstream md5_sev(md5_file.c_str());
	int version = 0;
	md5_sev >> version;
	if (version != VERSION)
	{
		CCLOG("version wrong = %d.",version);
		return false;
	}
	if(!md5_sev.is_open())
	{
		CCLOG("fail to open local md5 file");
		return false;
	}
	else
	{
		string filepath,md5string;
		while (!md5_sev.eof())
		{
			md5_sev>>filepath;
			md5_sev>>md5string;
			if(!md5_sev.good())
				break;

			mapSevMD5.insert(map<string,string>::value_type(filepath,md5string));
		}
		md5_sev.close();
	}

	map<string,string>::iterator itr = localMD5.begin();

	for(;itr!=localMD5.end();++itr)
	{
		string key = itr->first;
		string md5_value = itr->second;
		if(mapSevMD5.find(key)==mapSevMD5.end())
		{
			//TODO delete file, such as .resume
		}
	}

	for(itr=mapSevMD5.begin();itr!=mapSevMD5.end();++itr)
	{
		string key = itr->first;
		string md5_value = itr->second;
		if(localMD5.find(key)==localMD5.end())
		{
			up.des.push_back(key);
		}
		else
		{
			if (md5_value != localMD5[key])
			{
				up.des.push_back(key);
			}
		}
	}

	if (!up.des.empty())
		return true;
	
	return false;	//没有文件需要更新
}

bool AssetsUpdateManager::UnCompressFile(const std::string & src, const std::string & des)
{
	FILE * fpSrc = fopen(src.c_str(),"rb");
	FILE * fpDes = fopen(des.c_str(),"wb");
	
	int bRes = 0;
	if (fpSrc && fpDes)
		bRes = _inf(fpSrc,fpDes);

	fclose(fpSrc);
	fclose(fpDes);

	return true;
}

bool AssetsUpdateManager::MakeDir(const char* dir,int r)
{
	r--;
	while(r>0&&dir[r]!='/'&&dir[r]!='\\')
		r--;
	if(r==0)
		return false;
	MakeDir(dir,r);
	char t[512] = {0};
	strcpy(t,dir);
	t[r]='\0';
	//_mkdir(t);
	return createDir(t);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

bool AssetsUpdateManager::IsExistDir(const char* szDir)
{
	return -1 != _access(szDir,0);
}

bool AssetsUpdateManager::createDir(const char *path)
{
	if(_access(path, 0)!=-1) return true;

	BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
}

bool AssetsUpdateManager::copyFiles(std::string src,std::string des)
{
	if (src.size() > 0 && src[src.size() - 1] != '/')
	{
		src.append("/");
	}
	if (des.size() > 0 && des[des.size() - 1] != '/')
	{
		des.append("/");
	}

	string szDir = src;
	szDir = szDir + "*.*";
	int handle;
	struct _finddata_t fileinfo;

	handle = _findfirst(szDir.c_str(),&fileinfo);
	if(-1==handle) return false;
	while(!_findnext(handle,&fileinfo))
	{
		if(strcmp(fileinfo.name,".")==0 || strcmp(fileinfo.name,"..")==0)
			continue;

		string tempSrc = src + fileinfo.name;
		_replace_all(tempSrc,"\\","/");

		string tempDes = tempSrc;
		int pos = tempDes.find(src,0);
		tempDes.replace(pos,src.size(),des.c_str());

		if(fileinfo.attrib==_A_SUBDIR)
		{
			_replace_all(tempSrc,"\\","/");

			createDir(tempDes.c_str());
			copyFiles(tempSrc,tempDes);
		}
		else
		{
			_copyfile(tempSrc.c_str(),tempDes.c_str());
		}
	}
	_findclose(handle);

	return true;
}

bool AssetsUpdateManager::deleteDir(const std::string& src)
{
	string src_backup = src;
	if (src_backup.size() > 0 && src_backup[src_backup.size() - 1] != '/')
	{
		src_backup.append("/");
	}

	string szDir = src_backup;
	szDir = szDir + "*.*";
	int handle;
	struct _finddata_t fileinfo;

	handle = _findfirst(szDir.c_str(),&fileinfo);
	if(-1==handle) return false;
	while(!_findnext(handle,&fileinfo))
	{
		if(strcmp(fileinfo.name,".")==0 || strcmp(fileinfo.name,"..")==0)
			continue;

		string tempSrc = src_backup + fileinfo.name;
		_replace_all(tempSrc,"\\","/");


		if(fileinfo.attrib==_A_SUBDIR)
		{
			_replace_all(tempSrc,"\\","/");

			deleteDir(tempSrc);

			if(IsExistDir(tempSrc.c_str()))
				_rmdir(tempSrc.c_str());
		}
		else
		{
			string tempSrc = src_backup + fileinfo.name;
			remove(tempSrc.c_str());			
		}
	}
	if (src_backup.size() > 0 && src_backup[src_backup.size() - 1] == '/')
	{
		src_backup.erase(src_backup.size()-1,1);
	}
	_findclose(handle);

	return true;
}

bool AssetsUpdateManager::generateLocalMd5List(const std::string & root,std::map<std::string,std::string>& md5map,const std::string& baseDir)
{
	std::string tmp_root1 = root;
	std::string tmp_root2 = root + "\\*.*";

	int handle;
	struct _finddata_t fileinfo;

	handle = _findfirst(tmp_root2.c_str(),&fileinfo);
	if(-1==handle) return false;
	while(!_findnext(handle,&fileinfo))
	{
		if(strcmp(fileinfo.name,".")==0 || strcmp(fileinfo.name,"..")==0)
			continue;

		if (tmp_root1.size() > 0 && tmp_root1[tmp_root1.size() - 1] != '/')
		{
			tmp_root1.append("/");
		}

		string tempSrc = tmp_root1 + fileinfo.name;
		if(fileinfo.attrib==_A_SUBDIR)
		{
			generateLocalMd5List(tempSrc,md5map,baseDir);
		}
		else
		{
			unsigned char md5[16]={0};
			_calc_file_md5(tempSrc.c_str(),md5);

			string relativePath = tempSrc.substr(baseDir.length());
			char str[128] = {0};
			sprintf(str,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",md5[0], md5[1], md5[2], md5[3],
				md5[4], md5[5], md5[6], md5[7], md5[8], md5[9], md5[10], md5[11], md5[12], md5[13], md5[14], md5[15]);

			md5map[relativePath] = str;			
		}
	}
	_findclose(handle);

	return true;
}

#else

bool AssetsUpdateManager::IsExistDir(const char* szDir)
{
	struct stat dirStat;
	if(stat(szDir,&dirStat)==0 && S_ISDIR(dirStat.st_mode))
		return true;
	return false;
}

bool AssetsUpdateManager::createDir(const char *path)
{    
	if(access(path, 0)!=-1) return true;

	mode_t processMask = umask(0);
	int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}

	return true;
}

bool AssetsUpdateManager::copyFiles(std::string src,std::string des)
{
	if (src.size() > 0 && src[src.size() - 1] != '/')
	{
		src.append("/");
	}
	if (des.size() > 0 && des[des.size() - 1] != '/')
	{
		des.append("/");
	}

	string szDir = src;
	DIR* dp;
	struct dirent* entry=NULL;
	struct stat statbuf;
	if((dp=opendir(src.c_str()))==NULL)
		return false;
	while ((entry=readdir(dp))!=NULL) {
		if((strcmp(".",entry->d_name))==0|| strcmp("..", entry->d_name)==0)
			continue;

		string tempSrc = src + entry->d_name;
		_replace_all(tempSrc,"\\","/");

		lstat(tempSrc.c_str(),&statbuf);      


		string tempDes = tempSrc;
		int pos = tempDes.find(src,0);
		tempDes.replace(pos,src.size(),des.c_str());

		if(S_ISDIR(statbuf.st_mode))
		{
			createDir(tempDes.c_str());
			copyFiles(tempSrc,tempDes);
		}
		else
		{
			_copyfile(tempSrc.c_str(),tempDes.c_str());
		}
	}
	closedir(dp);

	return true;
}

bool AssetsUpdateManager::deleteDir(const std::string& src)
{
	string src_back = src;
	if (src.size() > 0 && src[src.size() - 1] != '/')
	{
		src_back.append("/");
	}
	DIR* dp=NULL;
	dirent* entry=NULL;
	struct stat statbuf;
	if((dp=opendir(src_back.c_str()))==NULL)
		return false;

	while ((entry=readdir(dp))!=NULL) {
		if (strcmp(".", entry->d_name)==0||strcmp("..", entry->d_name)==0)
			continue;

		string tempSrc = src_back + entry->d_name;
		lstat(tempSrc.c_str(), &statbuf);

		if (S_ISDIR(statbuf.st_mode)) {            
			deleteDir(tempSrc);
			rmdir(tempSrc.c_str());
		}
		else
		{			
			remove(tempSrc.c_str());
		}
	}

	closedir(dp);    

	return true;
}

bool AssetsUpdateManager::generateLocalMd5List(const std::string& root,std::map<std::string,std::string>& md5map, const string& baseDir)
{
	std::string tmp_root1 = root;
	std::string tmp_root2 = root;
	if (tmp_root2.size() > 0 && tmp_root2[tmp_root2.size() - 1] != '/')
	{
		tmp_root2.append("/");
	}

	DIR *dp=NULL;
	struct dirent* entry;
	struct stat statbuf;
	if((dp=opendir(tmp_root2.c_str()))==NULL)
		return false;

	while ((entry = readdir(dp))!=NULL) {
		if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
			continue;

		if (tmp_root1.size() > 0 && tmp_root1[tmp_root1.size() - 1] != '/')
		{
			tmp_root1.append("/");
		}

		string tempSrc = tmp_root1 + entry->d_name;

		lstat(tempSrc.c_str(),&statbuf);

		//  
		if(S_ISDIR(statbuf.st_mode))
		{            
			generateLocalMd5List(tempSrc, md5map,baseDir);
		}
		else
		{
			unsigned char md5[16]={0};
			_calc_file_md5(tempSrc.c_str(),md5);

			string relativePath = tempSrc.substr(baseDir.length());

			char str[128] = {0};
			sprintf(str,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",md5[0], md5[1], md5[2], md5[3],
				md5[4], md5[5], md5[6], md5[7], md5[8], md5[9], md5[10], md5[11], md5[12], md5[13], md5[14], md5[15]);

			md5map[relativePath] = str;
		}
	}

	closedir(dp);

	return true;
}

#endif