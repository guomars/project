#ifndef __G_GAME_DATA_H__
#define __G_GAME_DATA_H__

#include <string>
#include "csvtable.h"

int InitDataTables(const char * path, const char * file, int table_type);

csvtable * GetTable(const char * name);

#endif