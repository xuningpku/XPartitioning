#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <cstring>

using namespace std;



void* start_routine(void* arg)
{
	int id = *(int*)arg;
	pid_t pid=getpid();
	pthread_t thread = pthread_self();
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);

	CPU_SET(id, &cpuset);

	pthread_setaffinity_np(thread, sizeof(cpu_set_t),&cpuset);
	int s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if(s != 0)
	{
		printf("Error in pthread_getaffinity_np\n");
		return NULL;
	}
	else
	{
		printf("PID:%d Set returned by pthread_getaffinity_np() contained:\n", pid);
		for (int j = 0; j < CPU_SETSIZE; j++)
			if (CPU_ISSET(j, &cpuset))
				printf("	 CPU %d\n", j);
	}
    FILE* fp = fopen("/home/hadoop/simon/dataset/twitter_rv.net", "r");
	if(fp == NULL) {
		printf("failed to open!\n");
	}
    char buf[1024];
	long long line = 0;
	while( fgets(buf, 1024, fp) != NULL) {
		//fgets(buf, 1024, fp);
		stringstream oss;
		strlen(buf);
		//string str(buf);
		oss << buf;
		line++;
	}
    printf("id=%d line: %lld\n", id, line); 
	return NULL;
}

int main()
{
	int tot = 1;
	pthread_t thread[20];
	srand(time(NULL));
	int array[20];
	for(int i = 0; i < tot; i++)
	{
		array[i] = i;
		pthread_create(&thread[i], NULL, &start_routine, array+i);
	}
	for(int i = 0; i <  tot; i++)
		pthread_join(thread[i], NULL);
	return 0;
}
