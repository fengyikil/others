#include "view.h"
#include"QDebug"
#include"QPainter"
#include"QTimer"
#include <QMouseEvent>
view::view(QWidget *parent) :
  QWidget(parent)
{
  //  view_s = new view_shift(this);
  //  view_theory=new View_Theory(this);

  //  view_s->move(310,80);
  //  view_theory->move(310,80);
  this->resize(451,600);

  p_frame = new QPixmap(this->width(),this->height());
  p_frame->fill(Qt::transparent);
  p_shift = new QPixmap(this->width(),this->height());
  p_shift->fill(Qt::transparent);
  QTimer* timer;
  timer = new QTimer(this);
//  connect(timer, SIGNAL(timeout()), this, SLOT(draw_shift()));
//  timer->start(1000);
  draw_shift();
  draw_frame();


}

void view::paintEvent(QPaintEvent *)
{
  qDebug()<<"View";
  QPainter painter;
  painter.begin(this);
  painter.drawPixmap(0,0,this->width(),this->height(),*p_frame);
  painter.drawPixmap(55,80,this->width(),this->height(),*p_shift);

}
void view::draw_frame()
{
  p_frame->fill(Qt::transparent);
  QPainter painter(p_frame);
  painter.setPen(Qt::red);
  painter.drawLine(0,100,50,100);//line 1
  QPainterPath pathk;
  pathk.moveTo(20,100);
  pathk.lineTo(10,95);
  pathk.lineTo(10,105);
  pathk.closeSubpath();
  painter.setBrush(Qt::red);
  painter.drawPath(pathk);
  painter.setBrush(Qt::NoBrush);

  painter.setPen(Qt::black);
  painter.drawText(8,55,tr("动脉泵"));
  painter.drawLine(25,100,25,80);
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawEllipse(QRectF(15,60,20,20));
  painter.setRenderHint(QPainter::Antialiasing,false);
  painter.drawText(QRectF(15,60,20,20),Qt::AlignCenter,"P");

  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawText(62,70,tr("血泵"));
  painter.setPen(Qt::red);
  painter.drawArc(QRectF(50,75,50,50),0,16*180);
  painter.setRenderHint(QPainter::Antialiasing,false);
  painter.setPen(Qt::black);
  painter.drawText(130,35,tr("肝素泵"));
  painter.drawLine(150,100,150,80);
  painter.drawRect(140,50,20,30);
  painter.drawLine(140,60,160,60);
  painter.drawLine(150,60,150,40);
  painter.drawLine(135,40,165,40);

  painter.setPen(Qt::red);
  painter.drawLine(100,100,200,100);
  painter.drawLine(200,100,200,130);


  painter.setPen(Qt::black);
  painter.drawText(150,150,tr("液位"));
  painter.drawRect(190,130,20,20);
  painter.setBrush(QColor(65,65,149));
  QPainterPath path;
  path.moveTo(190,150);
  path.lineTo(210,150);
  path.lineTo(200,170);
  path.closeSubpath();
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawPath(path);//------san jiao xin
  painter.setRenderHint(QPainter::Antialiasing,false);
  painter.setPen(Qt::red);
  painter.drawLine(200,170,200,210);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(190,210,20,10);
  painter.drawRect(180,220,40,10);

  painter.drawRect(215,240,10,10);
  painter.drawRect(215,280,10,10);

  painter.setBrush(QColor(65,65,149));
  painter.drawRect(185,230,30,70);
  painter.setPen(Qt::white);
  for(int i=1;i<6;++i)
    painter.drawLine(185+i*5,231,185+i*5,300);

  painter.setBrush(Qt::NoBrush);
  painter.setPen(Qt::black);
  painter.drawRect(180,300,40,10);
  painter.drawRect(190,310,20,10);

  painter.setPen(Qt::red);
  painter.drawLine(200,320,200,370);

  painter.setPen(Qt::black);
  painter.drawText(110,337,tr("静脉压"));
  painter.drawLine(195,355,195,370);
  painter.drawLine(180,340,195,355);
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawEllipse(QRectF(160,325,20,20));
  painter.setRenderHint(QPainter::Antialiasing,false);
  painter.drawText(QRectF(160,325,20,20),Qt::AlignCenter,"P");


  painter.drawRect(190,370,20,20);

  painter.setBrush(QColor(65,65,149));
  QPainterPath pathb;
  pathb.moveTo(190,390);
  pathb.lineTo(210,390);
  pathb.lineTo(200,410);
  pathb.closeSubpath();
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawPath(pathb);//------san jiao xin

  painter.setRenderHint(QPainter::Antialiasing,false);
  painter.drawText(145,440,tr("气泡"));
  painter.drawRect(185,430,30,10);

  painter.drawText(135,502,tr("阻流夹"));

  painter.drawLine(185,490,185,505);
  painter.drawLine(215,490,215,505);
  painter.drawLine(185,490,215,505);
  painter.drawLine(215,490,185,505);

  painter.setPen(Qt::red);

  painter.drawLine(200,410,200,570);
  painter.drawLine(50,570,200,570);
  //   draw_circle(painter,1);
  //  draw_circle(painter,2);
  //  draw_status(painter);
  //  update();
}

void view::draw_shift()
{
  p_shift->fill(Qt::transparent);
  QPainter painter;
  painter.begin(p_shift);
  painter.setPen(Qt::red);
  painter.setBrush(QColor(65,65,149));
  painter.translate(20,20);
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.setPen(Qt::NoPen);
  painter.rotate(ro);
  ro+=15;
  painter.drawEllipse(QRect(-20,-5,40,10));
  painter.setRenderHint(QPainter::Antialiasing,false);
  //  update();

}
void view::mousePressEvent(QMouseEvent *e)
{
  qDebug()<<"click";
  qDebug()<<e->x();
  qDebug()<<e->y();

}

void view::timerEvent(QTimerEvent *e)
{
//   QRegion exposed;
//  p_shift->scroll(-1,0,p_shift->rect(), &exposed);
  draw_shift();
  update();
}

void view::showEvent(QShowEvent *)
{
  myTimerId=startTimer(200);
}

void view::hideEvent(QHideEvent *)
{
  killTimer(myTimerId);
}
