#include "mtable.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>
#include <mqueue.h>
#include <locale.h>
#include "map.h"
#include <pthread.h>
int data;
int water;
void creat_progress()
{
    

    water =fork();
    if(water == 0)
    {
        execl("water",NULL);
    }
    data = fork();
    if(data == 0)
    {
        execl("data",NULL);
    }
}

void main()
{
    int fd;
    int bf;

    struct tm* btime;
    char buffer[80];
    //初始化共享内存表
    pTable ptab;
    fd = shm_open("/mkoncern",O_RDWR|O_CREAT,0777);
    bf=ftruncate(fd,4096);
    ptab = (pTable)mmap(NULL,4096,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    memset(ptab,0,sizeof(Table));
    if(ptab == MAP_FAILED)
        printf("map failed\n");

    //初始化ptab
    //	ptab->OutD2 = 0xffff;
    ptab->OutD0 = 0x0;
    ptab->OutD1  = 0x0;
    ptab->OutD2 = 0x0;

    setlocale (LC_ALL, "");

    ptab->BootTime = time(NULL);

    btime = localtime(&ptab->BootTime);
    strftime (buffer, 80, "%c", btime);
    printf("boot time is %s\n",buffer);
    //创建消息队列
    mq_open("/water",O_RDWR|O_CREAT,0666,NULL);
    mq_open("/init",O_RDWR|O_CREAT,0666,NULL);
    mq_open("/data",O_RDWR|O_CREAT,0666,NULL);
    ///打开自己的消息队列
    Qmesg mesg;
    struct timespec ts;
    struct timeval tv;//延时用
    int mq_data[128];//消息缓存区
    mqd_t init_mq;
    int erro;
    init_mq = mq_open("/init",O_RDWR|O_CREAT,0666,NULL);
    //创建其它进程
    creat_progress();
    while(1)
    {
        // printf("I am init\n");
        //设置等待消息时间
        clock_gettime(CLOCK_REALTIME,&ts);
        ts.tv_nsec += 500 * 1000 * 1000;
        ts.tv_sec += ts.tv_nsec/(1000 * 1000 *1000);
        ts.tv_nsec %= (1000 * 1000 *1000);
        //等待消息
        erro= mq_timedreceive(init_mq,(char*)mq_data,128,0,&ts);
        memcpy(&mesg,mq_data,sizeof(Qmesg));
        //erro = -1;
        //printf("error is %d\n",erro);
        if(erro!=-1)
        {

//            switch(mesg.cmd.i)
//            {
//            case 1:
//            {


//            }
//            case 2:
//            {

//            }
//            case 99:
//            {
//                printf("mesg ...................re!!!!!!!!!!\n");
//            }
//            default:
//                break;
//            }
        }
//        else
//            printf("erro == -1\n");
    }
}

