#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    char buf[4][256];
    while (1)
    {
        printf("Ho va ten: ");
        fgets(buf[0], 256, stdin);
        strtok(buf[0], "\n");

        printf("MSSV: ");
        fgets(buf[1], 256, stdin);
        strtok(buf[1], "\n");

        printf("Ngay sinh: ");
        fgets(buf[2], 256, stdin);
        strtok(buf[2], "\n");

        printf("CPA: ");
        fgets(buf[3], 256, stdin);

        int ret = sendto(sender, buf, sizeof(buf), 0,
            (struct sockaddr *)&addr, sizeof(addr));
    }
    close(sender);
}