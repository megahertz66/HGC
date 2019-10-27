#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>       

int get_mac(char * mac, int len_limit)   
{
    struct ifreq ifreq;    
    int sock, ret = 0;
	int i = 0;

    if((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror ("socket");
        ret = -1;
    }
    strcpy(ifreq.ifr_name, "eth0");    //Currently, only get eth0

    if (ioctl(sock, SIOCGIFHWADDR, &ifreq) < 0)
    {
        perror("ioctl");
        ret = -1;
    }
	
    for(i = 0; i < 6; i++)
	{
		snprintf(mac + (i << 1), 18, "%x", (unsigned char) ifreq.ifr_hwaddr.sa_data[i]);
	}

    return ret;
}