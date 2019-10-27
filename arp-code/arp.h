
typedef unsigned char u8;
typedef unsigned short u16;

struct ethernet_header{
    u8 DST[6];
    u8 SRC[6];
    u16 LS;
};

struct arp_header{
    u16 ar_hrd;
    u16 ar_pro;
    u8 ar_hln;
    u8 ar_pln;
    u16 ar_op;
};

struct arp_body{
    u8 arp_shr[6];  // sender mac 
    u8 arp_sip[4];  // sender ipv4 address
    u8 arp_dhr[6];  // destnation mac 
    u8 arp_dip[4];  // destnation ipv4 address
    u8 pad[18];     // pad char
    u8 FCS[4];      // FCS
};

struct arp_frame{
    struct ethernet_header Eheader;
    struct arp_header Aheader;
    struct arp_body Abody;
};

void pad_struct(struct arp_frame *arpFrame, void *srcIp, void *srcMac, void *dstIp);

int get_local_mac(char *outMac, int outLen, char *inetCardName, int nameLen);

int send_arp(struct arp_frame *arpFrame, void *srcIp, int ipLen, void *srcMac, int macLen, unsigned char *dstIp, const struct sockaddr *desAddr);






