#include "top.h"

top::top(QWidget *parent)
  : QWidget(parent)
{
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
  msc = new myscroll(this);
  msc->move(100,0);
}

top::~top()
{
  
}
