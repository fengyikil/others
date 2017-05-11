#include <QApplication>
#include "top.h"
//#include "view_frame.h"
#include<QTextCodec>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));//设置编码以支持中文格式

  top t;
  t.show();
  return a.exec();
}
