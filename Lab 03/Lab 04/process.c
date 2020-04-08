#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int n = 20;

int func1(const void *a, const void *b);

void func2(int *arr);

int main()
{
	srand(time(NULL));
	int memid = shmget(IPC_PRIVATE, n*sizeof(int), 0600|IPC_CREAT|IPC_EXCL);
	int *arr = (int*)shmat(memid, 0, 0);
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 999;
	}
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	int childid = fork();
	if(childid == 0)
		func2(arr);
	else
		waitpid(childid, NULL, 0);
	shmdt(arr);
	return 0;
}

int func1(const void *a, const void *b)
{
        return(*((int*)a) - *((int*)b));
}

void func2(int *arr)
{
        qsort(arr, n, sizeof(int), func1);
        for(int i = 0; i < n; i++)
        {
		printf("%d ", arr[i]);
        }
}

