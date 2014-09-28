#ifndef __PACK_TOOL_H__
#define __PACK_TOOL_H__

#include <string>
#include <map>
#include <windows.h>

class PackTool
{
	PackTool() {}
public:
	static PackTool & GetInstance()
	{
		static PackTool pt;
		return pt;
	}

	bool Init(int argc,char *argv[]);

	int Pack();

private:

	int DoPack(std::string path, std::map<std::string,std::string>& md5map);

	int GenerateFile(const char * filename, const std::string & src, const std::string & dest, std::map<std::string,std::string>& md5map);

	int EncryLuaFile(const std::string & src, const std::string & suffix);

	int GenerateMD5File(std::map<std::string,std::string>& md5map);

private:
	std::string m_src;
	std::string m_des;
	std::string m_md5file;
};

#endif