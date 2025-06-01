#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main(int argc, char* argv[]) {
    // filling address struct
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));  // Обнуляем структуру
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    // socket creation
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket...");
        exit(EXIT_FAILURE);
    }

    // socket binding
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // socket listening
    if (listen(server_socket, 5) < 0) {
        perror("Failed to listen socket...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // main server loop
    while (1) {
        // accepting connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Failed to accept connection...");
            continue;  // Продолжаем работу после ошибки
        }

        printf("Client connected!\n");

        // receiving data
        char buffer[BUFFER_SIZE] = {0};
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received < 0) {
            perror("Failed to receive data");
        } else {
            buffer[bytes_received] = '\0';
            printf("Received: %s\n", buffer);  // Выводим всё сообщение
        }

        // closing client socket
        close(client_socket);
    }

    // closing server socket (эта часть кода никогда не выполнится в текущей реализации)
    close(server_socket);
    return EXIT_SUCCESS;
}
