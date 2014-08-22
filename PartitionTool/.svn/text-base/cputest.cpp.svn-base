#include <math.h>
//#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define _GNU_GNU             /* See feature_test_macros(7) */
#include <sched.h>

const float pi = 3.14;
const float eps = 0.1;

long gettickcount()
{
	timeval tv;
	timezone tz;
	gettimeofday(&tv, &tz);
//	printf("%lld %lld\n", tv.tv_sec, tv.tv_usec);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void cpuload(int percent)
{
    long timeSclice=1000000;
    long runTime = timeSclice * percent / 100;
    long sleepTime = timeSclice - runTime;

    long startTime = gettickcount();
    long endTime;
    
    do
    {
        endTime = gettickcount();
    }while(endTime - startTime < runTime);
    
    usleep(sleepTime);
}

int main()
{
	//gettickcount();
	//pre process

	int cpunum = sysconf(_SC_NPROCESSORS_CONF);
	cpu_set_t mask;
    int myid;	
	srand(6666);
	myid = rand() % cpunum;

	CPU_ZERO(&mask);
	CPU_SET(myid, &mask);

//	printf("set to cpu %d in %d cpus!!!\n",myid, cpunum);

	if(sched_setaffinity(0, sizeof(mask), &mask) == -1)
	{
		printf("warning: could not set CPU affinity, continuing...\n");
	}
	else
	{
		printf("set to cpu %d in %d cpus!!!\n",myid, cpunum);
	}

	while(1)
	{
		float f = 0;
		while(fabs(2*pi -f) > eps){
			cpuload(sin(f) * 50 + 50);
			f += 0.1;
		}
	}
	return 0;
}
