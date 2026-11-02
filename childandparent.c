#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

#define SHM_SIZE 1024 
int main(){
    key_t key;
    int shmid;
    char *shared_memory;
    pid_t pid;
    key = ftok(".",'x');
    if(key == -1){
        perror("flok failed");
        exit(1);
    }
    shmid = shmget(key, SHM_SIZE,IPC_CREAT|0666);
    if(shmid == -1){
        perror("shmget failed");
        exit(1);

    }
    pid = fork();
    if(pid <0){
        perror("fork failed");
        exit(1);
    }
if(pid >0){
    shared_memory = (char*)shmat(shmid,NULL,0);
if(shared_memory== (char*)-1){
    perror("Parent shmat failed");
    exit(1);
}
printf("Parent: Writing to shared memory...\n");
strcpy(shared_memory, "Hello from the Parent Process! ");
shmdt(shared_memory);
wait(NULL);
shmctl(shmid,IPC_RMID,NULL);
printf("Parent: Shared Memory Destroyed. Existing. \n");
}
else{
    sleep(1);
    shared_memory = (char*)shmat(shmid,NULL,0);
    if(shared_memory == (char*)-1){
        perror("Child shmat failed");
        exit(1);
    }
    printf("Child: Read data: \"%s\"\n", shared_memory);
        shmdt(shared_memory);
        exit(0);

}
        return 0;
}