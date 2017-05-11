#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../include/mtable.h"
#include <sys/mman.h>
#include <mqueue.h>
#include <pthread.h>

#ifndef AF_CAN
#define AF_CAN 29
#endif
#ifndef PF_CAN
#define PF_CAN AF_CAN
#endif
#define K_TEMP 0.0917 //温度斜率
#define K_DMY   6.40 //动脉压斜率
#define K_JMY    8.8  //静脉压斜率
#define K_LQY   2.5   //虑前透后压斜率
#define K_THY   2.5   //虑前透后压斜率
#define V_BLOOD 390 //每转一圈的反馈值
extern int init_cansocket(struct can_filter* filter,int f_num);
pTable ptab;
int s;
struct can_frame rfr[9];
char buffer[64];
int erro_num=0;
void data_handle()
{
    int i,j;
    char* pb=buffer;
    pReParam prp;
    prp =&(ptab->reparam);
    for(i=0;i<8;i++)
    {
        memcpy(pb,&rfr[i].data,8);
        pb+=8;
    }
    memcpy(&(ptab->backdata),buffer,sizeof(BackData));
    //处理温度
    ptab->cbackdata.CONTe = 30 + (ptab->backdata.CONTe - prp->contem_pa) * K_TEMP;
    ptab->cbackdata.TouQTe = 30 + (ptab->backdata.TouQTe - prp->tqtem_pa) * K_TEMP;
    ptab->cbackdata.JingShuiTe = 30 +(ptab->backdata.JingShuiTe - prp->jstem_pa)*K_TEMP;
    //处理压力
    ptab->cbackdata.JMY = (ptab->backdata.JMY-prp->jmy_pa)/K_JMY;
    ptab->cbackdata.DMY = (ptab->backdata.DMY-prp->dmy_pa)/K_DMY;

    ptab->cbackdata.LQY =  (ptab->backdata.LQY-prp->lqy_pa)/K_LQY;
    ptab->cbackdata.THY = (ptab->backdata.THY-prp->thy_pa)/K_THY;
    //处理血泵流量
    ptab->cbackdata.CNT1 =(ptab->backdata.CNT1)* ptab->reparam.xb_pa*60/390;
    //处理电导
    if(ptab->cbackdata.TouQTe<=29)
    ptab->cbackdata.TouQDDl =(ptab->backdata.TouQDDl/ptab->reparam.tq_ddl)/(1+(ptab->cbackdata.TouQTe - 25)*0.00483);
    else if (ptab->cbackdata.TouQTe>29 && ptab->cbackdata.TouQTe<=30)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0044);
    else if(ptab->cbackdata.TouQTe>30 && ptab->cbackdata.TouQTe<=31)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0059);
    else if(ptab->cbackdata.TouQTe>31 && ptab->cbackdata.TouQTe<=32)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0068);
    else if(ptab->cbackdata.TouQTe>32 && ptab->cbackdata.TouQTe<=33)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0073);
    else if(ptab->cbackdata.TouQTe>33 && ptab->cbackdata.TouQTe<=34)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0078);
    else if(ptab->cbackdata.TouQTe>34 && ptab->cbackdata.TouQTe<=35)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0078);
    else if(ptab->cbackdata.TouQTe>35 && ptab->cbackdata.TouQTe<=36)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0082);
    else if(ptab->cbackdata.TouQTe>36 && ptab->cbackdata.TouQTe<=37)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.0071);
    else if(ptab->cbackdata.TouQTe>37 && ptab->cbackdata.TouQTe<=38)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00796);
    else if(ptab->cbackdata.TouQTe>38 && ptab->cbackdata.TouQTe<=39)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00799);
    else if(ptab->cbackdata.TouQTe>39 && ptab->cbackdata.TouQTe<=40)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00785);
    else if(ptab->cbackdata.TouQTe>40 && ptab->cbackdata.TouQTe<=41)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00781);
    else if(ptab->cbackdata.TouQTe>41 && ptab->cbackdata.TouQTe<=42)
    ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00759);
    else
         ptab->cbackdata.TouQDDl = (ptab->backdata.TouQDDl/81.9)/(1+(ptab->cbackdata.TouQTe - 25)*0.00759);
}
void* data_thread()
{
    struct can_frame sfr;
    struct timeval tv;
    int ret;
    int i;
    char tmp;
    fd_set fds;
    while(1)
    {
        tv.tv_sec=0;
        tv.tv_usec=0;
        FD_ZERO(&fds);
        FD_SET(s,&fds);
        while(1)
        {
            //清空缓存
            ret=select(FD_SETSIZE,&fds,NULL,NULL,&tv);
            if(ret==0)
            {
               // printf("buffer is em\n");
                break;
            }
            else
            {
                //printf("buffer has a\n");
                read(s,&tmp,1);
            }
        }
        //发送数据采集命令
        sfr.can_id=0x1a;
        sfr.can_dlc=8;
        sfr.data[0]=14;
        write(s,&sfr,sizeof(sfr));
        //等待250ms
        tv.tv_sec=0;
        tv.tv_usec=150*1000;
        select(0,NULL,NULL,NULL,&tv);
        //数据采集
        for(i=0;i<9;i++)
        {
            tv.tv_sec = 0;
            tv.tv_usec= 0;
            FD_ZERO(&fds);
            FD_SET(s,&fds);
            ret=select(FD_SETSIZE,&fds,NULL,NULL,&tv);
            if(ret==0)
            {
                break;
            }
            else
            {
                read(s,&rfr[i],sizeof(struct can_frame));
            }
        }
        //采样的数据为8帧，则进行数据处理
        if(i==8)
        {
            data_handle();
          //  printf("re is succeed\n");

        }
        else
        {
           // printf("re is failed\n");
            erro_num++;
        }
        //printf("error_num is %d\n",erro_num);
        //printf("i is %d\n",i);

    }
}
//如果参数文件没有内容，则程序先指定参数
init_pa(pReParam prp)
{
    prp->phq_pa = 30.0;//平衡腔每腔（mL）
    prp->xb_pa = 8.9;//血泵每转流量（mL）
    prp->contem_pa= 3267; //30摄氏度对应的电压值
    prp->tqtem_pa = 3274;
    prp->jstem_pa =3276;
    prp->dmy_pa =  2042;//动脉零压力对应电压值
    prp->jmy_pa =  1223;
    prp->thy_pa =  1945;//透后零压力对应电压值
    prp->lqy_pa =  2080;
    prp->ab_pa = 0.226;//分频泵参数 每转流量（mL）
    prp->bb_pa = 0.226;
    prp->cb_pa = 0.226;
    prp->tq_ddl = 81.9;

}
void main()
{


    //打开自己的消息队列
    Qmesg mesg;
    struct timespec ts;
    struct timeval tv;//延时用
    int mq_data[128];//消息缓存区
    mqd_t data_mq;
    int erro;
    data_mq = mq_open("/data",O_RDWR|O_CREAT,0666,NULL);

    //校正用变量
    float X;
    float Y;
    float K;
    float MP;

    //打开共享内存
    int fd;
    fd=shm_open("mkoncern",O_RDWR,0777);
    ptab=(pTable)mmap(NULL,sizeof(Table),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //打开参数文件
    int pa_fd;
    ReParam rpb;
    pa_fd = open("paramter",O_RDWR|O_CREAT|O_SYNC,0666);
    //    printf("pa_fd is %d\n",pa_fd);
    //    sleep(2);

    if(read(pa_fd,&rpb,sizeof(ReParam))!=sizeof(ReParam))
    {
        printf("param size is error\n");
        init_pa(&rpb);
        write(pa_fd,&(rpb),sizeof(ReParam));
    }
    //    sleep(2);
    memcpy(&(ptab->reparam),&rpb,sizeof(ReParam));
    //初始化cansocket
    struct can_filter filter;
    filter.can_id=0x88|CAN_EFF_FLAG;
    filter.can_mask=0xFF;
    s=init_cansocket(&filter,sizeof(filter));
    //创建can数据采集线程
    pthread_t can_t;
    pthread_create(&can_t,NULL,data_thread,NULL);

    while(1)
    {
        //设置等待消息时间
        clock_gettime(CLOCK_REALTIME,&ts);
        ts.tv_nsec += 500 * 1000 * 1000;
        ts.tv_sec += ts.tv_nsec/(1000 * 1000 *1000);
        ts.tv_nsec %= (1000 * 1000 *1000);
        //等待消息
        erro= mq_timedreceive(data_mq,(char*)mq_data,128,0,&ts);
        memcpy(&mesg,mq_data,sizeof(Qmesg));
        //erro = -1;
        //printf("error is %d\n",erro);
        if(erro!=-1)
        {

            switch(mesg.cmd.i)
            {

            case 1://校正进水温度
            {
                ptab->reparam.jstem_pa = ptab->reparam.jstem_pa + (ptab->cbackdata.JingShuiTe - mesg.data.f )/K_TEMP;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 2://校正水箱温度
            {
                ptab->reparam.contem_pa = ptab->reparam.contem_pa + (ptab->cbackdata.CONTe - mesg.data.f )/K_TEMP;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 3://校正透前温度
            {
                ptab->reparam.tqtem_pa = ptab->reparam.tqtem_pa + (ptab->cbackdata.TouQTe - mesg.data.f )/K_TEMP;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
                /*
                流量          Y
                分频量        X
                每转流量      K
                每转脉冲     MP 1600
                输入频率     62500
                输出脉冲      P
                P = 62500/2(x+1)

                Y= P/MP * K
                化简：Y=31250*K/((X+1)*MP)
                      X=31250*K/(Y*MP) - 1
                      K = (X+1)*Y*MP/31250
                */
            case 4://校正 A泵
            {
                Y = ptab->AFlowRate/3600;//当前理论
                K = ptab->reparam.ab_pa; //旧K
                X = 31250*K/(Y*800) - 1;//求出当前X
                Y =mesg.data.f/3600;//实际Y
                K=  (X+1)*Y*800/31250;
                ptab->reparam.ab_pa = K;
                ptab->AFlowRate =mesg.data.f;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 5://校正 B泵
            {
                Y = ptab->BFlowRate/3600;//当前理论
                K = ptab->reparam.bb_pa; //旧K
                X = 31250*K/(Y*800) - 1;//求出当前X
                Y =mesg.data.f/3600;//实际Y
                K=  (X+1)*Y*800/31250;
                ptab->reparam.bb_pa = K;
                ptab->BFlowRate = mesg.data.f;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 6://校正 超滤泵
            {
                Y = ptab->ClFlowRate/3600;//当前理论
                K = ptab->reparam.cb_pa; //旧K
                X = 31250*K/(Y*800) - 1;//求出当前X
                Y =mesg.data.f/3600;//实际Y
                K=  (X+1)*Y*800/31250;
                ptab->reparam.cb_pa = K;
                ptab->ClFlowRate = mesg.data.f;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 7://校正 静脉压力
            {
                ptab->reparam.jmy_pa = ptab->backdata.JMY;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 8://校正 动脉压力
            {
                ptab->reparam.dmy_pa=ptab->backdata.DMY;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;
            }
            case 9://校正 滤器压力
            {
                ptab->reparam.lqy_pa = ptab->backdata.LQY;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;

            }
            case 10://校正 透后压力
            {
                ptab->reparam.thy_pa = ptab->backdata.THY;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                break;

            }
            case 11://校正 透前电导
            {
                 ptab->cbackdata.TouQDDl = mesg.data.f;
                 ptab->reparam.tq_ddl = ptab->backdata.TouQDDl/(mesg.data.f*(1+(ptab->cbackdata.TouQTe - 25)*0.012));
                 lseek(pa_fd,0,SEEK_SET);
                 write(pa_fd,&(ptab->reparam),sizeof(ReParam));
                 printf("ddl is set %f\n",ptab->reparam.tq_ddl);
            //ptab->cbackdata.TouQDDl =ptab->backdata.TouQDDl/(ptab->reparam.tq_ddl*(1+(ptab->cbackdata.TouQTe - 25)*0.012));
            }
            case 12://校正 平衡腔
            {

                ptab->reparam.phq_pa = (mesg.data.f *ptab->reparam.phq_pa ) / ptab->PhqFlowRate;
                ptab->PhqFlowRate = mesg.data.f;
                lseek(pa_fd,0,SEEK_SET);
                write(pa_fd,&(ptab->reparam),sizeof(ReParam));
            }
defaut:
                break;
            }
        }

    }
}



