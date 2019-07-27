#include "process.h"

sem_t* sem;

const vector<string> data_to_write{"abcde", "fghij", "klmno", "pqrst", "uvwxy"};

void* setup(int key, int* shmid) {
    sem = sem_open(SNAME, O_CREAT, 0777, 1);
    *shmid = shmget(SHM_KEY,1024,0666|IPC_CREAT);

    if (*shmid == -1)
        return NULL;

    return shmat(*shmid,(void*)0,0);
}

void set(int shmid, void* ptr, string in) {

    sem_wait(sem);

    char *str = (char*) ptr;
    strcpy(str, in.c_str());

    sem_post(sem);

}

string get (int shmid, void* ptr) {

    sem_wait(sem);

    char *str = (char*) ptr;

    if (strcmp(str, "") == 0) {
        //cout << "came hhere" << endl;
        sem_post(sem);
        return "";
    }

    string temp(str);

    sem_post(sem);

    return temp;

}

void clean(int key, void* ptr) {

    sem_close(sem);
    sem_unlink(SNAME);

    shmdt(ptr);

    int shmid = shmget(key,1024,0666|IPC_CREAT);
    shmctl(shmid,IPC_RMID,NULL);
}
