#ifndef TEST_RUN_TIME_H
#define TEST_RUN_TIME_H

#if defined _WIN32
#include <windows.h>
static LARGE_INTEGER litmp;
static LONGLONG Qpart1,Qpart2,Useingtime;
static double dfMinus,dfFreq,dfTime;

//获得CPU计时器的时钟频率
static inline void rtime_start()
{
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;

    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart1 = litmp.QuadPart; //开始计时
}
//function(); //待测试的计算函数等
static inline void rtime_end()
{
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart2 = litmp.QuadPart; //终止计时

    dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
    dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
    Useingtime = dfTime*1000000;
}

static inline void rtime_print()
{
    printf("UseTime is %f(us) %f(ms) %f(s)\n",Useingtime*1.0,Useingtime*1.0/1000,Useingtime*1.0/1000000);
}
#else
#include <sys/time.h>
static struct timeval tpstart,tpend;
static int Useingtime;
static inline void rtime_stat()
{
    gettimeofday(&tpstart,NULL);
}
static inline void rtime_end()
{
    gettimeofday(&tpend,NULL);

}
static inline void rtime_print()
{
Useingtime=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec);
printf("UseTime is %d us\n",Useingtime);

}
#endif
#define T_RUN_START {rtime_start();}
#define T_RUN_END(msg) {rtime_end();printf(msg);printf("---------------------\n");printf("\t\t");rtime_print();printf("\n\n");}
#endif
