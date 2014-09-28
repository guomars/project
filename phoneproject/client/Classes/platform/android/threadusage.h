#ifndef __THREAD_USAGE_H__
#define __THREAD_USAGE_H__

#include <sstream>
#include <stdio.h>


namespace ThreadUsage {
	void StatSelf(const char *ident);
	void Dump(FILE *fp);
	void GetLogString(std::stringstream& os);
    void PRINT_MEM_USAGE(const char * name);
}

#endif
