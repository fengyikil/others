#include "curve.h"
#include<QPainter>
#include<QDebug>
curve::curve(QWidget *parent) :
  QWidget(parent)
{
  this->resize(600,600);
  p_buffer = size();
  p_buffer.fill(Qt::transparent);
  draw();

}

void curve::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.drawPixmap(0, 0, p_buffer);
  painter.drawPixmap(300, 0, p_buffer.scaled(QSize(200,100), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
  painter.drawPixmap(0, 300, p_buffer.scaled(QSize(200,100), Qt::KeepAspectRatio,Qt::SmoothTransformation));
  painter.drawPixmap(300,300, p_buffer.scaled(QSize(200,100), Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));

// p_buffer =  p_buffer.scaled(QSize(200,100), Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
// painter.setRenderHint(QPainter::Antialiasing,true);
//  painter.drawPixmap(0, 0, p_buffer);
//  qDebug()<<this->width();
    qDebug()<<p_buffer.width();
     qDebug()<<p_buffer.height();
}

void curve::draw()
{
//  QPainter painter;
//  painter.begin(&p_buffer);
  QPixmap *pixmap;
  QString picName;
  picName = "/home/kil/picture/1.png";
  pixmap = new QPixmap(picName);
  p_buffer = *pixmap;
//     painter.setRenderHint(QPainter::Antialiasing,true);
//     painter.drawRect(10,10,300,300);

}
