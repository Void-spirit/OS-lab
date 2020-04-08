#include <iostream>
#include <sys/shm.h>
#include <stdlib.h>
using namespace std;

int func(const void *x, const void *y){
return (*((int*)x) - *((int*)y));
}

int main(int argv, char *argc[]){
int memeid = atoi(argc[1]);
const int n = atoi(argc[2]);
int *mem = (int*)shmat(memeid, 0, 0);
for (int i = 0; i < n; i++){
cout << mem[i] << " ";
}
cout << endl;
qsort(mem, n, sizeof(int), func);
for (int i = 0; i < n; i++){
cout << mem[i] << " ";
}
cout << endl;
return 0;
}
