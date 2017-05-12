#include <QApplication>
#include "top.h"
#include "myinputpanelcontext.h"
#include<QTextCodec>
#include<QObject>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));//设置编码以支持中文格式
  MyInputPanelContext *ic = new MyInputPanelContext;
  a.setInputContext(ic);

  //设置全局文字大小
      QFont font  = a.font();
      font.setPointSize(15);
      a.setFont(font);
  Top w;
  w.show();
  
  return a.exec();
}
