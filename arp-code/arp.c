#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>     //struct ifreq
#include <sys/ioctl.h>
#include <sys/types.h>  //socket
#include <sys/socket.h>
#include <unistd.h>
#include <net/ethernet.h> // ETH_P_ARP
#include <linux/if_packet.h>
#include <stdio.h>

#include "arp.h"

#define ARP_STYLE       0x0806
#define ARP_ETHER       1
#define ARPHDR_STYLE    0x0800

static u8 DST_Mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//static u8 SRC_Mac[] = {xx,xx,xx,xx,xx,xx,xx};
//static u8 SRC_IP[] = {192, 168, 1, 1}; 




// pad the struct  
void pad_struct(struct arp_frame *arpFrame, void *srcIp, void *srcMac, void *dstIp)
{
    memset(arpFrame, 0, sizeof(struct arp_frame));
    // pad ethernet heade
    memcpy(arpFrame->Eheader.DST, DST_Mac, 6);
    memcpy(arpFrame->Eheader.SRC, srcMac, 6);
    arpFrame->Eheader.LS = htons(ARP_STYLE);

    // pad arp heade
    arpFrame->Aheader.ar_hrd = htons(ARP_ETHER);
    arpFrame->Aheader.ar_pro = htons(ARPHDR_STYLE);
    arpFrame->Aheader.ar_hln = 6;
    arpFrame->Aheader.ar_pln = 4;
    arpFrame->Aheader.ar_op = 1;

    // pad arp body
    memcpy(arpFrame->Abody.arp_shr, srcMac, 6);
    memcpy(arpFrame->Abody.arp_sip, srcIp, 4);
    memcpy(arpFrame->Abody.arp_dip, dstIp, 4);
}


// send arp
int send_arp(struct arp_frame *arpFrame, void *srcIp, int ipLen, void *srcMac, int macLen, unsigned char *dstIp, const struct sockaddr *desAddr)
{
    int sockFd;
    int i = 0;
    unsigned char ifname[] = "eth0";
    struct sockaddr_ll to;
    unsigned char tempDstIp[4];

    memcpy(tempDstIp, dstIp, 3);
    sockFd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));  
    if(-1 == sockFd){
        printf("in send_arp socket creating is false\n");
        return -1;
    }

    // pad struct sockaddr_ll structure
    to.sll_family = AF_PACKET;
    to.sll_protocol = htons(ETH_P_ARP);
    to.sll_ifindex = if_nametoindex(ifname);

    bind(sockFd, (struct sockaddr *)&to, sizeof(to));

    for(i=0; i<255; i++){
        tempDstIp[3] = i;
        pad_struct(arpFrame, srcIp, srcMac, tempDstIp);
        if(sendto(sockFd,arpFrame,sizeof(struct arp_frame),0,(struct sockaddr *)&to,sizeof(to))<0){
            printf("sendto is false\n");
            return -1;
        }
        printf("send arp %d\n", i);
        sleep(2);
    }

    return 0;
}

// receive arp  
int receive_arp(int socketFd, struct arp_frame *arpFrame, struct sockaddr_ll *llStruct)
{
    recvfrom(socketFd, (void *)arpFrame, sizeof(struct arp_frame), 0, (struct sockaddr *)llStruct, sizeof(struct sockaddr_ll));
    return 0;
}







// get local MAC specify internet card name
int get_local_mac(char *outMac, int outLen, char *inetCardName, int nameLen)
{
    int skFd;
    struct ifreq req;       // 该结构体放在全局变量就可以使用目前不知道原因
    skFd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == skFd){
        printf("creat sock is false!\n");
        return -1;
    }

    memset(&req, 0, sizeof(req));
    strncpy(req.ifr_name, inetCardName, nameLen);
    if(ioctl(skFd, SIOCGIFHWADDR, &req) < 0){
        printf("sock ioctl is false\n");
        return -1;
    }

    memcpy(outMac, req.ifr_hwaddr.sa_data, 6);
    return 0;
}

int get_local_ip()

