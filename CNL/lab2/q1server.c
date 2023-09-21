#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // Added for getpid()
#include <stdlib.h>

#define PORTNO 10500

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int sockfd, newsockfd, portno, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    int size, arr[10]; // Assuming an array of maximum size 10

    // Create an unnamed socket for the server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Name the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.58.74");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    // Create a connection queue and wait for clients
    listen(sockfd, 5);
    while (1) {
        char buf[256];
        printf("\nServer waiting\n");

        // Accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        // Read the integer array size and elements from the client
        read(newsockfd, &size, sizeof(size));
        read(newsockfd, arr, size * sizeof(int));

        // Sort the integer array
        insertionSort(arr, size);

        // Send the sorted array and process ID back to the client
        write(newsockfd, arr, size * sizeof(int));
        int serverProcessID = getpid();
        write(newsockfd, &serverProcessID, sizeof(serverProcessID));

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
