#include "PackTool.h"
#include "zlib.h"
#include "gnoctets.h"
#include "gnsecure.h"
#include "Base64.h"

#include <io.h>
#include <direct.h>
#include <fstream>

#define USE_BASE64

namespace 
{
	static const int VERSION = (1 << 24) | (1 << 16) | (1 << 8) | 1;
	static const int CHUNK = 16384;
	static std::string LUA_SUFFIX("mix");
	static const char * pExt[] = {".txt",".html",".png",".ttf",".mp3",".wav",".jpg",".lua",".conf",".fnt",".plist",".ae",".json",".ue",".ry",".xml",".ini",".csv"}; 
	static const char EncryptKey[128] = {
		0xbf, 0x61, 0x09, 0x72, 0x1d, 0xbb, 0x6e, 0xe9, 0x9a, 0x01, 0x3d, 0x47, 0x0a, 0x11, 0x60, 0xbe, 
		0xf8, 0x48, 0x36, 0x3f, 0xdf, 0xf5, 0x9a, 0xc5, 0xca, 0x1c, 0x79, 0xcb, 0xbb, 0x90, 0x96, 0xde, 
		0x58, 0xff, 0x60, 0xbe, 0x8d, 0x4e, 0xd8, 0xe1, 0x83, 0x47, 0xd0, 0x57, 0x6d, 0x62, 0x49, 0x66, 
		0x71, 0x0d, 0x6a, 0xfe, 0x3b, 0xdc, 0xd2, 0x33, 0xd7, 0x8f, 0x5c, 0x5e, 0x4b, 0x86, 0x25, 0xd0, 
		0x6f, 0xd2, 0xd0, 0x8c, 0x53, 0x46, 0xd0, 0xc4, 0x3a, 0x10, 0xae, 0xcf, 0x75, 0xcd, 0xfd, 0x74,
		0xe8, 0xfe, 0x80, 0x0b, 0x14, 0xf9, 0x94, 0x66, 0xcc, 0x19, 0x7d, 0xda, 0x89, 0x27, 0x91, 0xab, 
		0x5c, 0x73, 0xb0, 0x78, 0xc9, 0x1c, 0x48, 0xd9, 0xe2, 0xc3, 0xfc, 0xfa, 0x3e, 0x74, 0xb9, 0xec, 
		0x81, 0x66, 0x5f, 0x5b, 0x3e, 0x73, 0x1e, 0xd2, 0x31, 0x99, 0xc7, 0xb5, 0xe7, 0x3e, 0xbc, 0x02,
	};

	static bool _calc_file_md5(const char * szFile, unsigned char md5[16])
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

		memcpy(md5,output.begin(), min(16, output.size()));

		delete [] buf;

		return true;
	}

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

	static bool _is_valid_suffix(const std::string & filename)
	{
		char size = sizeof(pExt)/sizeof(pExt[0]);
		for (char i = 0; i < size; i++)
		{
			int ret = filename.find(pExt[i]);
			if (filename.find(pExt[i]) != std::string::npos)
				return true;
		}
		return false;
	}

	static bool _create_dir(const char *path)
	{
		if(_access(path, 0)!=-1) return true;

		BOOL ret = CreateDirectoryA(path, NULL);
		if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
		{
			return false;
		}
		return true;
	}

	static bool _make_dir(const char* dir,int r)
	{
		r--;
		while(r>0&&dir[r]!='/'&&dir[r]!='\\')
			r--;
		if(r==0)
			return false;
		_make_dir(dir,r);
		char t[512] = {0};
		strcpy(t,dir);
		t[r]='\0';
		//_mkdir(t);
		return _create_dir(t);
	}

	static int _def(FILE* source, FILE* dest, int level = Z_DEFAULT_COMPRESSION)
	{
		int ret=0, flush=0;
		unsigned have = 0;
		z_stream strm;
		unsigned char in[CHUNK];
		unsigned char out[CHUNK];

		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		ret = deflateInit(&strm, level);
		if (ret != Z_OK)
			return ret;

		do {
			strm.avail_in = fread(in,1,CHUNK,source);
			if (ferror(source)){
				(void)deflateEnd(&strm);
				return Z_ERRNO;
			}
			flush = feof(source)?Z_FINISH:Z_NO_FLUSH;
			strm.next_in = in;

			do {
				strm.avail_out = CHUNK;
				strm.next_out = out;
				ret = deflate(&strm,flush);
				if (ret == Z_STREAM_ERROR)
					return Z_ERRNO;
				have = CHUNK - strm.avail_out;
				if (fwrite(out,1,have,dest) != have || ferror(dest)) {
					(void)deflateEnd(&strm);
					return Z_ERRNO;
				}
			}while(strm.avail_out == 0);
		}while(flush != Z_FINISH);
		
		if (ret != Z_STREAM_END)
			return Z_ERRNO;

		(void)deflateEnd(&strm);
		return Z_OK;
	}
}

bool PackTool::Init(int argc,char *argv[])
{
	if (argc != 4)
		return false;

	m_src = argv[1];
	m_des = argv[2];
	m_md5file = argv[3];

	if (m_src.size() > 0 && m_src[m_src.size() - 1] != '/')
	{
		m_src.append("/");
	}

	if (m_des.size() > 0 && m_des[m_des.size() - 1] != '/')
	{
		m_des.append("/");
	}

	if (m_des.find(m_src) == 0)
	{
		printf("导出路径不能包含在导入路径里边!\n");
		return false;
	}

	_make_dir(m_des.c_str(),m_des.size());

	printf("PackTool source_dir = %s\n",m_src.c_str());
	printf("PackTool dest_dir = %s\n",m_des.c_str());
	printf("PackTool md5file = %s\n",m_md5file.c_str());
	return true;
}

int PackTool::GenerateMD5File(std::map<std::string,std::string>& md5map)
{
	std::string md5path = m_des + m_md5file;
#ifdef USE_BASE64
	int len = 0;
	wchar_t * p = _ansi_to_unicode(m_md5file.c_str(),len);
	char * pRet = _unicode_to_utf8(p,len);
	delete [] p;
	
	len = len*4+1;
	char * des = new char[len];
	memset(des,0,sizeof(char)*len);
	
	Base64Code base64;
	base64.Encode(pRet,des);
	delete [] pRet;

	md5path = m_des;
	md5path += des;
	md5path += ".enc";

	delete [] des;
#endif

	//std::string md5path = m_des + m_md5file;
	FILE * dfp = fopen(md5path.c_str(),"wb");
	if (!dfp)
		return 1;

	std::ofstream md5_sev(md5path.c_str());
	md5_sev << VERSION << "\n";
	std::map<std::string,std::string>::iterator it = md5map.begin(), eit = md5map.end();
	for( ; it != eit; ++it)
	{
		md5_sev << it->first;
		md5_sev << " ";
		md5_sev << it->second;
		md5_sev << "\n";
	}
	md5_sev.close();

	return 0;
}

int PackTool::Pack()
{
	std::map<std::string,std::string> md5map;
	int ret = DoPack(m_src,md5map);
	if (0 == ret)
		ret = GenerateMD5File(md5map);
	return ret;
}

int PackTool::DoPack(std::string path, std::map<std::string,std::string>& md5map)
{
	if (path.size() > 0 && path[path.size() - 1] != '/')
	{
		path.append("/");
	}

	std::string tmp1 = path;
	std::string tmp2 = path + "*.*";

	int handle;
	struct _finddata_t fileinfo;

	handle = _findfirst(tmp2.c_str(),&fileinfo);
	if(-1==handle) return false;
	while(!_findnext(handle,&fileinfo))
	{
		if(strcmp(fileinfo.name,".")==0 || strcmp(fileinfo.name,"..")==0)
			continue;

		std::string tempSrc = tmp1 + fileinfo.name;
		std::string relativePath = tempSrc.substr(m_src.length());
		std::string des_path = m_des+tmp1.substr(m_src.length());
		if(fileinfo.attrib==_A_SUBDIR)
		{
			des_path += fileinfo.name;
			des_path += "/";
			_make_dir(des_path.c_str(),des_path.size());
			DoPack(tempSrc,md5map);
		}
		else
		{
			int ret = GenerateFile(fileinfo.name,tempSrc,des_path,md5map);
			if (0 != ret)
			{
				md5map.erase(tempSrc);
				printf("GenerateFile %s failed. ret=%d\n",relativePath.c_str(),ret);
				return ret;
			}
		}
	}
	return 0;
}

int PackTool::EncryLuaFile(const std::string & src, const std::string & suffix)
{
	FILE * fp = fopen(src.c_str(),"rb");
	fseek(fp,0,SEEK_END);
	int len = ftell(fp);
	if (len > 1)
	{
		fseek(fp,0,SEEK_SET);
		
		//读取并加密到缓存
		char * tmp = new char[len];
		memset(tmp,0,len);
		fread(tmp,1,len,fp);
		GNET::Octets codeBuf(tmp,len);
		delete [] tmp;
		
		GNET::ARCFourSecurity arc4;
		arc4.SetParameter(GNET::Octets(EncryptKey,sizeof(EncryptKey)/sizeof(char)));
		GNET::Octets decrypt = arc4.Update(codeBuf);

		//加密后的缓存写入到文件
		std::string dest = src + suffix;
		FILE * dfp = fopen(dest.c_str(),"wb");
		fwrite(codeBuf.begin(),1,codeBuf.size(),dfp);
		fclose(dfp);
	}
	fclose(fp);
	return 0;
}

int PackTool::GenerateFile(const char * filename, const std::string & src, const std::string & dest, std::map<std::string,std::string>& md5map)
{
	if (!_is_valid_suffix(src))
	{
		printf("ignore file %s.\n",src.c_str());
		return 0;
	}

	std::string luasuffix = ".lua";
	luasuffix += LUA_SUFFIX;
	if (src.find(luasuffix.c_str()) != std::string::npos)
	{
		printf("ignore luamix file %s.\n",src.c_str());
		return 0;
	}

	if (src.find(" ") != std::string::npos)
	{
		printf("文件名字/路径 %s 包含空格!\n", src.c_str());
		return 1;
	}

	printf("GenerateFile %s.\n",src.c_str());

	std::string tsrc = src;
	std::string tfilename = filename;

	bool bIsLua = src.find(".lua") != std::string::npos;
	if (bIsLua)
	{
		//给lua文件创建一个加密文件
		EncryLuaFile(src,LUA_SUFFIX);
		tsrc += LUA_SUFFIX;
		tfilename += LUA_SUFFIX;
	}

	//添加md5值，要添加未压缩之前的，这样客户端只需要保留解压之后的文件和以后的更新做比对就行
	unsigned char md5[16]={0};
	_calc_file_md5(tsrc.c_str(),md5);

	char str[128] = {0};
	sprintf(str,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",md5[0], md5[1], md5[2], md5[3],
		md5[4], md5[5], md5[6], md5[7], md5[8], md5[9], md5[10], md5[11], md5[12], md5[13], md5[14], md5[15]);

	std::string relativePath = tsrc.substr(m_src.length());
	md5map[relativePath] = str;
	
	//把文件压缩并添加到dest文件夹下
	std::string tdestpath = dest + tfilename;
#ifdef USE_BASE64
	int len = 0;
	wchar_t * p = _ansi_to_unicode(tfilename.c_str(),len);
	char * pRet = _unicode_to_utf8(p,len);
	delete [] p;
	
	len = len*4+1;
	char * des = new char[len];
	memset(des,0,sizeof(char)*len);
	
	Base64Code base64;
	base64.Encode(pRet,des);
	delete [] pRet;

	tdestpath = dest;
	tdestpath += des;
	tdestpath += ".enc";

	delete [] des;
#endif

	FILE * fpSrc = fopen(tsrc.c_str(),"rb");
	FILE * fpDes = fopen(tdestpath.c_str(),"wb");
	
	int bRes = 0;
	if (fpSrc && fpDes)
		bRes = _def(fpSrc,fpDes);

	fclose(fpSrc);
	fclose(fpDes);

	if (bIsLua)
		remove(tsrc.c_str());

	return bRes;
}