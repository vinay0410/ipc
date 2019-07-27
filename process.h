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
#include <unistd.h>


using namespace std;

#define SHM_KEY 1234
#define SNAME "/mysem"
#define MAX 100000

extern const vector<string> data_to_write;
//sem_t *sem;
//std::mutex shm_mutex; 

void set(int shmid, void* ptr, string in);
string get(int shmid, void* ptr);
void clean(int key, void* ptr);
void* setup(int key, int* shmid);