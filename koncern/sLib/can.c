#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#define myerr(str) fprintf(stderr,"%s,%s,%d:%s\n",__FILE__,__func__,__LINE__,str)
static void print_frame(struct can_frame *fr)
{
    int i;
    printf("I am process 1\n");
    printf("%08x\n",fr->can_id & CAN_EFF_MASK);
    printf("dlc=%d\n",fr->can_dlc);
    printf("data=");
    for(i=0;i<fr->can_dlc;i++)
        printf("%c\n",fr->data[i]);
   printf("\n");
}
int init_cansocket(struct can_filter* filter,int f_num)
{
    int s;
    int ret;
    struct sockaddr_can addr;
    struct ifreq ifr;
    s=socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if(s<0)
    {
        perror("socket PF_CAN failed");
        return 1;
    }
    strcpy(ifr.ifr_name,"can0");
    ret = ioctl(s,SIOCGIFINDEX,&ifr);

    if(ret<0)
    {
        perror("ioctl failed");
        return 1;
    }
    addr.can_family=PF_CAN;
    addr.can_ifindex=ifr.ifr_ifindex;
    ret=bind(s,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("bind failed");
        return 1;
    }
    if(1)
    {/*
                    struct can_filter filter[2];
                    filter[0].can_id=0x2a|CAN_EFF_FLAG;
                    filter[0].can_mask=0xFFF;
                    filter[1].can_id=0x20F|CAN_EFF_FLAG;
                    filter[1].can_mask=0xFFF;
                */

        printf("size is %d\n",sizeof(filter));
        ret=setsockopt(s,SOL_CAN_RAW,CAN_RAW_FILTER,filter,f_num);
        if(ret<0)
        {
            perror("setsockopt failed");
            return 1;
        }
    }
    return s;
}

