#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "arp.h"

int main()
{
    unsigned char srcIp[] = {};
    unsigned char srcMac[]= {};
    unsigned char disIp[] = {};

    struct arp_frame arpFrame;
    struct sockaddr sockAddr;

    memset(&arpFrame, 0, sizeof(struct arp_frame));
    memset(&sockAddr, 0, sizeof(struct sockaddr));

    send_arp(&arpFrame, (void *)srcIp, 4, (void *)srcMac, 6, disIp, &sockAddr);

    printf("hello word! \n");

    return 0;
}