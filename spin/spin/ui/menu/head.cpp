#include "head.h"
#include "QPainter"
Head::Head(QWidget *parent) :
  QWidget(parent)
{
  resize(1024,80);
  current_date_time = QDateTime::currentDateTime();
  Atext=current_date_time.toString("yyyy-MM-dd");
  Btext=current_date_time.toString("ddd");
  Ctext=current_date_time.toString("hh:mm:ss");
  tim=new QTimer(this);
  tim->setInterval(1000);
  tim->start();
  connect(tim,SIGNAL(timeout()),this,SLOT(get_time()));
}

void Head::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing,true);
  QLinearGradient top(515,0,515,60);
  painter.setPen(Qt::NoPen);
  top.setColorAt(0,QColor(222,249,222));
  top.setColorAt(0.4,QColor(233,251,233));
  top.setColorAt(0.8,QColor(243,253,243));
//  top.setColorAt(0.1,QColor(107,200,225));
//  top.setColorAt(0.5,QColor(164,221,237));
//  top.setColorAt(0.9,QColor(107,200,225));
  painter.setBrush(top);
  painter.drawChord(QRectF(-700,-225,2500,300),16*210,16*120);

  painter.setPen(Qt::black);
  painter.setFont(QFont("Times", 23));
  painter.drawText(QRect(0,0,1024,80),Qt::AlignCenter,tr("纺丝机测试版"));

  painter.setFont(QFont("Helvetica", 12));
  painter.drawText(QRectF(800,0,150,60),Qt::AlignCenter,Atext+"\n"+Btext+"\n"+Ctext);
}

void Head::get_time()
{
  current_date_time = QDateTime::currentDateTime();
  Atext=current_date_time.toString("yyyy-MM-dd");
  Btext=current_date_time.toString("ddd");
  Ctext=current_date_time.toString("hh:mm:ss");
  update();
}
