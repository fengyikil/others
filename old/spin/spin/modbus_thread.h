#ifndef MODBUS_THREAD_H
#define MODBUS_THREAD_H

#include <QThread>
#include <QTimer>
#include <errno.h>
#include <modbus.h>
#include "type.h"
class ModbusDevice:public QObject
{
  Q_OBJECT
public:
   explicit ModbusDevice(QObject *parent = 0);
   QTimer *timer;
   modbus_t *ctx;
   modbus_t *ctx1;
   modbus_t *ctx2;
   int erro;
   void InitModbus(modbus_t** cx);
   void SendReg(modbus_t** cx,int slave,int addr,unsigned short data);
   void SendRegs(modbus_t** cx,int slave,int addr, int nb, unsigned short *data);
   void receiveRegs(modbus_t** cx,int slave,int addr, int nb, unsigned short *data);

   void SetTaiDa(struct MdMesg);
   void SetFeq(struct MdMesg);
   void SetTemperature(struct MdMesg);
   void SetBj(struct MdMesg);
public slots:
   void SetMsg(struct MdMesg);
   void ReadAd();

};
class ModbusThread : public QThread
{
  Q_OBJECT
public:
  explicit ModbusThread(QObject *parent = 0);
  void run();
  ModbusDevice* device;
signals:
  
public slots:
  
};

#endif // MODBUS_THREAD_H
