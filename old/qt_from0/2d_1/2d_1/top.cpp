#include "top.h"
#include"QDebug"
#include <QMouseEvent>
top::top(QWidget *parent) :
  QWidget(parent)
{
//  this->hide();
  this->setGeometry(200,10,1024,768);
  setAutoFillBackground(true);
setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
//  this->setWindowFlags(Qt::SplashScreen );
  vw=new view(this);
  vw->move(310,80);
}

void top::mousePressEvent(QMouseEvent *e)
{
  qDebug()<<"top click";
  qDebug()<<e->x();
  qDebug()<<e->y();
}
