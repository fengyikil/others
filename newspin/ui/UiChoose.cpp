#include "UiChoose.h"
#include "global.h"

UiChoose::UiChoose(QWidget *parent):QWidget(parent)
{
  this->resize(1024,768);
  historyButton = new QPushButton(tr("查看历史"),this);
  modeButton = new QPushButton(tr("模式"),this);

  historyButton->setGeometry(400,250,150,50);
  modeButton->setGeometry(400,350,150,50);

  connect(historyButton,SIGNAL(clicked()),this,SLOT(ChooseHistory()));
  connect(modeButton,SIGNAL(clicked()),this,SLOT(ChooseMode()));

}

void UiChoose::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(QColor(85, 196, 255));
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  painter.setPen(Qt::green);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(190,10,341,25),Qt::AlignCenter,QString(tr("登录用户：%1")).arg(global->loginName));

//      painter.setPen(Qt::blue);
//      painter.setFont(QFont("Times", 15));
//      painter.drawText(QRect(768,10,256,25),Qt::AlignCenter,tr("重新登录"));
//      painter.drawLine(855,40,935,40);
  painter.setPen(Qt::red);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawArc(QRect(900,10,35,35),90*16,-270*16);

  painter.restore();
}

void UiChoose::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(900,0,40,40).contains(event->pos()))
        {
         ChangeUi(1);
        }
    }
  update();
}

void UiChoose::ChooseHistory()
{
  emit ChangeUi(4);
}

void UiChoose::ChooseMode()
{
  emit ChangeUi(5);
}
