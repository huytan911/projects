#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));

    bind(receiver, (struct sockaddr *)&addr, sizeof(addr));

    char buf[4][256];
    struct sockaddr_in sender_addr;
    int sender_addr_len = sizeof(sender_addr);
    
    while (1)
    {
        int ret = recvfrom(receiver, buf, sizeof(buf), 0,
                           (struct sockaddr *)&sender_addr, &sender_addr_len);
        time_t now = time(0);
        char time[80];
        strftime(time, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));
        FILE *f = fopen(argv[2], "a");
        char sv[2048];
        sprintf(sv, "%s %s %s %s %s %s", inet_ntoa(sender_addr.sin_addr), time, buf[0], buf[1], buf[2], buf[3]);
        fprintf(f, "%s", sv);
        printf("%s", sv);
        fclose(f);
    }
    close(receiver);
}