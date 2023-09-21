#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(){
    int len,result,sockfd,n=1;
    struct sockaddr_in address;
    char ch[256], buf[256];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.58.121");
    address.sin_port=htons(10500);
    len=sizeof(address);
    result=connect(sockfd,(struct sockaddr *)&address,len);
    if(result==-1){
        perror("Client Error\n");
        exit(1);
    }
    printf("Enter string\n");
    gets(ch);
    ch[strlen(ch)]='\0';
    write(sockfd,ch,strlen(ch));
    printf("string sent back from server is:\n");
    while(n){
        n=read(sockfd,buf,sizeof(buf));
        puts(buf);
    }
}