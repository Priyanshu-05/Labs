#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 10200
int main(){
    int sockfd,newsockfd,clilen,n=1,portno;
    struct sockaddr_in cliaddr,seraddr;
    char buf[256];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr=inet_addr("343.343.4343.343");
    seraddr.sin_port=htons(PORTNO);
    bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(sockfd,5);
    printf("server waiting\n");
    while(1){
        clilen=sizeof(cliaddr);
        newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
        n=read(sockfd,buf,sizeof(buf));
        printf("decrypted message\n");
        for(int i=0;i<strlen(buf);i++){
            printf("%c",(buf[i]-4));
        }
        printf("Encrypted message %s\n",buf);
        n=write(newsockfd,buf,sizeof(buf));
    }
}