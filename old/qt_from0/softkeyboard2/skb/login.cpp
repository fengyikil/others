#include "login.h"
UserLogin::UserLogin(QWidget* parent):QWidget(parent)
{
  this->resize(400,400);
  userNameLabel = new QLabel(tr("用户名 : "),this);
  userNameEdit = new QLineEdit(this);
  okButton = new QPushButton(tr("确定"),this);

  userNameLabel->setGeometry(5,20,90,50);
  userNameEdit->setGeometry(100,20,150,50);
  okButton->setGeometry(100,90,150,50);
}
UserRegister::UserRegister(QWidget *parent):QWidget(parent)
{
  this->resize(400,400);
  userNameLabel = new QLabel(tr("用户名 :"),this);
  userNameEdit = new QLineEdit(this);
  passWdLabel = new QLabel(tr("密码 :"),this);
  passWdEdit =  new QLineEdit(this);
  rpassWdLabel = new QLabel(tr("重复密码 :"),this);
  rpassWdEdit =  new QLineEdit(this);
  okButton = new QPushButton(tr("注册并登录"),this);

  passWdEdit->setEchoMode(QLineEdit::Password);
  rpassWdEdit->setEchoMode(QLineEdit::Password);


  userNameLabel->setGeometry(5,20,90,50);
  passWdLabel->setGeometry(5,80,90,50);
  rpassWdLabel->setGeometry(5,140,90,50);

  userNameEdit->setGeometry(100,20,150,50);
  passWdEdit->setGeometry(100,80,150,50);
  rpassWdEdit->setGeometry(100,140,150,50);
  okButton->setGeometry(100,200,150,50);
}

Login::Login(QWidget *parent) :QWidget(parent)
{
  this->resize(1024,768);
  lor = 1;
  uLogin = new UserLogin(this);
  uLogin->move(200,200);
  uRegister = new UserRegister(this);
  uRegister->move(200,200);
  uRegister->hide();
}

void Login::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(Qt::gray);
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  if(lor)
    {
      painter.setPen(Qt::blue);
      painter.setFont(QFont("Times", 15));
      painter.drawText(QRect(0,10,512,25),Qt::AlignCenter,tr("用户登录"));
      painter.drawLine(215,40,295,40);
      painter.setPen(Qt::black);
      painter.drawText(QRect(512,10,512,25),Qt::AlignCenter,tr("用户注册"));
      painter.drawLine(727,40,807,40);
    }
  else
    {
      painter.setPen(Qt::black);
      painter.setFont(QFont("Times", 15));
      painter.drawText(QRect(0,10,512,25),Qt::AlignCenter,tr("用户登录"));
      painter.drawLine(215,40,295,40);
      painter.setPen(Qt::blue);
      painter.drawText(QRect(512,10,512,25),Qt::AlignCenter,tr("用户注册"));
      painter.drawLine(727,40,807,40);
    }
  painter.restore();
}

void Login::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(215,0,80,50).contains(event->pos()))
        {
          lor = 1;
          uRegister->hide();
          uLogin->show();
        }
      else if(QRect(727,0,807,50).contains(event->pos()))
        {
          lor = 0;
          uLogin->hide();
          uRegister->show();
        }
      update();
    }
}


