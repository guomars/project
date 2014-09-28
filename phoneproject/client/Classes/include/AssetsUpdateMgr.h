#ifndef __ASSETS_UPDATE_MGR_H__
#define __ASSETS_UPDATE_MGR_H__

#include <string>
#include "cocos2d.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

typedef void(*func)(void * p);

class download_param : public CCObject
{
	download_param():timeout(30),trytime(1),use_base64(false),use_resume(false),ret(false),download_finish_func(NULL),script_download_finish_func(NULL) {}
public:
	std::string src;	//下载文件的url
	std::string des;	//下载文件的路径
	std::string sub_path;	//下载文件的子路径
	std::string filename;	//下载文件的名字
	int timeout;	//下载任务的超时时间
	int trytime;	//下载任务失败重试次数
	bool use_base64;	//是否转换成base64编码的文件名
	bool use_resume;	//是否使用断点重下，md5文件不能断点重下
	bool ret;	//下载结束之后判断是成功还是失败
	func download_finish_func;	//下载结束之后调用的c回调函数
	CCCallFunc* script_download_finish_func;	//下载结束之后调用的脚本回调函数

	static download_param * create()
	{
		download_param * pobj = new download_param();
		if (pobj)
		{
			pobj->autorelease();
		}
		return pobj;
	}

	//这个是给lua用的
	static download_param * create(std::string _src, std::string _des, std::string _sub_path, std::string _filename,
			int _timeout, int _trytime, bool _use_base64, bool _use_resume, CCCallFunc* _script_download_finish_func)
	{
		download_param * pobj = new download_param();
		if (pobj)
		{
			pobj->src = _src;
			pobj->des = _des;
			pobj->sub_path = _sub_path;
			pobj->filename = _filename;
			pobj->timeout = _timeout;
			pobj->trytime = _trytime;
			pobj->use_base64 = _use_base64;
			pobj->use_resume = _use_resume;
			pobj->download_finish_func = NULL;
			pobj->script_download_finish_func = _script_download_finish_func;

			pobj->autorelease();
		}
		return pobj;
	}

	bool getRet() const
	{
		return ret;
	}
};

class update_param : public CCObject
{
	update_param():timeout(30),trytime(1),ret(false) {}
public:
	std::string resource_path;	//当前使用的资源路径
	std::string download_path;	//下载文件临时保存路径
	std::string src;	//下载链接的url
	std::string md5_file;	//md5文件的名字
	std::vector<std::string> des;	//md5不匹配的文件名字
	int timeout;	//下载的单个任务的超时时间
	int trytime;	//下载的单个任务失败重试次数
	bool ret;	//更新结束之后判断是成功还是失败

	static update_param * create()
	{
		update_param * pobj = new update_param();
		if (pobj)
		{
			pobj->autorelease();
		}
		return pobj;
	}

	//这个是给lua用的
	static update_param * create(std::string _resource_path, std::string _download_path, std::string _src, std::string _md5_file, int _timeout, int _trytime)
	{
		update_param * pobj = new update_param();
		if (pobj)
		{
			pobj->resource_path = _resource_path;
			pobj->download_path = _download_path;
			pobj->src = _src;
			pobj->md5_file = _md5_file;
			pobj->timeout = _timeout;
			pobj->trytime = _trytime;
			pobj->autorelease();
		}
		return pobj;
	}

	bool getRet() const
	{
		return ret;
	}
};

class AssetsUpdateManager
{
	enum AUM_STAT
	{
		AUMS_INIT,
		AUMS_UPDATE_MD5FILE,
		AUMS_UPDATE_MD5FILE_OK,
		AUMS_UPDATE_ONE_FILE,
		AUMS_UPDATE_ONE_FILE_OK,
		AUMS_UPDATE_OK,
		AUMS_UPDATE_FAILED,
	}m_stat;

	AssetsUpdateManager():m_stat(AUMS_INIT) {}

public:
	static AssetsUpdateManager* GetInstance()
	{
		static AssetsUpdateManager _stub;
		return &_stub;
	}

	bool IsExistDir(const char* szDir);
	bool createDir(const char *path);
	bool MakeDir(const char* dir,int r);
	bool deleteDir(const std::string& src);
	bool copyFiles(std::string src,std::string des);

	//建立下载任务，由于没有开启新的线程，所以下载慢的话会卡住调用的线程
	void downLoad(download_param * pdp);

	//建立一个新的线程去调用downLoad函数
	void newThreadDownLoad(download_param * pdp);

	//在tick里边调用更新资源,返回false就是没更新完呢
	bool CheckUpdate(update_param * pup);
	void onFileDownLoadFinish(void * p);
    
    std::string GetDocumentPath();
    std::string GetTmpPath();
    std::string GetCachePath();

private:
	bool UnCompressFile(const std::string & src, const std::string & des);
	bool CheckMD5(update_param * pup);
	bool generateLocalMd5List(const std::string& root,std::map<std::string,std::string>& md5map,const std::string& baseDir);
};

#endif