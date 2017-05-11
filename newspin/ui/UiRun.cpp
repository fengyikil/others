#include "UiRun.h"

UiRun::UiRun(QWidget *parent) :
  QWidget(parent)
{
  this->resize(1024,768);
  l[0] = new QLabel(tr("计量泵"),this);
  l[1] = new QLabel(tr("凝固域"),this);
  l[2] = new QLabel(tr("清洗槽"),this);
  l[3] = new QLabel(tr("收丝槽"),this);
  arrayEditBt[0] = new EditBt(tr("膜液泵流速"),tr("ml/min"),false,this);
  arrayEditBt[1] =  new EditBt(tr("芯液泵流速"),tr("ml/min"),false,this);
  arrayEditBt[2] =  new EditBt(tr("膜液泵温度"),tr("℃"),false,this);
  arrayEditBt[3] =  new EditBt(tr("芯液泵温度"),tr("℃"),false,this);

  arrayEditBt[4] =  new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[5] =  new EditBt(tr("空气间隙"),tr("mm"),false,this);
  arrayEditBt[6] =  new EditBt(tr("DMAC浓度"),tr("%"),false,this);
  arrayEditBt[7] =  new EditBt(tr("导丝轮速度"),tr("m/min"),false,this);


  arrayEditBt[8] =  new EditBt(tr("导丝轮升降"),tr("个/秒"),false,this);
  arrayEditBt[9] =  new EditBt(tr("循环泵流速"),tr("l/min"),false,this);
  arrayEditBt[10] =  new EditBt(tr("补充泵流速"),tr("l/min"),false,this);


  arrayEditBt[11] =   new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[12] =   new EditBt(tr("导丝轮升降"),tr("个/秒"),false,this);
  arrayEditBt[13] =  new EditBt(tr("导丝轮速度"),tr("m/min"),false,this);
  arrayEditBt[14] =   new EditBt(tr("循环泵流速"),tr("l/min"),false,this);

  arrayEditBt[15] =   new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[16] =   new EditBt(tr("收丝轮循环"),tr("cm/min"),false,this);
  arrayEditBt[17] =   new EditBt(tr("收丝轮速度"),tr("m/min"),false,this);
  arrayEditBt[18] =   new EditBt(tr("循环泵流速"),tr("℃"),false,this);


  pauseButton=new QPushButton(tr("暂停"),this);
  lockButton  =new QPushButton(tr("解锁"),this);
  shutDownButton=new QPushButton(tr("关机"),this);

  l[0]->setGeometry(80,140,100,25);
  l[1]->setGeometry(280,140,100,25);

  l[2]->setGeometry(680,140,100,25);
  l[3]->setGeometry(880,140,100,25);
  arrayEditBt[0]->setGeometry(50,180,131,81);
  arrayEditBt[1]->setGeometry(50,280,131,81);
  arrayEditBt[2]->setGeometry(50,380,131,81);
  arrayEditBt[3]->setGeometry(50,480,131,81);

  arrayEditBt[4]->setGeometry(250,180,131,81);
  arrayEditBt[5]->setGeometry(250,280,131,81);
  arrayEditBt[6]->setGeometry(250,380,131,81);
  arrayEditBt[7]->setGeometry(250,480,131,81);

  arrayEditBt[8]->setGeometry(450,180,131,81);
  arrayEditBt[9]->setGeometry(450,280,131,81);
  arrayEditBt[10]->setGeometry(450,380,131,81);

  arrayEditBt[11]->setGeometry(650,180,131,81);
  arrayEditBt[12]->setGeometry(650,280,131,81);
  arrayEditBt[13]->setGeometry(650,380,131,81);
  arrayEditBt[14]->setGeometry(650,480,131,81);

  arrayEditBt[15]->setGeometry(850,180,131,81);
  arrayEditBt[16]->setGeometry(850,280,131,81);
  arrayEditBt[17]->setGeometry(850,380,131,81);
  arrayEditBt[18]->setGeometry(850,480,131,81);

   pauseButton->setGeometry(180,600,150,80);
   lockButton->setGeometry(430,600,150,80);
   shutDownButton->setGeometry(680,600,150,80);


}

void UiRun::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(QColor(85, 196, 255));
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  painter.setPen(Qt::green);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(190,10,341,25),Qt::AlignCenter,tr("运行"));
  //  painter.drawLine(295,40,405,40);

  painter.setPen(Qt::red);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawArc(QRect(900,10,35,35),90*16,-270*16);
  //  painter.restore();

  QLinearGradient grad(240,0,240,65);

  grad.setColorAt(0.1,QColor(107,200,225));
  grad.setColorAt(0.5,QColor(164,221,237));
  grad.setColorAt(0.9,QColor(107,200,225));
  painter.setPen(QColor(186,195,205));
  painter.setBrush(grad);

  painter.drawRect(QRect(180,60,110,65));
  painter.drawRect(QRect(290,60,110,65));
  painter.drawRect(QRect(400,60,110,65));
  painter.drawRect(QRect(510,60,110,65));
  painter.drawRect(QRect(620,60,110,65));
  painter.drawRect(QRect(730,60,110,65));


  painter.setPen(QColor(61, 171, 10));

  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(180,60,110,25),Qt::AlignCenter,tr("空气温度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(180,78,110,20),Qt::AlignCenter,tr("℃"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(180,100,110,20),Qt::AlignCenter,QString().setNum(this->value1,'g',6));

  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(290,60,110,25),Qt::AlignCenter,tr("空气湿度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(290,78,110,20),Qt::AlignCenter,tr("%"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(290,100,110,20),Qt::AlignCenter,QString().setNum(this->value2,'g',6));


  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(400,60,110,25),Qt::AlignCenter,tr("膜丝张力"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(400,78,110,20),Qt::AlignCenter,tr("g"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(400,100,110,20),Qt::AlignCenter,QString().setNum(this->value3,'g',6));


  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(510,60,110,25),Qt::AlignCenter,tr("膜丝周长"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(510,78,110,20),Qt::AlignCenter,tr("m/min"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(510,100,110,20),Qt::AlignCenter,QString().setNum(this->value4,'g',6));


  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(620,60,110,25),Qt::AlignCenter,tr("膜液温度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(620,78,110,20),Qt::AlignCenter,tr("℃"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(620,100,110,20),Qt::AlignCenter,QString().setNum(this->value5,'g',6));


  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(730,60,110,25),Qt::AlignCenter,tr("芯液温度"));
  painter.setFont(QFont("Times", 12));
  painter.drawText(QRect(730,78,110,20),Qt::AlignCenter,tr("℃"));
  painter.setFont(QFont("Times", 16));
  painter.drawText(QRect(730,100,110,20),Qt::AlignCenter,QString().setNum(this->value6,'g',6));

  painter.restore();
}

void UiRun::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(900,0,40,40).contains(event->pos()))
        {
          qDebug()<<"commmmmmmmmmmmm";
          ChangeUi(5);
        }
    }
  update();
}

void UiRun::showEvent(QShowEvent *)
{
}

void UiRun::hideEvent(QHideEvent *)
{
}
