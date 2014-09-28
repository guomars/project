#ifndef __DATAMGR_H__
#define __DATAMGR_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <map>
#include <string>

class DataMgr
{
	DataMgr();
public:
	typedef std::map<std::string,std::string >  StringMap;
private:
	StringMap m_StringMap;
	std::string m_save_file;
public:
	static DataMgr * sharedMgr()
	{
		static DataMgr data_mgr;
		return &data_mgr;
	}
	void ClearMap()
	{
		m_StringMap.clear();
	}

	const char* GetString(const char*key, bool tofile=false);
	void SetString(const char*key, const char*value, bool fromfile=false);
	// lua中涉及到数字操作的直接使用GetString容易使整个脚本无效，所以提供GetInt接口。【最明显的一个bug就是，lua中tonumber(GetString("key"))，然后如果那个key没有，tonumber实际上无法成功，会导致整个脚本出错】
	int GetInt(const char*key, bool tofile=false);
	void SetInt(const char*key,int value, bool fromfile=false);

	bool SaveToFile(const char *fileName = NULL);
	bool LoadFromFile(const char *fileName);

	bool CreateDir(const char *path);
};

#endif // __DATAMGR_H__