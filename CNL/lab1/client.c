#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
void encryptMessage(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] += 4;
    }
}
int main()
{
int len,result,sockfd,n=1;
struct sockaddr_in address;
char ch[256],buf[256];
//Create a socket for the client
sockfd = socket(AF_INET, SOCK_STREAM, 0);
//Name the socket as agreed with the server
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("172.16.58.127"); 
address.sin_port=htons(10200);
len = sizeof(address);
//Connect your socket to the server’s socket
result=connect(sockfd,(struct sockaddr *)&address,len);
if(result==-1)
{
perror("\nCLIENT ERROR");
exit(1);
}// Read input from the user
    printf("Enter a string to encrypt: ");
    fgets(ch, sizeof(ch), stdin);
    ch[strlen(ch) - 1] = '\0'; // Remove the newline character from fgets input

    // Encrypt the message
    encryptMessage(ch);

    // Send the encrypted string to the server
    write(sockfd, ch, strlen(ch));

    // Read and display the decrypted string from the server
    printf("Encrypted message sent to the server: %s\n", ch);
    n = read(sockfd, buf, sizeof(buf));
    buf[n] = '\0';

    printf("Decrypted message received from the server: %s\n", buf);

    close(sockfd);
    return 0;

}