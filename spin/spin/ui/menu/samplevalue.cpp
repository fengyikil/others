#include "samplevalue.h"
#include "QPainter"
SampleValue::SampleValue(QWidget *parent) :
  QWidget(parent)
{
  value1 = value2 = value3 =value4 =value5 =value6 =value7 = value8 =  0.2;
    this->resize(890,72);
}

void SampleValue::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();
  QLinearGradient grad(240,0,240,65);
//  grad.setColorAt(0.2,QColor(186,195,205));
//  grad.setColorAt(0.35,QColor(230,234,237));
//  grad.setColorAt(0.8,QColor(186,195,205));
  grad.setColorAt(0.1,QColor(107,200,225));
  grad.setColorAt(0.5,QColor(164,221,237));
  grad.setColorAt(0.9,QColor(107,200,225));
  painter.setPen(QColor(186,195,205));
  painter.setBrush(grad);
  painter.drawRect(QRect(0,0,110,65));
  painter.drawRect(QRect(110,0,110,65));
  painter.drawRect(QRect(220,0,110,65));
  painter.drawRect(QRect(330,0,110,65));
  painter.drawRect(QRect(440,0,110,65));
  painter.drawRect(QRect(550,0,110,65));
  painter.drawRect(QRect(660,0,110,65));
  painter.drawRect(QRect(770,0,110,65));

painter.restore();
painter.save();
 painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(0,0,110,25),Qt::AlignCenter,tr("空气温度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(0,18,110,20),Qt::AlignCenter,tr("℃"));
  painter.setPen(QColor(61, 171, 10));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(0,35,110,20),Qt::AlignCenter,QString().setNum(this->value1,'g',6));

painter.restore();
painter.save();
 painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(110,0,110,25),Qt::AlignCenter,tr("空气湿度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(110,18,110,20),Qt::AlignCenter,tr("%"));
  painter.setPen(QColor(61, 171, 10));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(110,35,110,20),Qt::AlignCenter,QString().setNum(this->value2,'g',6));

  painter.restore();
  painter.save();
  painter.setFont(QFont("Times", 12));
    painter.drawText(QRect(220,0,110,25),Qt::AlignCenter,tr("膜丝张力"));
    painter.setFont(QFont("Times", 12));
    painter.drawText(QRect(220,14,110,20),Qt::AlignCenter,tr("g"));
    painter.setPen(QColor(61, 171, 10));
    painter.setFont(QFont("Times", 16));
    painter.drawText(QRect(220,35,110,20),Qt::AlignCenter,QString().setNum(this->value3,'g',6));

    painter.restore();
    painter.save();
      painter.setFont(QFont("Times", 12));
      painter.drawText(QRect(330,0,110,25),Qt::AlignCenter,tr("膜丝周长"));
      painter.setFont(QFont("Times", 12));
      painter.drawText(QRect(330,18,110,20),Qt::AlignCenter,tr("m/min"));
      painter.setPen(QColor(61, 171, 10));
      painter.setFont(QFont("Times", 16));
      painter.drawText(QRect(330,35,110,20),Qt::AlignCenter,QString().setNum(this->value4,'g',6));

      painter.restore();
      painter.save();
       painter.setFont(QFont("Times", 12));
        painter.drawText(QRect(440,0,110,25),Qt::AlignCenter,tr("膜液温度"));
        painter.setFont(QFont("Times", 12));
        painter.drawText(QRect(440,18,110,20),Qt::AlignCenter,tr("℃"));
        painter.setPen(QColor(61, 171, 10));
        painter.setFont(QFont("Times", 16));
        painter.drawText(QRect(440,35,110,20),Qt::AlignCenter,QString().setNum(this->value5,'g',6));

        painter.restore();
        painter.save();
          painter.setFont(QFont("Times", 12));
          painter.drawText(QRect(550,0,110,25),Qt::AlignCenter,tr("芯液温度"));
          painter.setFont(QFont("Times", 12));
          painter.drawText(QRect(550,18,110,20),Qt::AlignCenter,tr("℃"));
//          painter.setPen(QColor(61, 171, 10));
           painter.setPen(QColor(61, 171, 10));
          painter.setFont(QFont("Times", 16));
          painter.drawText(QRect(550,35,110,20),Qt::AlignCenter,QString().setNum(this->value6,'g',6));

          painter.restore();
          painter.save();
            painter.setFont(QFont("Times", 12));
            painter.drawText(QRect(660,0,110,25),Qt::AlignCenter,tr("膜液压力"));
            painter.setFont(QFont("Times", 12));
            painter.drawText(QRect(660,15,110,20),Qt::AlignCenter,tr("g"));
            painter.setPen(QColor(61, 171, 10));
            painter.setFont(QFont("Times", 16));
            painter.drawText(QRect(660,35,110,20),Qt::AlignCenter,QString().setNum(this->value7,'g',6));

            painter.restore();
//            painter.save();
              painter.setFont(QFont("Times", 12));
              painter.drawText(QRect(770,0,110,25),Qt::AlignCenter,tr("芯液压力"));
              painter.setFont(QFont("Times", 12));
              painter.drawText(QRect(770,14,110,20),Qt::AlignCenter,tr("g"));
              painter.setPen(QColor(61, 171, 10));
              painter.setFont(QFont("Times", 16));
              painter.drawText(QRect(770,35,110,20),Qt::AlignCenter,QString().setNum(this->value8,'g',6));
}
