/*
 * implementing log.
 */

#ifndef __GNET_LOG_H__
#define __GNET_LOG_H__

#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/un.h>
#include <errno.h>

#include <ios>
#include <iostream>
#include <fstream>
#include <string>

#include "octets.h"

namespace GNET
{
	class Log
	{
	private:
		Log() { }

		virtual ~Log()
		{
		}

		static Log & instance( )
		{
			static Log s_log;
			return s_log;
		}

	public:
		static const char * prioritystring( int __priority )
		{
			static char * sz_emerg   = "emerg";
			static char * sz_alert   = "alert";
			static char * sz_crit    = "crit";
			static char * sz_err     = "err";
			static char * sz_warning = "warning";
			static char * sz_notice  = "notice";
			static char * sz_info    = "info";
			static char * sz_debug   = "debug";

			switch( __priority )
			{
			case LOG_DEBUG:
				return sz_debug;
			case LOG_INFO:
				return sz_info;
			case LOG_NOTICE:
				return sz_notice;
			case LOG_WARNING:
				return sz_warning;
			case LOG_ERR:
				return sz_err;

			case LOG_CRIT:
				return sz_crit;
			case LOG_ALERT:
				return sz_alert;
			case LOG_EMERG:
				return sz_emerg;
			default:
				return sz_info;
			}
		}

		static void log( int __priority, const char * __fmt, ... )
		{
#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
            if (__priority > LOG_WARNING)
                return;
#endif
			va_list ap;
			va_start(ap,__fmt);

            FILE * file = NULL;
            if (__priority > LOG_WARNING)
                file = stdout;
            else
                file = stderr;
            
            fprintf( file, "%s : ", Log::prioritystring(__priority) );
            vfprintf( file, __fmt, ap );
                
            size_t len = (__fmt ? strlen(__fmt) : 0);
            if( len > 0 && __fmt[len-1] != '\n' )
                fprintf( file, "\n" );
			va_end(ap);
		}

		static void trace( const char * __fmt, ... )
		{
#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
            return;
#endif
			va_list ap;
			va_start(ap,__fmt);
            
            FILE * file = stdout;
            
            fprintf( file, "trace : ");
            vfprintf( file, __fmt, ap );
            
            size_t len = (__fmt ? strlen(__fmt) : 0);
            if( len > 0 && __fmt[len-1] != '\n' )
                fprintf( file, "\n" );
			va_end(ap);
		}
	};

#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
    #define LOG_TRACE(...)
#else
	#define LOG_TRACE	GNET::Log::trace
#endif

}

#endif


