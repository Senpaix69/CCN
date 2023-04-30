#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    // variables
    int server_fd;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE] = {};

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

    // step2: binding sockets
    if (bind(server_fd, (const struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Socket binding failed\n");
        exit(EXIT_FAILURE);
    }

    // read write
    unsigned int len = sizeof(client);
    while (1)
    {
        printf("waiting for data...\n");
        recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &len);
        printf("Recieved from client: %s\n", buffer);
        int lenBuffer = strlen(buffer);

        char find = buffer[lenBuffer - 1];
        printf("To find: %c\n", find);
        if (find >= 'A' && find <= 'Z')
            find += 32;

        buffer[lenBuffer - 1] = '\0';
        buffer[lenBuffer - 2] = '\0';
        lenBuffer -= 2;

        printf("From word: %s\n", buffer);

        int freq = 0;
        for (int i = 0; i < lenBuffer; i++)
        {
            if (buffer[i] >= 'A' && buffer[i] <= 'Z')
                buffer[i] += 32;
            if (find == buffer[i])
                freq++;
        }
        printf("Frequency of '%c' in '%s' is: %d\n\n", find, buffer, freq);
        memset(buffer, 0, BUFFER_SIZE);
    }

    return 0;
}

/*
    data manipulation steps
    recieved: Senpai S
    toFind: S
    Word: Senpai

    toFind = lastCharacter
    bufflenght--; for last character
    bufflenght--; for white space
*/