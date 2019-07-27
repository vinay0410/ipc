/* file : process.i */
  
/* name of module to use*/
%module ipc_process
%{ 
    /* Every thing in this file is being copied in  
     wrapper file. We include the C header file necessary 
     to compile the interface */
    #include "process.h" 
 
%} 
  
/* explicitly list functions and variables to be interfaced */
void set(int shmid, void* ptr, string in);
string get(int shmid, void* ptr);
void clean(int key, void* ptr);
void* setup(int key, int* shmid); 
