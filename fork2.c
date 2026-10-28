#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include<stdlib.h>
int main(){
    
    pid_t p =fork();
    if(p<0){
        perror("fork fail");
        exit(1);
    }
    fork();
    fork();
    fork();
   
    printf("Hello world!,process_id(pid) =%d \n",getpid());
    return 0;
}