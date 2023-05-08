#include <stdio.h>
#include <pthread.h>
void * thread_main(void *arg);

int main(int argv, char *argv[])
{
	pthread_t t_id;
	int pthread_param = 5;

	if(pthread_create(&t_id, NULL, thread_main, (void*)&pthread_param)!= 0)
	{
		pts("pthread_create() error");
		return -1;
	};
	sleep(10);put("end of main");
	return 0;
}

void* thread_main(void *arg)
{
	int i;
	int cnt =*((int*)arg);
	for(i = 0; i<cnt; i++)
	{
		sleep(1);puts("runing thread");
	}
	return NULL;
}