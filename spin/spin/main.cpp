#include <QApplication>
#include<QTextCodec>
#include <QMetaType>//记得包含这个头文件
#include "mainmenu.h"
#include "modbus_thread.h"
#include "type.h"
#include "ui/soft_keyboard/myinputpanelcontext.h"
#include "ui/menu/menu_top.h"
struct AdData adData;
unsigned  short bjData;
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));//设置编码以支持中文格式
  MyInputPanelContext *ic = new MyInputPanelContext;
  a.setInputContext(ic);
  qRegisterMetaType<struct MdMesg>("struct MdMesg");
  MainMenu w;
//  MenuTop w;
  ModbusThread mt;
  mt.start();

    QObject::connect(&w,SIGNAL(SendMesg(struct MdMesg)),mt.device,SLOT(SetMsg(struct MdMesg)),Qt::QueuedConnection);

//  QObject::connect(&w,SIGNAL(SendMesg(struct MdMesg)),mt.device,SLOT(SetMsg(struct MdMesg)),Qt::QueuedConnection);
  w.show();
  
  return a.exec();
}
