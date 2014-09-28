#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "threadusage.h"

#ifndef RUSAGE_THREAD
#define RUSAGE_THREAD 1
#endif

class usage_stat
{
    struct timeval _begin_time;
    struct rusage _begin_usage;

    float _user;
    float _sys;
    long _memory;
    bool _thread;
public:
    usage_stat(bool is_thread=true):_user(0.f),_sys(0.f), _memory(0), _thread(is_thread)
    {
    	Reset();
    }
    float GetUser() const {return _user;}
    float GetSys() const {return _sys;}
    long GetMem() const {return _memory;}

    static float GetDiff(const timeval& end, const timeval & begin)
    {
    	return (float)(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)/1000000.f;
    }
    bool DoStat(float min_interval, float e)
    {
	    struct timeval now;
	    gettimeofday(&now, NULL);
	    float elapse= GetDiff( now, _begin_time);
	    if (elapse -min_interval < e) return false;

	    struct rusage r_usage;
	    getrusage(_thread?RUSAGE_THREAD:RUSAGE_SELF,&r_usage );
	    float ut = GetDiff(r_usage.ru_utime, _begin_usage.ru_utime);
	    float st = GetDiff(r_usage.ru_stime, _begin_usage.ru_stime);
        _memory = r_usage.ru_maxrss;
	    _user = ut/elapse;
	    _sys = st/elapse;
	    return true;
    }
    void Reset()
    {
    	gettimeofday(&_begin_time, NULL);
	getrusage(_thread?RUSAGE_THREAD:RUSAGE_SELF,&_begin_usage);
    }
};

struct thread_usage	//一个线程所相关的统计信息
{
	int lock;
private:
	usage_stat sec;	//每一秒的统计
	usage_stat sec5;//每五秒的统计
	usage_stat min; //每分钟的统计
	usage_stat min5;//每五分钟的统计
public:
	std::string ident;
	thread_usage():lock(0){}
	thread_usage(bool thread):lock(0),sec(thread),sec5(thread),min(thread),min5(thread){}
	void TryDoStat() { //这个函数会被一秒调用一次
		//ASSERT(lock);
		if (sec.DoStat(1, -0.3)) sec.Reset();
		if (sec5.DoStat(5,-0.3)) sec5.Reset();
		if (min.DoStat(60, -1))  min.Reset();
		if (min5.DoStat(300, -5)) min5.Reset();
	}
	std::stringstream& dump(int idx, std::stringstream& os)
	{
		//ASSERT(lock);
		char buf[256] = {0};
		char name[256] = {0};
		if (!ident.empty())
			strcpy(name ,ident.c_str());
		else
			strcpy(name, "unknown");
		sprintf (buf, "%d:%-10s usage:1(%02.1f%%,%02.1f%%,%ld) 5(%02.1f%%,%02.1f%%,%ld) 60(%02.1f%%,%02.1f%%,%ld) 300(%02.1f%%,%02.1f%%,%ld)\n",
				idx, name, 
				sec.GetUser()*100 , sec.GetSys()*100, sec.GetMem(),
				sec5.GetUser()*100, sec5.GetSys()*100, sec5.GetMem(),
				min.GetUser()*100, min.GetSys()*100, min.GetMem(),
                 min5.GetUser()*100, min5.GetSys()*100, min5.GetMem());
		os << buf;
		return os;
	}

	std::stringstream& get_log_string(std::stringstream& os)
	{
		//ASSERT(lock);
		char buf[256] = {0};
		char name[256] = {0};
		if (!ident.empty())
			strcpy(name ,ident.c_str());
		else
			strcpy(name, "unknown");
		sprintf (buf, "(%s,us%02.1f%%,sy%02.1f%%)", name, min5.GetUser()*100, min5.GetSys()*100);
		os << buf;
		return os;
	}
};

namespace ThreadUsage
{
	static thread_usage _instance(false); 

	void StatSelf(const char *ident)
	{
		_instance.TryDoStat();
		if (_instance.ident.empty() && ident)
		{
			_instance.ident = ident;
		}
	}

	void Dump(FILE *fp)
	{
		std::stringstream os;
		_instance.dump(0, os);
		
		fprintf (fp, os.str().c_str());
		fflush(fp);
	}

	void GetLogString(std::stringstream& os)
	{
		_instance.get_log_string(os);
	}
    
    void PRINT_MEM_USAGE(const char * name)
    {
        static rusage g_usage;
        if (name)
        {
            rusage tmp = g_usage;
            getrusage(RUSAGE_SELF, &g_usage);
            printf("%s memory cost %ld , total %ld\n", name, g_usage.ru_maxrss-tmp.ru_maxrss, g_usage.ru_maxrss);
        }
        else{
            getrusage(RUSAGE_SELF, &g_usage);
            printf("memory cost %ld \n",g_usage.ru_maxrss);
        }
    }
};


/*int main(int argc, char ** argv)
{
	if(argc != 2)
		return 0;
	unsigned long r = atoi(argv[1]);
	
	struct timeval now;
	gettimeofday(&now, NULL);
	while(1)
	{
		if(rand()%100 < r)
		{
			int s = 0;			
			for(int i=0; i<500; i++)
				for(int j=0; j<5000; j++)
					s += 1;
		}
		else
			usleep(10000);			
		struct timeval now2;
		gettimeofday(&now2, NULL);
		//float elapse = (float)(now2.tv_sec - now.tv_sec) + (now2.tv_usec - now.tv_usec)/1000000.f;
		//printf("elapse = %f\n", elapse);
		
		if(now2.tv_sec != now.tv_sec)
		{
			ThreadUsage::StatSelf("Main");
			if(now2.tv_sec % 5 == 0)
				ThreadUsage::Dump(stdout);
		}
		now = now2;
	}
	return 0;
}*/
