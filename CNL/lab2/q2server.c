#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <stdlib.h>
#include <pthread.h> // for threading
#include <limits.h>
#define PORTNO 10500

// Function to perform arithmetic operations
int performOperation(int num1, int num2, char operator) {
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0)
                return num1 / num2;
            else
                return INT_MAX; // Handle division by zero
        default:
            return INT_MAX; // Invalid operator
    }
}

void *clientHandler(void *socket_desc) {
    int newsockfd = *(int *)socket_desc;
    int num1, num2, result;
    char operator;

    // Read operands and operator from the client
    read(newsockfd, &num1, sizeof(num1));
    read(newsockfd, &num2, sizeof(num2));
    read(newsockfd, &operator, sizeof(operator));

    // Perform the arithmetic operation
    result = performOperation(num1, num2, operator);

    // Send the result back to the client
    write(newsockfd, &result, sizeof(result));

    close(newsockfd);
    pthread_exit(NULL);
}

int main() {
    int sockfd, newsockfd, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    pthread_t thread_id;

    // Create an unnamed socket for the server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Name the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    // Create a connection queue and wait for clients
    listen(sockfd, 5);
    printf("Server waiting for connections...\n");

    while (1) {
        // Accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        if (pthread_create(&thread_id, NULL, clientHandler, (void *)&newsockfd) < 0) {
            perror("Could not create thread");
            return 1;
        }
    }

    close(sockfd);
    return 0;
}
