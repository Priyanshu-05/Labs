#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define PORTNO 10500

int main() {
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    int num1, num2, result_server;
    char operator;

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.58.74"); // Localhost
    address.sin_port = htons(PORTNO);
    len = sizeof(address);

    // Connect your socket to the server's socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    // Input two integers and an operator from the user
    printf("Enter the first integer: ");
    scanf("%d", &num1);
    printf("Enter the second integer: ");
    scanf("%d", &num2);
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    // Send operands and operator to the server
    write(sockfd, &num1, sizeof(num1));
    write(sockfd, &num2, sizeof(num2));
    write(sockfd, &operator, sizeof(operator));

    // Receive and display the result from the server
    read(sockfd, &result_server, sizeof(result_server));
    printf("Result received from server: %d\n", result_server);

    close(sockfd);
    return 0;
}
