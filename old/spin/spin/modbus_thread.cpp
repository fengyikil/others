#include "modbus_thread.h"
#include "QDebug"
extern struct AdData adData;
extern unsigned  short bjData;
ModbusThread::ModbusThread(QObject *parent) :
  QThread(parent)
{
  device = new ModbusDevice(this);
  device->moveToThread(this);
}

void ModbusThread::run()
{
  device->InitModbus(&device->ctx);
  device->InitModbus(&device->ctx1);
  device->InitModbus(&device->ctx2);
  exec();
}
ModbusDevice::ModbusDevice(QObject *parent)
{
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(ReadAd()));
  timer->start(1000);
}
void ModbusDevice::InitModbus(modbus_t** cx)
{

  if(cx == &ctx)
    {
       ctx = modbus_new_rtu("/dev/ttyS0",9600,'E',8,1);
    }
  else if(cx == &ctx1)
    {
      ctx1 = modbus_new_rtu("/dev/ttyS1",9600,'N',8,1);
    }
  else if(cx == &ctx2)
    {
      ctx2 = modbus_new_rtu("/dev/ttyS2",9600,'N',8,1);
    }
  struct timeval timeout;
  qDebug()<<"InitModbus";

  if(modbus_connect(*cx) == -1)
    {
      qDebug()<<modbus_strerror(errno);
      //          fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
      modbus_free(*cx);
      return ;
    }
  else
    {
      modbus_set_debug(*cx,1);
      qDebug()<<"connection ok\n";
    }
  timeout.tv_sec = 0;
  timeout.tv_usec =1000*1000;
  modbus_set_response_timeout(*cx,&timeout);
  //          printf("connection ok\n");
}


void ModbusDevice::SendReg(modbus_t** cx,int slave,int addr,unsigned short data)
{
  int num=0;
  modbus_set_slave(*cx,slave);
  while(modbus_write_register(*cx,addr,data)==-1)
    {
      modbus_flush(*cx);
      modbus_close(*cx);
      modbus_free(*cx);
      InitModbus(cx);
      qDebug()<<"cx is"<<cx;
      modbus_set_slave(*cx,slave);
      erro = 1;
      num++;
      if(num==1)
        return;
    }
}
void ModbusDevice::SendRegs(modbus_t** cx,int slave,int addr, int nb, unsigned short *data)
{
  struct timeval tpstart,tpend;
  float timeuse;
  gettimeofday(&tpstart,NULL);

  int num=0;
  qDebug()<<"send";
  modbus_set_slave(*cx,slave);

  while(modbus_write_registers(*cx,addr,nb,data)==-1)
    {
      gettimeofday(&tpend,NULL);
      timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
      tpend.tv_usec-tpstart.tv_usec;
      timeuse/=1000000;
      printf("Used Time:%f\n",timeuse);


      qDebug()<<"erro num is"<<num;
      modbus_flush(*cx);
      modbus_close(*cx);
      modbus_free(*cx);
      InitModbus(cx);
       qDebug()<<"cx is"<< cx;
      modbus_set_slave(*cx,slave);
      erro = 1;
      num++;
      if(num==1)
        return;
      gettimeofday(&tpstart,NULL);
    }
  gettimeofday(&tpend,NULL);
  timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
  tpend.tv_usec-tpstart.tv_usec;
  timeuse/=1000000;
  printf("Used Time:%f\n",timeuse);
  erro = 0;
}

void ModbusDevice::receiveRegs(modbus_t** cx,int slave,int addr, int nb, unsigned short *data)
{
int num=0;
  modbus_set_slave(*cx,slave);
  while(modbus_read_registers(*cx,addr,nb,data)==-1)
    {
      qDebug()<<"erro num is"<<num;
      modbus_flush(*cx);
      modbus_close(*cx);
      modbus_free(*cx);
      InitModbus(cx);
      modbus_set_slave(*cx,slave);
      erro = 1;
      num++;
      if(num==5)
        return;
    }
  erro = 0;
}

void ModbusDevice::SetMsg(struct MdMesg msg)
{
  int tmp = msg.slave/10;
  switch (tmp) {
    case 0:
      SetTaiDa(msg);
      break;
    case 1:
      SetFeq(msg);
      break;
    case 2:
      SetTemperature(msg);
      break;
    case 5:
      SetBj(msg);
      break;
    default:
      break;
    }
}

void ModbusDevice::SetTaiDa(struct MdMesg msg)
{
  /*
  * p3-06  0x30c 780
  * p1-09  0x112 274
  * p4-07  0x40e 1038
  */

  unsigned int tmp;
  unsigned short* p =(unsigned short*)&tmp;
  qDebug()<<"SetTaiDa"<<msg.value;

  //set p3-06
  tmp = 0xf;
//  SendRegs(1,0x00,2,p);
  SendRegs(&ctx,msg.slave,0x30c,2,p);
  //set p1-09
  tmp = msg.value;
  tmp=tmp*10;
  SendRegs(&ctx,msg.slave,0x112,2,p);
  //set p4-07
  if(tmp!=0)
    {
      tmp = 0x5;
      SendRegs(&ctx,msg.slave,0x40e,2,p);
    }
  else
    {
      tmp = 0x0;
      SendRegs(&ctx,msg.slave,0x40e,2,p);
    }
}
void ModbusDevice::SetFeq(struct MdMesg msg)
{
  /**
  * 0x2101~0x2102
  *
  */
  qDebug()<<"SetFeq"<<msg.value;

  unsigned short tmp[2];
 tmp[1] = qAbs(msg.value);
 tmp[1] = tmp[1]*100;
  if(msg.value>0)
    {
      tmp[0] = 0x01;
      SendRegs(&ctx,msg.slave,0x2101,2,tmp);
    }
 else if(msg.value==0)
    {
      tmp[0] = 0x0;
      SendRegs(&ctx,msg.slave,0x2101,2,tmp);
    }
  else
    {
      tmp[0] = 0x02;
      SendRegs(&ctx,msg.slave,0x2101,2,tmp);

    }
}
void ModbusDevice::SetTemperature(struct MdMesg msg)
{
  /*
* 0x2103  8451
*
*/

   qDebug()<<"Tem"<<msg.value;
  unsigned short tmp;
  tmp = msg.value;
  SendRegs(&ctx,msg.slave,0x2103,1,&tmp);

}
void ModbusDevice::SetBj(struct MdMesg msg)
{
   qDebug()<<"StBJ"<<msg.value;
   char reg;
  unsigned short tmp = qAbs(msg.value);
  tmp = tmp<<8;

  if(msg.value>0)
    {
       tmp |=0x02;
    }
  else if(msg.value==0)
    {
      tmp |=0x02;
    }
  else
    {
    tmp |= 0x03;
    }
  switch (msg.slave) {
    case 51:
      reg = 0x01;
      break;
    case 52:
      reg = 0x02;
      break;
    case 53:
      reg = 0x03;
      break;
    case 54:
      reg = 0x04;
      break;
    case 55:
      reg = 0x05;
      break;
    default:
      break;
    }
  SendReg(&ctx1,51,reg,tmp);
}
void ModbusDevice::ReadAd()
{
//  int id = 51;
//  receiveRegs(&ctx1,id,0x06,1,&bjData);
    int  id =101;
  receiveRegs(&ctx2,id,0x01,39,(unsigned short*)&adData);
}



