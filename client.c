
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char* argv[]) {
    // filling address struct
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // socket desriptor
    int network_socket;

    // connecting socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) {
        perror("Failed to connect socket...");
        exit(EXIT_FAILURE);
    }

    // connecting to server
    if (connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to connect to server...");
        close(network_socket);
        exit(EXIT_FAILURE);
    }

    // sending information
    char message[256] = "Богосьян Алик Альбертович KKSO-26-24 1 kurs";
    send(network_socket, message, strlen(message), 0);

    // then close the socket
    close(network_socket);

    return EXIT_SUCCESS;
}
