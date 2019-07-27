#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

using namespace std;

int main()
{
    key_t          ShmKEY;

    ShmKEY = ftok("./ftok.cp", 'x');

    cout << ShmKEY << endl;
}