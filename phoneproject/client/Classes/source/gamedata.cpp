#include "gamedata.h"
#include "cocos2d.h"
#include <map>

USING_NS_CC;

std::map<std::string, csvtable > tables;

int InitDataTables(const char * path, const char * file, int table_type)
{
	std::string t_file(file);
	std::string t_path(path);
    if (path[t_path.size()-1]!='/')
        t_path.push_back('/');
    {
		t_path += file;
		t_path += ".csv";
		std::string fullname = CCFileUtils::sharedFileUtils()->fullPathForFilename(t_path.c_str());
        int ret = tables[t_file].Init(fullname.c_str(), table_type);
        if ( ret != 0)
        {
            return ret;
        }
        ret = tables[t_file].read("");
        if ( ret != 0)
        {
            return ret;
        }
		CCLog("InitTable %s",fullname.c_str());
    }

    return 0;
}

csvtable * GetTable(const char * name)
{
	if (!name)
		return NULL;

	std::string t_name(name);
	std::map<std::string, csvtable >::iterator it = tables.find(t_name);
	if (it == tables.end())
		return NULL;

	return &(it->second);
}