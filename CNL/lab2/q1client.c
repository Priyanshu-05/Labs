#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    int arr[10]; // Assuming an array of maximum size 10
    int size;

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.58.74");
    address.sin_port = htons(10500);
    len = sizeof(address);

    // Connect your socket to the server’s socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    printf("\nEnter the size of the integer array (max 10): ");
    scanf("%d", &size);

    printf("Enter the integer array elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Send the integer array to the server
    write(sockfd, &size, sizeof(size));
    write(sockfd, arr, size * sizeof(int));

    // Receive and display the sorted array and process ID from the server
    read(sockfd, arr, size * sizeof(int));
    int serverProcessID;
    read(sockfd, &serverProcessID, sizeof(serverProcessID));

    printf("Received sorted array from server (process ID: %d): ", serverProcessID);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}
