#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Server nhan file tu client

int main(int argc, char *argv[])
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(atoi(argv[1]));

    if (bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    char buf[2048];
    unsigned int clientAddrLen = sizeof(clientAddr);

    FILE *f1 = fopen(argv[2], "r");
    char hello_buf[2048];
    fgets(hello_buf, 2048, f1);
    fclose(f1);
    int connSock = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (connSock > 0)
    {
        printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        send(connSock, hello_buf, strlen(hello_buf), 0);
    }

    int ret1;
    
    while (1)
    {
        FILE *f2 = fopen(argv[3], "a");
        ret1 = recv(connSock, buf, 2048, 0);
        if (ret1 < 0)
            break;
        buf[ret1] = '\0';
        fprintf(f2, "%s", buf);
        fclose(f2);
    }

    
    close(connSock);
    close(listener);
}