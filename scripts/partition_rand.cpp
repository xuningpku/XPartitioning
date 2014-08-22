#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int get_rand(int s, int e)
{
	int length = e - s + 1;
	unsigned int rnd = rand() * RAND_MAX + rand();
	return (rnd % length + s);
}

void test_rand()
{
	int cnt[100] = {0};

	for(int i = 0; i < 10000; i++)
	{
		cnt[get_rand(0,99)]++;
	}

	for(int i = 0; i < 100; i++)
	{
		printf("%d ", cnt[i]);
	}
	printf("\n");
}

int main(int argc, char** args)
{
	char* filename = args[1];
//	int num_lines = atoi(args[2]);
	int part = atoi(args[2]);
	printf("random partition file: %s into %d partitions.\n", filename, part);
	srand(time(NULL));
//	test_rand();
//	return 1;
	freopen(filename, "r", stdin);
	FILE* out[100];
	int out_num = part;
	char fname[256];
	for(int i = 0; i < out_num; i++)
	{
		sprintf(fname, "%s.rnd.%d", filename, i);
		out[i] = fopen(fname, "w");
	}

	int v1, v2;
	while(scanf("%d %d", &v1, &v2) != EOF)
	{
		int idx = rand() % out_num;
		fprintf(out[idx], "%d %d\n", v1, v2);
	}
	for(int i = 0; i< out_num; i++)
	{
		fclose(out[i]);
	}
	return 0;
}

