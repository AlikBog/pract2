#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"  

int main(int argc, char* argv[]) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address)); 
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    int network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) {
        perror("Failed to create socket...");
        exit(EXIT_FAILURE);
    }

    if (connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to connect to server...");
        close(network_socket);
        exit(EXIT_FAILURE);
    }

    // sending information
    char message[] = "Богосьян Алик Альбертович ККСО-26-24";
    size_t bytes_sent = send(network_socket, message, strlen(message), 0);

    if (bytes_sent < 0) {
        perror("Failed to send message");
    }
    else {
        printf("Message sent successfully: %s\n", message);
    }

    // close the socket
    close(network_socket);

    return EXIT_SUCCESS;
}
