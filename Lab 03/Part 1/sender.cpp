#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

const int n = 20;
int main(){
srand(time(NULL));
int memeid = shmget(IPC_PRIVATE, n*sizeof(int), 0600|IPC_CREAT|IPC_EXCL);
int *arr = (int*)shmat(memeid, 0, 0);
for (int i = 0; i < n; i++){  //цикл для генерации рандомных чисел
arr[i] = rand() % 999;
}
char callbuf[1024];
sprintf(callbuf, "./receiver %i %i", memeid, n);
system(callbuf);
return 0;
}

