#include "editbt.h"
#include<QEvent>
#include <QApplication>
#include<QDebug>
#include<QPainter>
EditBt::EditBt(QWidget *parent) :
  QWidget(parent)
{
  resize(151,81);
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
  setAttribute(Qt::WA_InputMethodEnabled);
}

void EditBt::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();
  painter.drawLine(0,80,150,80);
  painter.drawLine(150,1,150,80);

  QLinearGradient mgradient(112,30,112,0);
  mgradient.setColorAt(0,QColor(186,195,205));
  mgradient.setColorAt(0.4,QColor(230,234,237));
  mgradient.setColorAt(0.8,QColor(186,195,205));

   painter.setBrush(mgradient);
   painter.setPen(Qt::NoPen);
   painter.drawRect(QRect(0,0,150,80));

  painter.setPen(Qt::black);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(0,2,150,25),Qt::AlignCenter,this->itemName);
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(0,25,150,20),Qt::AlignCenter,this->unitName);
  painter.setFont(QFont("Times", 20));
  painter.setPen(QColor(0,65,175));
  painter.drawText(QRect(0,45,150,25),Qt::AlignCenter,QString().setNum(this->value,'g',6));

  painter.restore();
}

void EditBt::mousePressEvent(QMouseEvent *event)
{
  this->setFocus();
  QEvent ett(QEvent::RequestSoftwareInputPanel);
  QApplication::sendEvent(this,&ett);
}

void EditBt::keyPressEvent(QKeyEvent *e)
{
  struct MdMesg mmsg;

  this->value = e->text().toFloat();
  mmsg.slave = this->slave;
  mmsg.value =  this->value;
  qDebug()<<"sendmsg";
  SendMesg(mmsg);
  update();
}
