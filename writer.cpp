#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unordered_set>
using namespace std; 
  
#define SHM_KEY 1234

int main() 
{ 
    // ftok to generate unique key 
    //key_t key = ftok("shmfile",65); 
  
    //cout << key << endl;

    // shmget returns an identifier in shmid 
    int shmid = shmget(SHM_KEY,1024,0666|IPC_CREAT); 
  
    //cout << shmid << endl;

    // shmat to attach to shared memory 
    
    clock_t t;
    t = clock();
    
    void *str1;

    for (int i = 0; i < 100000; i++) {
        str1 = shmat(shmid,(void*)0,0);
    } 

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    cout << "Time Taken by Reader: " << time_taken << endl;
  
    cout << str1 << endl;

    unordered_set<string> data;

    data.insert("abcd");
    data.insert("efgh");
    data.insert("ijkl");
    data.insert("mnop");

    t = clock();

    for (int i = 0; i < 100000; i++) {
         data.find("abcd");
    }

    t = clock() - t;

    time_taken = ((double)t)/CLOCKS_PER_SEC;    
    cout << "Time Taken by MAp: " << time_taken << endl;

    t = clock();

    void* str2 = shmat(shmid, (void*)0, 0);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    cout << "Time Taken by Reader: " << time_taken << endl;

    cout << str2 << endl;

    t = clock();

    void* str3 = shmat(shmid, (void*)0, 0);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    cout << "Time Taken by Reader: " << time_taken << endl;

    cout << str3 << endl;

    cout<<"Write Data : "; 
    cin >> (char*) str1; 
  
    string temp;

    printf("Data written in memory: %s\n",(char*) str1); 
    printf("Data written in memory: %s\n",(char*) str2);
    printf("Data written in memory: %s\n",(char*) str3); 

    cin >> temp;

    //detach from shared memory  
    shmdt(str1);
    shmdt(str2); 
    shmdt(str3);

    return 0; 
} 
