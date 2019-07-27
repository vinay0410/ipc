#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;


int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    //cout << key << endl;

    string data = "abdqwbeujqehujqkahwsdjkwqgherjqwabndjkgqukwjehnkqwbadxukjqwghjkkbjdklbqwuikbjklhgeujkdqwbnadsxjkbquwkgedujkqwbsdjkxhqwuikhbedjkgbqwujkasgxjkqwbeukdsgq";

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    string temp;
    // shmat to attach to shared memory
    //char *str = (char*) shmat(shmid,(void*)0,0);

    clock_t t;
    t = clock();

    for (int i = 0; i < 100000; i++) {

        char *str = (char*) shmat(shmid,(void*)0,0);

        strcpy(str, data.c_str());
        temp = std::string(str);
        //cin >> temp;
        //cout << temp << endl;
        //printf("Data written in memory: %s\n",str);

        shmdt(str);
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    cout << time_taken << endl;

    //detach from shared memory

    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}
