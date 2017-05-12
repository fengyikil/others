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
#include <semaphore.h>
#include <mqueue.h>
#include "../include/map.h"
#include <pthread.h>
#include "hot.h"
#include<math.h>

//消息宏
#define MSG_PHQ_LIULIANG          1   //设置平衡腔流量
#define MSG_PHQ_KAIGUANG         2  //平衡腔周期开关
#define MSG_SL_KAIGUANG           3  //水路控制开关
#define MSG_HOT_KAIGUANG         4  //加热控制开关
#define MSG_AB_LIULIANG            5  //设置A泵流量
#define MSG_BB_LIULIANG            6  //设置B泵流量
#define MSG_CLB_LIULIANG           7  //设置超滤泵流量

//共享内存句柄
pTable ptab;
//can帧
struct can_frame fr;
int s; 
//水路相关变量
pthread_t phq_t;
pthread_t hot_t;
pthread_t water_t;
unsigned char phq_cmd;
unsigned char hot_cmd;
unsigned char water_cmd;
unsigned int phq_sleep; 
unsigned int hot_mode;//加热模式
//温度队列
ptem_queue ConTeQue;
ptem_queue TouQTeQue;

//extern int init_cansocket(struct can_filter* filter,int f_num);

write_io(unsigned char cmd, unsigned short value)
{
    fr.data[0] = cmd;
    fr.data[2] = value;
    fr.data[3] = value>>8;
    write(s,&fr,sizeof(struct can_frame));
}
write_ioa(unsigned char cmd, unsigned short  value,unsigned short value1)
{
    fr.data[0] = cmd;
    fr.data[2] = value;
    fr.data[3] = value>>8;
    fr.data[4] = value1;
    fr.data[5] = value1>>8;
    write(s,&fr,sizeof(struct can_frame));
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
void set_liusu (unsigned char cmd,float Y,float K,int MP)
{
    float X;
    unsigned short Z;
    unsigned short M;
    unsigned short N;
    Y = Y/3600;
    X=31250*K/(Y*MP) - 1;
    Z = (unsigned short)(X +1);
    M = (unsigned short) X;
    N = (unsigned short) (Z*10 -X*10+0.5);
    printf("M is %d\n",M);
    printf("N is %d\n",N);
    write_ioa(cmd,M,N);

}
void *phq_thread()
{
    int step = 0;
    struct timespec req,rem;
    printf("phq_thread start\n");
    while(1)
    {
        req.tv_sec  = phq_sleep/1000;
        req.tv_nsec = (phq_sleep%1000)*1000*1000;
        nanosleep(&req,&rem);
        //sleep(1);
        if(phq_cmd)
        {
            if(step == 0)
            {
                ptab->OutD0 F6_OFF
                        ptab->OutD0 F9_OFF
                        ptab->OutD0 F7_OFF
                        ptab->OutD0 F12_OFF
                        write_io(IO_0,ptab->OutD0);
                req.tv_sec  = 0;
                req.tv_nsec = 300*1000*1000; //开关平衡器之间延时300毫秒
                nanosleep(&req,&rem);

                ptab->OutD0 F5_ON
                        ptab->OutD0 F10_ON
                        ptab->OutD0 F8_ON
                        ptab->OutD0 F11_ON
                        write_io(IO_0,ptab->OutD0);
                step=1;

            }
            else
            {
                ptab->OutD0 F5_OFF
                        ptab->OutD0 F10_OFF
                        ptab->OutD0 F8_OFF
                        ptab->OutD0 F11_OFF
                        write_io(IO_0,ptab->OutD0);

                req.tv_sec  = 0;
                req.tv_nsec = 300*1000*1000; //开关平衡器之间延时300毫秒
                nanosleep(&req,&rem);

                ptab->OutD0 F6_ON
                        ptab->OutD0 F9_ON
                        ptab->OutD0 F7_ON
                        ptab->OutD0 F12_ON
                        write_io(IO_0,ptab->OutD0);
                step = 0;
            }

        }
    }
}
void pid_con(int tartemp)
{

    int t1,t5;
    float e1,e5;
    float P,D;
    float K;//流量系数
    int add;
    if(phq_cmd)
            K = ptab->PhqFlowRate/650.0;
    else
        K = 0;

    printf("pid_con start\n");
    max_min_avera(ConTeQue,1,6);
    t1 = ConTeQue->avera;
    e1 = tartemp-t1;


    max_min_avera(ConTeQue,12,18);
    t5 = ConTeQue->avera;
    e5 = tartemp-t5;

    //add = (ptab->PROPORTION * e1 + ptab->INTEGRATION*(e1+e2+e3+e4+e5) + ptab->DIFFERENTIATION * (e1 - e5))/10;
    //    add = (15*e1 +3*(abs(e1)+10)*(e1-e5))/10;
    if(e1<0)
    {
        P=1.5;
        D=0.3;
        add = (P*e1 + D*(e1-e5)*fabs(e1) )*K + 0.5 ;
    }
    else if(e1==0)
    {
        P=1.5;
        D=0.3;
        add = (P*e1 + D*(e1-e5))*K + 0.5 ;
    }
    else
    {
        P=1.5;
        D=0.2;
        add = (P*e1 + D*(e1-e5)*fabs(e1) )*K + 0.5 ;
    }
    ptab->RealPower = ptab->RealPower +add;
    if(ptab->RealPower>2000)
        ptab->RealPower = 2000;
    else if(ptab->RealPower<50)
        ptab->RealPower = 50;
    printf("K is %f\n",K);
    printf("add is %d\n",add);
    printf("realpower is %d\n",ptab->RealPower);
}
void *hot_thread()
{
    struct timespec req,rem;
    int tartemp;
    int contartemp;
    int differ;
    int count=0;
    int count1=0;
    int count2=0;
    int count3=0;
    int stable_erro = 0;
    short max;
    short min;
    short avera;
    short max1;
    short min1;
    short avera1;
    printf("hot_thread start\n");
    init_que(ConTeQue,180);
    init_que(TouQTeQue,180);
    while(1)
    {
        req.tv_sec  = 1;
        req.tv_nsec = 0;
        nanosleep(&req,&rem);
        en_que(ConTeQue,ptab->backdata.CONTe);
        en_que(TouQTeQue,ptab->backdata.TouQTe);
        tartemp = (ptab->TargetTem - 30)/0.0917 + ptab->reparam.tqtem_pa;
        contartemp = (ptab->TargetTem - 30)/0.0917 + ptab->reparam.contem_pa + stable_erro;
        differ = (contartemp - ptab->backdata.CONTe);
        if(hot_cmd)
        {

            switch(hot_mode)
            {
            case 1:
            {
                if(differ>50)
                    ptab->RealPower = 1600;
                else if(differ>40)
                    ptab->RealPower = 1400;
                else if(differ>30)
                    ptab->RealPower = 1200;
                else if(differ>20)
                    ptab->RealPower = 1000;
                else
                {
                    ptab->RealPower = 900;
                    hot_mode = 2;
                }
                break;
            }
            case 2:
            {
                count2++;
                if(count2>=120)
                    hot_mode=3;
                break;
            }
            case 3:
            {
                count++;
                if(count==12)//12秒进行一次PID调整
                {
                    if(ConTeQue->size>18)
                        pid_con(contartemp);
                    count = 0;
                }
                break;
            }
            default:
                break;
            }
            //稳态平衡调整
            if(count1<300)
                count1++;
            if(count1==300)
            {
                //判断温度是否稳定
                max_min_avera(ConTeQue,1,120);
                max = ConTeQue->max;
                min = ConTeQue->min;
                if((abs(max-contartemp)<5)&&(abs(min-contartemp)<5))//控制温度稳定
                {
                    max_min_avera(TouQTeQue,1,120);
                    max = TouQTeQue->max;
                    min =TouQTeQue->min;
                    avera = TouQTeQue->avera;
                    if(abs(max-min)<9)//透前温度稳定 极大值不波动
                    {
                        max_min_avera(TouQTeQue,1,10);
                        avera = TouQTeQue->avera;
                        max_min_avera(TouQTeQue,110,120);
                        avera1=TouQTeQue->avera;

                        if(abs(avera-avera1)<3) //透前温度稳定 两头平均值不波动
                        {
                            stable_erro = tartemp - avera;
                            count1 = 0; //如果调整则至少五分钟后再调
                        }
                    }
                }
            }
            //判断水箱无水时间 超过10秒停止加热,正常输出功率
            if(ptab->backdata.InD&FU_IN)
                count3++;
            else
                count3 = 0;
            if(count3<10)
            {
                write_io(V27_JR,ptab->RealPower);
                printf("ptab->RealPower is %d\n",ptab->RealPower);
            }
            else
                write_io(V27_JR,0);
        }

    }
}
void *water_thread()
{
    struct timespec req,rem;
    while(1)
    {
        req.tv_sec  =0;
        req.tv_nsec = 500*1000*1000;
        nanosleep(&req,&rem);
        if(water_cmd)
        {
            //检测V6 进水
            printf("ptab is %d\n",ptab->OutD1);
            if(ptab->backdata.InD&FU_IN)
                ptab->OutD2 F1_OFF
                        else
                        ptab->OutD2 F1_ON
                        write_io(IO_2,ptab->OutD2);
            //检测V22 透后
            if(ptab->backdata.InD&FU_OUT)
            {

                ptab->OutD1 B3_OFF
                        write_io(IO_1,ptab->OutD1);
                ptab->OutD0 F22_OFF
                        write_io(IO_0,ptab->OutD0);

            }
            else
            {

                ptab->OutD1 B3_ON
                        write_io(IO_1,ptab->OutD1);
                ptab->OutD0 F22_ON
                        write_io(IO_0,ptab->OutD0);
            }
        }
    }
}
void main()
{
    sleep(2);

    //打开自己的消息队列
    Qmesg mesg;
    struct timespec ts;
    struct timeval tv;//延时用
    int mq_data[128];//消息缓存区
    mqd_t water_mq;
    int erro;
    int i;
    water_mq = mq_open("/water",O_RDWR|O_CREAT,0666,NULL);
    
    //打开共享内存
    int fd;
    fd=shm_open("mkoncern",O_RDWR,0666);
    ptab=(pTable)mmap(NULL,sizeof(Table),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

   // 初始化can
    struct can_filter filter;
    filter.can_id=0x32|CAN_EFF_FLAG;
    filter.can_mask=0xFF;
    s=init_cansocket(&filter,sizeof(filter));

    fr.can_id=0x1a;
    fr.can_dlc=8;
    for(i=0;i<8;i++)
        fr.data[i]=0x0;


    //初始化控制开关
    phq_cmd = 0;
    hot_cmd = 0;
    water_cmd = 0;
    hot_mode = 0;
    //初始化队列
    ConTeQue = (ptem_queue) malloc(sizeof(tem_queue));
    TouQTeQue = (ptem_queue) malloc(sizeof(tem_queue));
    //创建水路线程

    pthread_create(&hot_t,NULL,hot_thread,NULL);
    pthread_create(&phq_t,NULL,phq_thread,NULL);
    pthread_create(&water_t,NULL,water_thread,NULL);

    //初始化相关的一部分ptab变量
    ptab->PROPORTION=8;
    ptab->INTEGRATION=1;
    ptab->DIFFERENTIATION=12;

    while(1)
    {
        //设置等待消息时间
        clock_gettime(CLOCK_REALTIME,&ts);
        ts.tv_nsec += 500 * 1000 * 1000;
        ts.tv_sec += ts.tv_nsec/(1000 * 1000 *1000);
        ts.tv_nsec %= (1000 * 1000 *1000);
        //等待消息
        erro= mq_timedreceive(water_mq,(char*)mq_data,128,0,&ts);
        memcpy(&mesg,mq_data,sizeof(Qmesg));
        //erro = -1;
        //printf("error is %d\n",erro);
        if(erro!=-1)
        {
            printf("re\n");
            switch(mesg.cmd.i)
            {
            case 1://设置平衡腔流量
            {
                if(mesg.data.i<=1100 && mesg.data.i>=300)//防止数值过小或过大
                {
                    ptab->PhqFlowRate = mesg.data.i;
                    printf("ptab->PhqFlowRate is %d\n",ptab->PhqFlowRate);
                    phq_sleep = (ptab->reparam.phq_pa*60*1000)/mesg.data.i; //(设定流量/(60*1000) = 30/所求时间)
                    phq_sleep = phq_sleep-300; //除去切换电磁阀延迟时间

                }
                break;
            }
            case 2://开关平衡腔周期控制
            {
                if(mesg.data.i)
                {
                    phq_cmd = 1;
                }
                else
                {
                    phq_cmd = 0;
                    ptab->OutD0 F6_OFF
                            ptab->OutD0 F9_OFF
                            ptab->OutD0 F7_OFF
                            ptab->OutD0 F12_OFF

                            ptab->OutD0 F5_OFF
                            ptab->OutD0 F10_OFF
                            ptab->OutD0 F8_OFF
                            ptab->OutD0 F11_OFF
                            write_io(IO_0,ptab->OutD0);

                }
                printf("mesg.data.i is %d\n",mesg.data.i);
                break;
            }
            case 3://开关水路
            {
                if(mesg.data.i)
                {
                    water_cmd = 1;
                    ptab->OutD1 F20_ON
                            ptab->OutD1 F21_ON
                            ptab->OutD0 F22_ON
                            ptab->OutD2 F23_ON
                            ptab->OutD1 F24_ON
                            ptab->OutD1 F25_ON
                            ptab->OutD1 F26_ON
                            ptab->OutD2 F27_ON
                            ptab->OutD2 F28_ON
                            write_io(IO_0,ptab->OutD0);
                    write_io(IO_1,ptab->OutD1);
                    write_io(IO_2,ptab->OutD2);
                }
                else
                {
                    water_cmd = 0;
                    ptab->OutD1 F20_OFF
                            ptab->OutD1 F21_OFF
                            ptab->OutD0 F22_OFF
                            ptab->OutD2 F23_OFF
                            ptab->OutD1 F24_OFF
                            ptab->OutD1 F25_OFF
                            ptab->OutD1 F26_OFF
                            ptab->OutD2 F27_OFF
                            ptab->OutD2 F28_OFF
                            write_io(IO_0,ptab->OutD0);
                    write_io(IO_1,ptab->OutD1);
                    write_io(IO_2,ptab->OutD2);
                }
                printf("mesg.data.i is %d\n",mesg.data.i);
                break;
            }
            case 4://开加热控制
            {
                if(mesg.data.i)
                {
                    hot_cmd =1;
                    hot_mode = 3;
                    printf("hot_cmd is .......%d\n",hot_cmd);
                    printf("hot_mode is .......%d\n",hot_mode);
                }
                else
                {
                    hot_cmd = 0;
                    hot_mode = 0;
                    printf("hot_cmd not .......%d\n",hot_cmd);

                }
                printf("mesg.data.i is %d\n",mesg.data.i);
                break;
            }
            case 5://改变A泵流速
            {
                ptab->AFlowRate = mesg.data.f;
                printf("ptab->reparam.ab_pa is %f",ptab->reparam.ab_pa);
                if(mesg.data.f!=0)
                    set_liusu(B4_PU,mesg.data.f,ptab->reparam.ab_pa,800);
                else
                    write_io(B4_PU,0);
                break;

            }
            case 6://改变B泵流速
            {
                ptab->BFlowRate = mesg.data.f;
                if(mesg.data.f!=0)
                    set_liusu(B5_PU,mesg.data.f,ptab->reparam.bb_pa,800);
                else
                    write_io(B5_PU,0);
                break;

            }
            case 7://改变超滤泵流速
            {
                ptab->ClFlowRate = mesg.data.f;
                if(mesg.data.f!=0)
                    set_liusu(B6_PU,mesg.data.f,ptab->reparam.cb_pa,1600);
                else
                    write_io(B6_PU,0);
                break;

            }
            default:break;

            }
        }
//        else//执行例行操作
//        {
//            if(ptab->cbackdata.CONTe>=45)
//            {
//                hot_cmd = 0;
//                write_io(V27_JR,0);
//            }
//        }
    }
}

