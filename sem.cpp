#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mutex>
#include <vector>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>    

using namespace std;

#define SHM_KEY 1234
#define SNAME "/mysem"
#define MAX 1


sem_t* mySem;

void atomic_func() {

    sem_wait(mySem);

    cout << "Hello World" << endl;

    sem_post(mySem);

}

int main() {

    cout << sem_unlink(SNAME) << endl;

    mySem = sem_open(SNAME, O_CREAT, 0777, 1);

    int val;
    sem_getvalue(mySem, &val);

    cout << val << endl;

    std::thread t1 (atomic_func);

    t1.join();

    sem_getvalue(mySem, &val);

    cout << val << endl;


    int ret = sem_close(mySem);


    cout << ret << endl;

    ret = sem_unlink(SNAME);

    cout << ret << endl;

}