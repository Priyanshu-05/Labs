#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORTNO 10200
void decryptMessage(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] -= 4;
    }
}
int main()
{
int sockfd,newsockfd,portno,clilen,n=1;
struct sockaddr_in seraddr,cliaddr;
int i,value;
// create an unnamed socket for the server
sockfd = socket(AF_INET,SOCK_STREAM,0);
//Name the socket
seraddr.sin_family = AF_INET;
seraddr.sin_addr.s_addr = inet_addr("172.16.58.127");// **
seraddr.sin_port = htons(PORTNO);
bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
//Create a connection queue and wait for clients
listen(sockfd,5);
while (1) {
        char buf[256];
        printf("Server waiting...\n");

        // Accept a connection
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        // Read from client
        n = read(newsockfd, buf, sizeof(buf));
        buf[n] = '\0';

        printf("Message from Client: %s\n", buf);

        // Decrypt the message
        decryptMessage(buf);

        printf("Decrypted message: %s\n", buf);

        // Send the decrypted message back to the client
        n = write(newsockfd, buf, strlen(buf));

        close(newsockfd);
        break; // Terminate after one session
    }

    close(sockfd);
    return 0;
}