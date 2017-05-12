#include "EditBt.h"
#include<QEvent>
#include <QApplication>
#include<QDebug>
#include<QPainter>
#include<QDebug>
EditBt::EditBt(QString IName,QString UName,bool isinput, QWidget *parent) :
  itemName(IName),unitName(UName),isInput(isinput), QWidget(parent)
{
  resize(131,81);
  //  setAutoFillBackground(true);
  //  setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
  inputState = 0;
  if(isinput)
    setAttribute(Qt::WA_InputMethodEnabled,true);
}

void EditBt::SetIuput(bool ipt)
{
  if(ipt)
    setAttribute(Qt::WA_InputMethodEnabled,true);
  else
    setAttribute(Qt::WA_InputMethodEnabled,false);

}

void EditBt::SetText(QString s)
{
  textValue = s;
  if(textValue=="0")
    textValue.clear();
  else if(textValue.contains("."))
    inputState = 2;
  else
    inputState = 1;
  value = textValue.toFloat();
}

void EditBt::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  painter.save();
  painter.drawLine(0,80,130,80);
  painter.drawLine(130,1,130,80);

  QLinearGradient mgradient(112,30,112,0);
  mgradient.setColorAt(0,QColor(186,195,205));
  mgradient.setColorAt(0.4,QColor(230,234,237));
  mgradient.setColorAt(0.8,QColor(186,195,205));

  painter.setBrush(mgradient);
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,130,80));

  painter.setPen(Qt::black);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(0,2,130,25),Qt::AlignCenter,this->itemName);
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(0,25,130,20),Qt::AlignCenter,this->unitName);
  painter.setFont(QFont("Times", 20));
  painter.setPen(QColor(0,65,175));
  //  painter.drawText(QRect(0,45,150,25),Qt::AlignCenter,QString().setNum(this->value,'g',6));
  painter.drawText(QRect(0,45,130,25),Qt::AlignCenter,this->textValue);

  painter.restore();
  //   qDebug()<<"child";
}

void EditBt::mousePressEvent(QMouseEvent *event)
{
  this->setFocus();
  QEvent ett(QEvent::RequestSoftwareInputPanel);
  QApplication::sendEvent(this,&ett);
}

void EditBt::keyPressEvent(QKeyEvent *e)
{
  qDebug()<<e->key();
  qDebug()<<e->text();
  if(e->key()==0x30) //0
    {
      if(inputState!=0)
        {
          textValue.append("0");
        }
    }
  else if(e->key()>0x30&&e->key()<=0x39)//1~9
    {
      if(inputState==0)
        inputState = 1;
      textValue.append(e->text());

    }

  else if(e->key()==0x2d) // -
    {
      if(textValue!="")
        {
          if(textValue.startsWith("-"))
            textValue.remove(0,1);
          else
            textValue.prepend("-");
        }
    }
  else if(e->key()==0x2e) // .
    {

      if(inputState==0)
        {
          textValue.append("0");
          textValue.append(e->text());
          inputState = 2;
          qDebug()<<".";
        }
      else if(inputState==1&&textValue!="-")
        {
          textValue.append(e->text());
          inputState = 2;
        }

    }
  else if(e->key()==0x1000003) //backspace
    {
      if(textValue.endsWith("."))
        {
          textValue.remove(textValue.size()-1,1);
          if(textValue=="0")
            {
              textValue.clear();
              inputState = 0;
            }
          else
            inputState = 1;
        }
      else
        {
          textValue.remove(textValue.size()-1,1);
          if(textValue=="")
            inputState = 0;
        }
      qDebug()<<inputState;
    }
  else if(e->key()==0x0100000b) //clear
    {
      textValue.clear();
      inputState=0;
      //    value = textValue.toFloat();
      //    emit SendEnter(value);
    }
  value = textValue.toFloat();
  qDebug()<< value;
  update();
}
