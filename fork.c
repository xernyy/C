//Using fork() system call create a process and print the id of the child process and the parent process. 

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int pid = fork();

    while(pid==0){
        printf("The parent's process ID is %d. The child's process ID is %d. \n", getppid(), getpid());
        break;
    }
}
