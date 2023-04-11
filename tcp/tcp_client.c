#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Client gửi file sang server

int main(int argc, char *argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    int ret1 = connect(client, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret1 == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[2048];
    int ret2, messLen;
    ret2 = recv(client, buf, sizeof(buf), 0);
    printf("%s", buf);
    while (1)
    {
        printf("Send to server: ");
        fgets(buf, 2048, stdin);
        messLen = strlen(buf);
        if(messLen == 0)
            break;
        ret2 = send(client, buf, messLen, 0);
        if(ret2 <= 0)
            break;
    }

    close(client);
}