#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        printf("Error creating child process!\n");
    } else if (pid == 0) {
       
        printf("Child Process: My PID is %d\n", getpid());
        sleep(10); 
        printf("Child Process: My Parent's PID was %d before becoming orphan.\n", getppid());
    } else {
      
        printf("Parent Process: My PID is %d\n", getpid());
        sleep(2); 
        printf("Parent Process: Exiting and becoming an orphan...\n");
    }

    return 0;
}
