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

vector<string> data{"abcde", "fghij", "klmno", "pqrst", "uvwxy"};


sem_t *sem;
std::mutex shm_mutex; 

void set(int shmid, void* ptr, string data);
//string get(int shmid, void* ptr);
void clean(int key, void* ptr);
void* setup(int key, int* shmid);

void* setup(int key, int* shmid) {
    *shmid = shmget(SHM_KEY,1024,0666|IPC_CREAT);
    return shmat(*shmid,(void*)0,0);
}

void set(int shmid, void* ptr, string data) {

    //int shmid = shmget(key,1024,0666|IPC_CREAT);
    // shmat to attach to shared memory

    //shmctl(shmid,SHM_LOCK,NULL);

    //shm_mutex.lock();

    sem_wait(sem);

    //shm_mutex.unlock();

    char *str = (char*) ptr;

    strcpy(str, data.c_str());

    //shm_mutex.lock();

    sem_post(sem);

    //shm_mutex.unlock();
    //shmctl(shmid,SHM_UNLOCK,NULL);
}

string get (int shmid, void* ptr) {

    //int shmid = shmget(key,1024,0666);

    //shm_mutex.lock();

    //shmctl(shmid,SHM_LOCK,NULL);

    sem_wait(sem);

    //shm_mutex.unlock();

    char *str = (char*) ptr;
    string temp(str);

    //shm_mutex.lock();

    sem_post(sem);

    //shmctl(shmid,SHM_UNLOCK,NULL);

    //shm_mutex.unlock();

    return temp;

}

void clean(int key, void* ptr) {

    shmdt(ptr);

    int shmid = shmget(key,1024,0666|IPC_CREAT);
    shmctl(shmid,IPC_RMID,NULL);
}

void multiple_writes() {
    int shmid;
    void* ptr = setup(SHM_KEY, &shmid);

    int val;

    cout << "writes " << sem_getvalue(sem, &val) << endl;

    string temp;

    for (int i = 0; i < MAX; i++) {
        set(shmid, ptr, data[i%5]);
        //cout << "here" << endl;
    }

    cout << "writes" << endl;
    cout << data[4] << endl;
    //cout << get(shmid, ptr) << endl;

    clean(SHM_KEY, ptr);

}


void multiple_reads(vector<string>& ans) {
    int shmid;
    void* ptr = setup(SHM_KEY, &shmid);

    int val;

    cout << "reads " << sem_getvalue(sem, &val) << endl;

    string temp;

    for (int i = 0; i < MAX; i++) {
        ans[i] = get(shmid, ptr);
    }

    //cout << temp << endl;

    clean(SHM_KEY, ptr);

}

int main()
{

    cout << sem_unlink(SNAME) << endl;

    sem = sem_open(SNAME, O_CREAT, 0777, 1);

    if (sem == SEM_FAILED) {
        cout << "Semaphore can't be opened" << endl;
        exit(1);
    }

    int val;

    sem_getvalue(sem, &val);

    cout << val << endl;

    clock_t t;
    t = clock();

    //multiple_writes();
    //cout << "written" << endl;
    //multiple_reads();

    vector<string> ans(MAX);

    std::thread t1 (multiple_writes);
    //usleep(20000);
    std::thread t2 (multiple_reads, std::ref(ans));

    t1.join();
    t2.join();

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    //cout << temp << endl;
    cout << time_taken << endl;

    cout << ans[0] << endl;

    bool valid = false;

    for (int i = 0; i < ans.size(); i++) {
        valid = false;
        for (int j = 0; j < data.size(); j++) {
            if (ans[i] == data[j]) {
                valid = true;
            }
        }
        if (!valid) {
            cout << "Failed: " << ans[i] << endl;
            return 1;
        }
    }

    cout << sem_close(sem) << endl;

    cout << sem_unlink(SNAME) << endl;

    //clean(SHM_KEY, ptr);

    return 0;
}
