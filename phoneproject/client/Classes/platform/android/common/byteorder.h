
//#include "platform.h"

#if defined(__x86_64__)
    #warning "__x86_64__"
	#include "byteorder_x86_64.h"
#elif defined(__i386__)
    #warning "__i386__"
	#define __GNUC_IOS__
	#include "byteorder_i386.h"
#else
    #warning "__else__"
	#define __GNUC_IOS__
    #include "byteorder_i386.h"
#endif
