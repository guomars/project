#include "DataMgr.h"
#include "WStrToUTF8.h"
#include "gutil.h"

#include <pthread.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <direct.h>
#include "gnproto.h"
#include "gnsecure.h"
#else
#include <dirent.h>
#include "protocol.h"
#include "security.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

namespace
{
	//含有本词缀的会保存到文件中
	static const char * SAVE_TAG = "_save";
}

DataMgr::DataMgr() 
{
}

const char* DataMgr::GetString(const char*key, bool fromfile)
{
	std::string keylower(key);
	ToLower(keylower);
	if (fromfile)
		keylower.append(SAVE_TAG);
	StringMap::iterator it = m_StringMap.find(keylower);
	if(it == m_StringMap.end())
	{
		return "";
	}

	return it->second.c_str();
}

int DataMgr::GetInt(const char*key, bool fromfile)
{
	std::string keylower(key);
	ToLower(keylower);
	if (fromfile)
		keylower.append(SAVE_TAG);
	StringMap::iterator it = m_StringMap.find(keylower);
	if(it == m_StringMap.end())
	{
		return 0;
	}

	return StringToT<int>(it->second);
}

void DataMgr::SetInt(const char*key,int value, bool tofile)
{
	std::string keylower(key);
	ToLower(keylower);

	size_t len = keylower.size();
	size_t size = strlen(SAVE_TAG);
	size_t pos = keylower.find(SAVE_TAG);
	if (len >= size && pos == len-size)
	{
		CCLog("SetInt(%s) Failed.", key);
		return ;
	}

	if (tofile)
		keylower.append(SAVE_TAG);

	m_StringMap.erase(keylower);
	m_StringMap.insert(std::make_pair(keylower,TToString(value)));

	CCLog("SetInt(%s) value(%d).", key,value);
}
	
void DataMgr::SetString(const char*key, const char*value, bool tofile)
{
	std::string keylower(key);
	ToLower(keylower);

	size_t len = keylower.size();
	size_t size = strlen(SAVE_TAG);
	size_t pos = keylower.find(SAVE_TAG);
	if (len >= size && pos == len-size)
	{
		CCLog("SetString(%s) Failed.", key);
		return ;
	}

	if (tofile)
		keylower.append(SAVE_TAG);

	m_StringMap.erase(keylower);
	m_StringMap.insert(std::make_pair(keylower,value));

	CCLog("SetString(%s) value(%s).", key,value);
}

bool DataMgr::LoadFromFile(const char *fileName)
{
	std::string temp = GetFileData(fileName);

	if (temp.empty())
		return false;

	std::vector<std::string> vec;
	int pos;
	const char LF = 0x0a;

	while(true)
	{
		if(temp.empty())
			break;
		pos = temp.find(LF);
		if(pos != -1)
		{
			vec.push_back(temp.substr(0,pos));
			temp = temp.substr(pos + 1);
		}
		else
		{
			vec.push_back(temp);
			temp = "";
		}
	}

	m_StringMap.clear();

	for(int i = 0;i < (int)vec.size();++i)
	{
		std::string & str = vec[i];
		temp = GetDecryptedStr(str.c_str(),str.size());
		VectorString vecSplit;
		SplitToList(temp,vecSplit,'=');
		if(vecSplit.size() != 2)
			continue;
		std::string keylower = vecSplit[0];
		ToLower(keylower);
		size_t len = keylower.size();
		size_t size = strlen(SAVE_TAG);
		size_t pos = keylower.find(SAVE_TAG);
		if (len >= size && pos == len-size)
			m_StringMap.insert(std::make_pair(keylower,vecSplit[1]));
	}

	m_save_file = fileName;

	return true;
}

bool DataMgr::SaveToFile(const char *fileName)
{
	const char * _file = NULL;
	if (fileName)
	{
		_file = fileName;
		m_save_file = fileName;
	}
	else
		_file = m_save_file.c_str();

	FILE*file = fopen(_file,"wb");
	if (!file){
		CreateDir(_file);
		file = fopen(_file, "wb");
		if (!file){
			CCLog("SaveStr(%s) Failed", _file);
			return false;
		}
	}

	StringMap::iterator it = m_StringMap.begin(),itEnd = m_StringMap.end();

	std::string temp;
	for(;it != itEnd;++it)
	{
		size_t len = it->first.size();
		size_t size = strlen(SAVE_TAG);
		size_t pos = it->first.find(SAVE_TAG);
		if (len >= size && pos == len-size)
		{
			temp = it->first;
			temp += "=";
			temp += it->second;
			temp += "\n";
			std::string decryptedstr = GetDecryptedStr(temp.c_str(),temp.size());
			fwrite(decryptedstr.c_str(),1,(int)decryptedstr.size(),file);
		}
	}

	fclose(file);

	return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
bool DataMgr::CreateDir(const char *path)
{
	if(_access(path, 0)!=-1) return true;

	BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
}

#else
bool DataMgr::CreateDir(const char *path)
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
#endif