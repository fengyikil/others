#ifndef MTAB_H
#define MTAB_H
#include <time.h>
#define PARM 70 //参数个数
typedef struct _ReParam
{
    float phq_pa; //平衡腔每一腔流量 mL
    float xb_pa;  //血泵每转一圈流量 mL
    int contem_pa;//水箱30度对应的电压值
    int tqtem_pa;//透前30度对应的电压值
    int jstem_pa;//进水30度对应的电压值
    int dmy_pa;//动脉压为0时对应的电压值
    int jmy_pa;//静脉压力
    int lqy_pa;//虑前压力为0时对应的电压值
    int thy_pa;//透后压力
    float ab_pa;//A泵每转流量 mL
    float bb_pa;//B泵每转流量 mL
    float cb_pa;//超滤泵每转流量 mL
    float tq_ddl;
    float th_ddl;
    float by_ddl;
    float jc_ddl;
}ReParam,*pReParam;
typedef struct _BackData
{
    unsigned short InD;   //DIN反馈输入
    unsigned short BloodG;//漏血绿色数据
    unsigned short BloodR;//漏血红色数据
    unsigned short BloodB;//漏血蓝色数据


    unsigned short ByDDl; //B液电导
    unsigned short TouQDDl;//透前电导
    unsigned short JkDDl;  //监测电导
    unsigned short TouHDDl;//透后电导

    unsigned short BeiDDl1;//备用电导
    unsigned short BeiDDl2;//备用电导
    unsigned short GsbPos; //肝素泵位置
    unsigned short ZljPos;//阻流夹位置

    unsigned short JMY; //静脉压
    unsigned short DMY;//动脉压
    unsigned short LQY;//滤器压
    unsigned short THY;//透后压

    unsigned short JingShuiTe;//进水温度
    unsigned short ZYY2;//中央供液压力检测2
    unsigned short CONTe; //水箱温度
    unsigned short TouQTe;//透前温度

    unsigned short AdBEI;//AD采集备用
    unsigned short TestV;//自检电压值
    unsigned short CNT1;//血泵反馈计数
    unsigned short CNT2;//置换泵反馈计数

    unsigned short CNT3;//供压泵反馈计数
    unsigned short CNT4;//负压泵反馈计数
    unsigned short BEI1;//未知备用
    unsigned short BEI2;//

    unsigned short BEI3;//
    unsigned short BEI4;//
    unsigned short BEI5;//
    unsigned short BEI6;//

}BackData,*pBackData;

typedef struct _CBackData
{
    unsigned short InD;   //DIN反馈输入
    unsigned short BloodG;//漏血绿色数据
    unsigned short BloodR;//漏血红色数据
    unsigned short BloodB;//漏血蓝色数据


    unsigned short ByDDl; //B液电导
    float TouQDDl;//透前电导
    float JkDDl;  //监测电导
    float TouHDDl;//透后电导

    unsigned short BeiDDl1;//备用电导
    unsigned short BeiDDl2;//备用电导
    unsigned short GsbPos; //肝素泵位置
    unsigned short ZljPos;//阻流夹位置

     short JMY; //静脉压
     short DMY;//动脉压
     short LQY;//滤器压
     short THY;//透后压

    float JingShuiTe;//进水温度
     short ZYY2;//中央供液压力检测2
    float CONTe; //水箱温度
    float TouQTe;//透前温度

    unsigned short AdBEI;//AD采集备用
    unsigned short TestV;//自检电压值
    unsigned short CNT1;//血泵流速（min）
    unsigned short CNT2;//置换泵流速（min）

    unsigned short CNT3;//供压泵反馈计数
    unsigned short CNT4;//负压泵反馈计数
    unsigned short BEI1;//未知备用
    unsigned short BEI2;//

    unsigned short BEI3;//
    unsigned short BEI4;//
    unsigned short BEI5;//
    unsigned short BEI6;//

}CBackData,*pCBackData;

typedef union
{
    int i;
    unsigned int ui;
    short s[2];
    unsigned short us[2];
    char  c[4];
    unsigned char uc[4];
    float f;
}Var;
//消息
typedef struct _Qmesg
{
    Var cmd;
    Var data;
}Qmesg,*pQmesg;
//运行状态
typedef struct _RunState
{
	unsigned  char stage;  //一级状态 自检 预冲 治疗 消毒
	unsigned  char sstage; //二级状态 滤过模式 等等
}RunState,*pRunState;
//内存表格
typedef struct _Table
{
	RunState run_state;
    unsigned short AlarmBit[16];//报警标志位矩阵
    time_t BootTime; //开机时间
	unsigned short OutD0;//分别对应3个IO输出口
	unsigned short OutD1;
	unsigned short OutD2;
    float TargetTem;//目标温度
    short RealPower;//当前功率
    float AFlowRate;//当前A泵流速
    float BFlowRate;//当前B泵流速
    float ClFlowRate;//当前超滤泵流速
    int PhqFlowRate;//平衡腔流量
    ReParam reparam;
    BackData backdata;
    CBackData cbackdata;
    int PROPORTION;
    int INTEGRATION;
    int DIFFERENTIATION;
}Table,*pTable;
#endif
