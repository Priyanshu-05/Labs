// 1. Write a producer and consumer program in C using the FIFO queue. The producer 
// should write a set of 4 integers into the FIFO queue and the consumer should 
// display the 4 integers.
producer-
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>

#define FIFO_NAME "my_queue"
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]){
    int pipe_fd, res, open_mode = O_WRONLY, n = 0;
    char buffer[BUFFER_SIZE+1];
    if(access(FIFO_NAME, F_OK) == -1){
        res = mkfifo(FIFO_NAME, 0777);
        if(res != 0){
            fprintf(stderr, "Could not create file %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if(pipe_fd != -1){
        printf("Enter 4 numbers: \n");
        while(n<4){
            printf("%d : ", n+1);
            scanf("%s", buffer);
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            if(res == -1){
                fprintf(stderr, "Write error on PIPE\n");
                exit(EXIT_FAILURE);
            }
            n++;
        }
        close(pipe_fd);
    }
    else{
        exit(EXIT_FAILURE);
    }
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
    return 0;
}

consumer-
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>

#define FIFO_NAME "my_queue"
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]){
    int pipe_fd, res, open_mode = O_RDONLY, n = 0;
    char buffer[BUFFER_SIZE+1];
    memset(buffer, '\0', sizeof(buffer));
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    int bytes_read = 0;
    if(pipe_fd != -1){
        do{
            printf("%d : ", n+1);
            res = read(pipe_fd, buffer, BUFFER_SIZE);
            printf("%s\n", buffer);
            bytes_read += BUFFER_SIZE;
            n++;
        }while(n<4);
        close(pipe_fd);
    }
    else{
        exit(EXIT_FAILURE);
    }
    printf("Process %d finished, %d bytes read.\n", getpid(), bytes_read);
    exit(EXIT_SUCCESS);
    return 0;
}

// 2. Demonstrate creation, writing to, and reading from a pipe.
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

int main(int argc, char const *argv[]){
	int n, fd[2];
	char buf[1025], *data = "Sample Data for 6th OS Lab";
	pipe(fd);
	write(fd[1], data, strlen(data));
	n = read(fd[0], buf, 1024);
	if(n >= 0){
		buf[n] = 0;
		printf("Read %d bytes from the pipe\n\"%s\"\n", n, buf);
	}
	else
		perror("Read");
	exit(0);
}

// 3. Write a C program to implement one side of FIFO.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

#define fname "hi.txt"

void main()
{
    FILE *f1,*f2;
    pid_t pid=fork();
    if(pid==-1)
    {
        perror("Fork Error \n");
        exit(EXIT_FAILURE);
    }
    if(pid>0)
    {
        wait(NULL);
        f2=fopen(fname,"r");
        if(!f2)
        {
            perror("File Error \n");
            exit(EXIT_FAILURE);
        }
        char cc;
        while((cc=fgetc(f2))!=EOF)
        {
            printf("%c",cc);
        }
        printf("\n");
        fclose(f2);
    }
    else
    {
        f1=fopen(fname,"w+");
        if(!f1)
        {
            perror("File Error \n");
            exit(EXIT_FAILURE);
        }
        char c[256];
        printf("Enter Something : \t");
        scanf(" %s",c);
        fputs(c,f1);
        fclose(f1);
    }
    exit(EXIT_SUCCESS);
}

// 4. Write two programs, producer.c implementing a producer and consumer.c 
// implementing a consumer, that do the following:
// Your product will sit on a shelf: that is an integer - a count of the items "on the 
// shelf". This integer may never drop below 0 or rise above 5
producer-
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>
 
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1000
 
 
int main(int argc, char *argv[])
{
    int pipe_fd;
    int res;
    int open_mode=O_WRONLY;
    // int n=0;
    // char buffer[BUFFER_SIZE+1];
    int shelf_count = 5;
   
    if(access(FIFO_NAME,F_OK)==-1)
    {
        res=mkfifo(FIFO_NAME,0777);
        if(res!=0)
        {
            fprintf(stderr, "Could not create file%s\n",FIFO_NAME );
            exit(EXIT_FAILURE);    
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n",getpid());
    pipe_fd=open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);

    printf("Producer stocked the shelf with 5 items. Shelf count: %d\n", shelf_count);
    if (pipe_fd!=-1)
    {

        while (1) {
            // sleep(1);
            res=write(pipe_fd, &shelf_count, sizeof(int));
            if(res==-1)
            {
                fprintf(stderr, "Write Error on Pipe\n");
                exit(EXIT_FAILURE);
            } else if (shelf_count >= 5) {
                printf("Producer: Shelf is full. Waiting for consumer...\n");
                continue;
            }
            else {
                shelf_count--;
                printf("Producer added one item to the shelf. Shelf count: %d\n", shelf_count);
            }
    }
    }
    else
        exit(EXIT_FAILURE);
    (void)close(pipe_fd);
    
    printf("Process %d Finished\n",getpid() );
    exit(EXIT_SUCCESS);
 
}

consumer-
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>
 
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1000
 
int main(int argc, char *argv[])
{
    int pipe_fd;
    int res;
    int open_mode=O_RDONLY;
    int shelf_count = 0;

    printf("Process %d opening FIFO O_RDONLY\n",getpid());
    pipe_fd=open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);
    
    if (pipe_fd!=-1)
    {
        while (1) {
        if (shelf_count <= 0) {
            res=read(pipe_fd, &shelf_count, sizeof(int));
            printf("%d",shelf_count);
            sleep(1);
            continue;
        }

        shelf_count--;
        printf("Consumer removed one item from the shelf. Shelf count: %d\n", shelf_count);
    }
        (void)close(pipe_fd);
    }
    
    else
        exit(EXIT_FAILURE);
    
    // printf("Process %d Finished, %d bytes read\n",getpid(),n );
    exit(EXIT_SUCCESS);
}

