#include <stdio.h>
#include <windows.h>
#include <poress.h>

unsigned WINAPI Read(void *arg);
unsigned WINAPI Accu(void *arg);
static HANDLE semOne;
static HANDLE semTwo;
static int num;

int main(int argc, char *argv[])
{
	HANDLE hThread1, hThread2;
	semOne = CreateSemaphore(NULL,0,1,NULL);
	semTwe = CreateSemaphore(NULL,1,1,NULL);
	hThread1=(HANDLE)_beginthreadex(NULL, 0, Read, NULL, 0, NULL);
	hThread2=(HANDLE)_beginthreadex(NULL, 0, Accu, NULL, 0, NULL);

	WaitForSingleObjects(hThread1, INFINITE);
	WaitForSingleObjects(hThread2, INFINITE);

	CloseHandle(semOne);
	CloseHandle(semTwo);
	return 0;
}

unsigned WINAPI Read(void *arg)
{
	int i;
	for(i = 0; i <5; i++)
	{
		fputs("Input num: ", stdout);
		WaitForSingleObjects(semTwo, INFINITE);
		scanf("%d", &num);
		ReleseSemaphore(semOne, 1, NULL);
	}
	return 0;
}

unsigned WINAPI Accu(void *arg)
{
	int sum = 0, i;
	for(i = 0; i <5; i++)
	{
		WaitForSingleObjects(semOne, INFINITE);
		sum+=num;
		ReleseSemaphore(semTwo, 1, NULL);
	}
	printf("Result: %d \n", sum);
	return 0;
}