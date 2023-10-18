/*Q1. Write a program to print the lines of a file that contain a word given as the program
argument (a simple version of grep UNIX utility)*/
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char const *argv[]){
    int sfd,i=0,k=0;
    char ch[100], chr;
    if(argc!=3){
        printf("\nInsufficient Arguments\n");
        exit(1);
    }
    if((sfd=open(argv[2],O_RDONLY)) == -1){
        printf("File not found.\n");
        exit(2);
    }
    while((read(sfd, &chr, 1)) > 0){
        if(chr != '\n'){
            ch[i++] = chr;
        } else{
            k++;
            ch[i] = '\0';
            i=0;
            if(strstr(ch,argv[1]) != NULL){
                printf("Line : %d\t %s\n",k,ch);
            }
        }
    }
    exit(0);
}


// --->OUTPUT:PS D:\5th Sem\OS Lab> ./LAB1 love sample.txt
// Line : 3         I really love the Windows Operating System.


/*2. Write a program to list the files given as arguments, stopping every 20 lines until a
key is hit. (a simple version of more UNIX utility)*/
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[]){
    int sfd, sfd2, i=0, k=0, p=0;
    char ch[100], ch2[100], chr;


    if(argc != 3){
        printf("\nInsufficient Arguments\n");
        exit(1);
    }
    if((sfd = open(argv[1],O_RDONLY)) == -1){
        printf("File not found!\n");
        exit(2);
    }
    while((read(sfd, &chr, 1)) > 0){
        if(chr != '\n'){
            ch[i++] = chr;
        } else{
            k++;
            p++;
            ch[i] = '\0';
            i=0;
            printf("Line : %d\t %s\n",p,ch);
            if(k == 20){
                fgetc(stdin);
                k=0;
            }
        }
    }
    close(sfd);


    if((sfd2 = open(argv[2],O_RDONLY)) == -1){
        printf("File not found!\n");
        exit(2);
    }
    p=0;
    while((read(sfd2, &chr, 1)) > 0){
        if(chr != '\n'){
            ch2[i++] = chr;
        } else{
            k++;
            p++;
            ch[i] = '\0';
            i=0;
            printf("Line : %d\t %s\n",p,ch2);
            if(k == 20){
                fgetc(stdin);
                k=0;
            }
        }
    }
    exit(0);
}


// -->OUTPUT:PS D:\5th Sem\OS Lab> ./LAB1 sample.txt sample2.txt


/*3. Demonstrate the use of different conversion specifiers and resulting output to
allow the items to be printed.*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


//extern int errno


int main(){
    int a = 18;
    float b = 9.69;
    char c = 'F';
    char str[] = "Ayush Goyal";
    printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n",a,b,c,str,a);
    errno = EPERM;
    printf("Error Access Number : %m\n");
}
// -->OUTPUT:a = 18, b = 9.690000, c = F, str = Ayush Goyal, Hexadecimal for a = 12
// Error Access Number : m


/*4. Write a program to copy character-by character copy is accomplished using calls to the
functions referenced in stdio.h*/
#include<stdio.h>
#include <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
    char c;
    int in,out;
    char buffer[128];
    int nread;
    if(argc!=3){
        printf("\nInsufficient Arguments\n");
        exit(1);
    }
    in=open(argv[1],O_RDWR);
    out=open(argv[2],O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    if( in==-1 || out==-1){
        printf("File not found\n");
        exit(1);
    }
    while(read(in,&c,1) == 1){
        write(out,&c,1);
    }
    printf("Contents of file copied\n");
    exit(0);
}


---------------------------------------------------------------------------------------------------
2.
/* 1. Write a C program to emulate the ls -l UNIX command that prints all files in a
 current directory and lists access privileges, etc. DO NOT simply exec ls -l from the
 program. */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>


char const *perms(__mode_t mode){
    static char local_buff[16] = {0};
    int i = 0;
    //user permissions
    local_buff[i++] = ((mode & S_IRUSR) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWUSR) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXUSR) ? 'x' : '-');
    //group permissions
    local_buff[i++] = ((mode & S_IRGRP) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWGRP) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXGRP) ? 'x' : '-');
    //other permissions
    local_buff[i++] = ((mode & S_IROTH) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWOTH) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXOTH) ? 'x' : '-');


    return local_buff;
}


int main(int argc, char *argv[]){
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    if(argc == 1)
        mydir = opendir(".");
    else
        mydir = opendir(argv[1]);
   
    while((myfile = readdir(mydir)) != NULL){
        bzero(&mystat, sizeof(mystat));
        stat(myfile->d_name, &mystat);
        printf("%10.10s", perms(mystat.st_mode));
        printf("\t%d", mystat.st_uid);
        printf("\t%ld\t",mystat.st_size);
        printf("%s\t", ctime(&mystat.st_mtime));
        printf("%s\n", myfile->d_name);
    }
    closedir(mydir);
}


// 2. Write a program that will list all files in a current directory and all files in
// subsequent subdirectories.
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>


void executeFunc(char* dir, int depth){
    struct dirent *myfile;
    struct stat mystat;
    DIR *mydir = opendir(dir);
    chdir(dir);
    while((myfile = readdir(mydir)) != NULL){
        bzero(&mystat, sizeof(mystat));
        stat(myfile->d_name, &mystat);
        for(int i=0;i<depth;i++)
            printf(" ");
        printf("%s", myfile->d_name);
        if(S_ISDIR(mystat.st_mode))
            printf("/");
        printf("\n");
        if(S_ISDIR(mystat.st_mode) && strcmp(myfile->d_name, ".") != 0 && strcmp(myfile->d_name, "..") != 0){
            executeFunc(myfile->d_name, depth+1);
        }
    }
    chdir("..");
    closedir(mydir);
}


int main(){
    executeFunc(".", 0);
    return 0;
}


// 1. Write a program that will only list subdirectories in alphabetical order.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>


int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }
   
    DIR *dir_ptr = opendir(argv[1]);
    if (dir_ptr == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", argv[1]);
        return 1;
    }
   
    struct dirent *entry;
    char *subdirs[100]; // Adjust the size as needed
   
    int subdir_count = 0;
   
    while ((entry = readdir(dir_ptr)) != NULL) {
        if (is_directory(entry->d_name) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            subdirs[subdir_count] = strdup(entry->d_name);
            subdir_count++;
        }
    }
   
    qsort(subdirs, subdir_count, sizeof(char *), compare_strings);
   
    for (int i = 0; i < subdir_count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }
   
    closedir(dir_ptr);
   
    return 0;
}


// 2. Write a program that allows the user to remove any or all of the files in a current
// working directory. The name of the file should appear followed by a prompt as to
// whether it should be removed.
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void printFiles(char* dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp=opendir(dir);
    if(!dp)
    {
        printf("Cannot open directory : %s\n",dir);
        exit(0);
    }
    chdir(dir);
    char c;
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(!S_ISDIR(statbuf.st_mode))
        {
            printf("Do you want to remove the file (Y|N) : %s\n",entry->d_name);
            scanf(" %c",&c);
            if(c=='Y'||c=='y')
            {
                remove(entry->d_name);
            }
        }
    }
    chdir("..");
}


void main()
{
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s",dir);
    printFiles(dir);
}
--------------------------------------------------------------------------------------------
3.
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


--------------------------------------------------------------------------------------
4.
// 1. Write a program to find the inode number of an existing file in a directory. Take the
// input as a filename and print the inode number of the file.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


void main() {
    char fileName[100];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    printf("Inode: %ld\n", fileStat.st_ino);
}


// 2. Write a program to print out the complete stat structure of a file.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>


void main() {
    char fileName[100], timeStr[32], fileMode[11];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    time_t t = fileStat.st_atime;
    struct tm * timeStamp = localtime(&t);
    strftime(timeStr, sizeof(timeStr), "%a %Y-%m-%d %H:%M:%S", timeStamp);
    fileMode[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
    fileMode[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    fileMode[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    fileMode[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    fileMode[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    fileMode[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    fileMode[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    fileMode[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    fileMode[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    fileMode[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    fileMode[10] = '\0';
    printf("Device ID: %ld\nFile Serial No: %ld\nMode of file: %s\nNo. of hard links: %ld\nTime of last access: %s\n", fileStat.st_dev, fileStat.st_ino, fileMode, fileStat.st_nlink, timeStr);
}


// 3. Write a program to create a new hard link to an existing file and unlink the same.
// Accept the old path as input and print the newpath.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


void main() {



    char oldPath[100], newPath[100];
    printf("Enter old path ");
    scanf("%s", oldPath); //    /home/student/210905100/Lab4/temp1/temp.txt
    printf("Enter new path "); //    /home/student/210905100/Lab4/temp2/temp.txt
    scanf("%s", newPath);
    int res = link(oldPath, newPath);
    if (res == 0) {
        res = unlink(oldPath);
        if (res == 0)
            printf("New path to the file: %s\n", newPath);
        else
            printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}


/*Output: ./q3
Enter old path /home/student/210905100/Lab4/temp1/temp.txt
Enter new path /home/student/210905100/Lab4/temp2/temp.txt
New path to the file: /home/student/210905100/Lab4/temp2/temp.txt
*/



// 4. Write a program to create a new soft link to an existing file and unlink the same.
// Accept the old path as input and print the newpath.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


void main() {


   
    char oldPath[100], newPath[100];
    printf("Enter old path ");
    scanf("%s", oldPath); //    /home/student/210905100/Lab4/temp1/temp.txt
    printf("Enter new path "); //   /home/student/210905100/Lab4/temp2/temp.txt
    scanf("%s", newPath);
    int res = symlink(oldPath, newPath);
    if (res == 0) {
        printf("Symbolic link created\n");


        // res = unlink(oldPath);
        // if (res != 0)
        //     printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}
----------------------------------------------------------------------------------------
8.
// 1. Write a multithreaded program that generates the Fibonacci series. The program
// should work as follows: The user will enter on the command line the number of
// Fibonacci numbers that the program is to generate. The program then will create a
// separate thread that will generate the Fibonacci numbers, placing the sequence in
// data that is shared by the threads (an array is probably the most convenient data
// structure). When the thread finishes execution the parent will output the sequence
// generated by the child thread. Because the parent thread cannot begin outputting the
// Fibonacci sequence until the child thread finishes, this will require having the parent
// thread wait for the child thread to finish.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* generate_fibonacci(void* param){
    int* arr=(int*)param;
    int n=arr[0];
    arr[1]=0;
    arr[2]=1;
    for(int i=3;i<=n;i++){
        arr[i]=arr[i-1]+arr[i-2];
    }
    return NULL;
}


int main(int argc, char const *argv[]){
    int n;
    printf("Enter number of fibonacci numbers:\n");
    scanf("%d",&n);
    int* arr=(int*)malloc((n+1)*sizeof(int));
    arr[0]=n;
    pthread_t thread;
    pthread_create(&thread,0,&generate_fibonacci,(void*)arr);
    pthread_join(thread,0);
    for(int i=1;i<=n;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
    return 0;
}


// 2. Write a multithreaded program that calculates the summation of non-negative
// integers in a separate thread and passes the result to the main thread.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* summation(void* param){
    int* arr=(int*)param;
    int sum=0;
    int n=arr[0];
    for(int i=1;i<=n;i++){
        if(arr[i]>0){
            sum+=arr[i];
        }
    }
    return (void*)sum;
}


int main(int argc,char const *argv[]){
    int n;
    printf("Enter the number of numbers:\n");
    scanf("%d",&n);
    int* arr=(int*)malloc((n+1)*sizeof(int));
    arr[0]=n;
    printf("Enter the numbers:\n");
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    int answer=0;
    pthread_t thread;
    pthread_create(&thread,0,&summation,(void*)arr);
    pthread_join(thread,(void**)&answer);
    printf("Summation of non-negative numbers:%d\n",answer);
    return 0;
}


// 3. Write a multithreaded program for generating prime numbers from a given starting
// number to the given ending number.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
void *prime(int *arr)
{
    int n1 = arr[1];
    int n2 = arr[2];
    printf("The Prime Numbers between '%d' and '%d' are: \n", n1, n2);
    for (int i = n1; i <= n2; i++)
    {
        int flag = 0;
        for (int j = 2; j <= i / 2; j++)
        {
            if ((i % j) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
            printf("%d ", i);
    }
    printf("\n");
}
int main()
{
    int arr[2];
    printf("Enter the Lower Limit: \n");
    scanf("%d", &arr[1]);
    printf("Enter the Upper Limit: \n");
    scanf("%d", &arr[2]);
    pthread_t thread;
    pthread_create(&thread, 0, &prime, (void *)arr);
    pthread_join(thread, NULL);
}


// 4. Write a multithreaded program that performs the sum of even numbers and odd
// numbers in an input array. Create a separate thread to perform the sum of even
// numbers and odd numbers. The parent thread has to wait until both the threads are
// done.



#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


void* add_odd(void* args){
    int *arr = (int*)args;
    int n = arr[0];
    int *res = (int*)malloc(sizeof(int));
    *res = 0;
    for(int i=1;i<=n;i++){
        if(arr[i] %2== 1)
            *res += arr[i];
    }
    return (void*)res;
}


void* add_even(void* args){
    int *arr = (int*)args;
    int n = arr[0];
    int *res = (int*)malloc(sizeof(int));
    *res = 0;
    for(int i=1;i<=n;i++){
        if((arr[i] %2==0))
            *res += arr[i];
    }
    return (void*)res;
}


int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Not enough arguments!\n");
        exit(EXIT_FAILURE);
    }
    int n = argc - 1;
    int* arr = (int*)calloc(n+1, sizeof(int)), *resEven, *resOdd;
    arr[0] = n;
    for(int i=0;i<n;i++){
        arr[i+1] = atoi(argv[i+1]);
    }
    pthread_t threadOdd, threadEven;
    pthread_create(&threadOdd, 0, &add_odd, (void*)arr);
    pthread_create(&threadEven, 0, &add_even, (void*)arr);
    pthread_join(threadOdd, (void**)&resOdd);
    pthread_join(threadEven, (void**)&resEven);
    printf("The Sum of Odd numbers is: %d\n", *resOdd);
    printf("The Sum of Even numbers is: %d\n", *resEven);
    return 0;
}


-------------------------------------------------------------------------------------
5.
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


