#include "process.h"

void multiple_writes() {
    int shmid;
    void* ptr = setup(SHM_KEY, &shmid);

    int val;

    string temp;

    for (int i = 0; i < MAX; i++) {
        set(shmid, ptr, data_to_write[i%5]);
        //cout << "here" << endl;
    }

    cout << "writes" << endl;
    cout << data_to_write[4] << endl;
    //cout << get(shmid, ptr) << endl;

    clean(SHM_KEY, ptr);

}

int main() {

    clock_t t;
    t = clock();

    multiple_writes();

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;


    cout << "Time Taken in Writes: " << time_taken << endl;

}