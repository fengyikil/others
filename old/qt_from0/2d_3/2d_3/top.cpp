#include "top.h"
#include <unistd.h>
top::top(QWidget *parent)
  : QWidget(parent)
{
  this->resize(1024,768);
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
  ce = new curve(this);
// ce->setGeometry(50,50,100,100);
// ce->setGeometry(50,50,300,300);
}

top::~top()
{
  
}
