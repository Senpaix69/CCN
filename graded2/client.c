#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Too few arguments\nFormat: ./a.out communication c\n");
        return -1;
    }
    char *word = argv[1];
    char ch = argv[2][0];

    char message[100] = {};
    strcpy(message, word);
    int len = strlen(message);
    message[len] = ' ';
    message[len + 1] = ch;

    // variables
    int server_fd;
    struct sockaddr_in server;

    // step1: socket create
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    // step1.1: setup server(family, port, addr)
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // read write
    sendto(server_fd, message, strlen(message), 0, (const struct sockaddr *)&server, sizeof(server));
    printf("Message send\n");

    return 0;
}