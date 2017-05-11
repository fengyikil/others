#include "myscroll.h"
#include "QPainter"
#include <QTime>
int i;
QString str;
myscroll::myscroll(QWidget *parent) :
  QWidget(parent)
{
  this->resize(450,600);
  p1 = new QPixmap(300,400);
  p1->fill(Qt::transparent);
  p1 = new QPixmap(this->width(),this->height());
  p1->fill(Qt::transparent);

  QTime tim;
  tim=QTime::currentTime();
  qsrand(tim.msec()+tim.second()*1000);
  QPainter painter;
  painter.begin(p1);
  painter.setPen(Qt::red);
  save.setX(0);
  save.setY(300);
  for(int i=1;i<400;i++)
    {
      now.setX(i);
      now.setY(qrand()%20+300);
    painter.drawLine(save,now);
    save =now;
    }
painter.drawLine(0,400,400,400);
painter.drawLine(0,200,0,400);
for(int i=0;i<200;i++)
{
  if(!(i%10))
    {
    painter.drawLine(0,400-i,3,400);
    }
}


for(i=0;i<400;i++)
  {
    if(!(i%50))
      {
        painter.save();
       painter.translate(i,400);
       painter.rotate(-15);
       painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(0,0,0,5);
        str.setNum(i);
        painter.drawText(QRectF(-10,0,30,50),Qt::AlignCenter,str);

        painter.restore();
      }
  }
//  draw_p1();

}

void myscroll::paintEvent(QPaintEvent *)
{

  QPainter painter;
  painter.begin(this);
  painter.drawPixmap(100,10,400,600,*p1);


}

void myscroll::timerEvent(QTimerEvent *)
{
   QRegion exposed;
    p1->scroll(-1,0,p1->rect(), &exposed);
  QPainter painter;

  save.setX(save.x()-1);
  now.setY(qrand()%20+300);
  painter.begin(p1);
  painter.setPen(Qt::red);
  painter.drawLine(save,now);
  save = now;
 painter.drawLine(0,400,400,400);
 painter.drawLine(0,200,0,400);
 for(int i=0;i<200;i++)
 {
   if(!(i%10))
     {
     painter.drawLine(0,400-i,3,400-i);
     }
 }
//  painter.drawPoint(299,310);

 if(!(i%50))
   {
     painter.translate(400,400);
     painter.rotate(-15);
     painter.setRenderHint(QPainter::Antialiasing,true);
      painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
      painter.drawLine(0,0,0,5);
      str.setNum(i);
      painter.drawText(QRectF(-10,0,30,50),Qt::AlignCenter,str);
   }
 i++;

  update();
}

void myscroll::showEvent(QShowEvent *)
{
  myTimerId=startTimer(1000);
}

void myscroll::hideEvent(QHideEvent *)
{
   killTimer(myTimerId);
}

void myscroll::draw_p1()
{
  QPainter painter;
  painter.begin(p1);
  painter.setPen(Qt::red);
  painter.drawLine(0,400,400,400);
}
