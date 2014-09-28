
#include "platform.h"

#if defined(__x86_64__)
	#include "marshal_x86_64.h"
#elif defined(__i386__)
    #define __GNUC_IOS__
	#include "marshal_i386.h"
#else
    #define __GNUC_IOS__
    #include "marshal_i386.h"

#endif
