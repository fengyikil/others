#include <QApplication>
#include "top.h"
#include<QLineEdit>
#include "myinputpanelcontext.h"
#include "editbt.h"
#include<QTextCodec>
#include<QObject>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));//设置编码以支持中文格式
  MyInputPanelContext *ic = new MyInputPanelContext;
  a.setInputContext(ic);

  top w;
  w.setGeometry(0,0,1024,768);

   QLineEdit pp(&w);

   EditBt ed(&w);
   ed.SetItemName(QObject::tr("分频器"));
   ed.SetUnitName("(r/min)");
   ed.SetValue(89.99);
   ed.move(800,100);

   EditBt ed1(&w);
   ed1.SetItemName(QObject::tr("分频器"));
   ed1.SetUnitName("(r/min)");
   ed1.SetValue(89.99);
   ed1.move(400,600);

   EditBt ed2(&w);
   ed2.SetItemName(QObject::tr("分频器"));
   ed2.SetUnitName("(r/min)");
   ed2.SetValue(89.99);
   ed2.move(400,100);

   EditBt ed3(&w);
   ed3.SetItemName(QObject::tr("分频器"));
   ed3.SetUnitName("(r/min)");
   ed3.SetValue(89.99);
   ed3.move(50,650);
  w.show();
  
  return a.exec();
}
