//1. Write a C program to block a parent process until the child completes using a wait system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main()
{
    int status;
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("Error !!!\n");
    }
    else if(pid==0)
    {
        printf("Child Process \n");
        exit(0);
    }
    else
    {
        wait(&status);
        printf("Parent Process \n");
        printf("Child Process Returned : %d\n",status);
    }
}

//2. Write a C program to load the binary executable of the previous program in a child 
//process using the exec system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("Error !!!\n");
    }
    else if(pid==0)
    {
        execl("./q1","./q1",NULL);
        printf("Program 2 Child Process \n");
    }
    else
    {
        wait(NULL);
        printf("Program 2 Parent Process \n");
    }
}

//3. Write a program to create a child process. Display the process IDs of the process, 
//parent and child (if any) in both the parent and child processes.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("Error !!!\n");
    }
    else if(pid==0)
    {
        printf("Child Process ID from Child : %d\n",getpid());
        printf("Parent Process ID from Child : %d\n",getppid());
    }
    else
    {
        printf("Child Process ID from Parent : %d\n",pid);
        printf("Parent Process ID from Parent : %d\n",getpid());
    }
}

//4. Create a zombie (defunct) child process (a child with exit() call, but no 
// corresponding wait() in the sleeping parent) and allow the init process to adopt it 
// (after parent terminates). Run the process as a background process and run the “ps” 
// command
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("Error !!!\n");
    }
    else if(pid==0)
    {
        exit(0);
    }
    else
    {
        sleep(100);
        printf("Program 2 Parent Process \n");
    }
}