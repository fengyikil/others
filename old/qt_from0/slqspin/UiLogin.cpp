#include "UiLogin.h"
#include <QtSql>
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
  surePassWdLabel = new QLabel(tr("重复密码 :"),this);
  surePassWdEdit =  new QLineEdit(this);
  okButton = new QPushButton(tr("注册"),this);

  passWdEdit->setEchoMode(QLineEdit::Password);
  surePassWdEdit->setEchoMode(QLineEdit::Password);


  userNameLabel->setGeometry(5,20,90,50);
  passWdLabel->setGeometry(5,80,90,50);
  surePassWdLabel->setGeometry(5,140,90,50);

  userNameEdit->setGeometry(100,20,150,50);
  passWdEdit->setGeometry(100,80,150,50);
  surePassWdEdit->setGeometry(100,140,150,50);
  okButton->setGeometry(100,200,150,50);
}

UiLogin::UiLogin(QWidget *parent) :QWidget(parent)
{
  this->resize(1024,768);
  innerUi = 1;
  uLogin = new UserLogin(this);
  uLogin->move(200,200);
  uRegister = new UserRegister(this);
  uRegister->move(200,200);
  uRegister->hide();

  connect(uLogin->okButton,SIGNAL(clicked()),this,SLOT(UserLoginBt()));
  connect(uRegister->okButton,SIGNAL(clicked()),this,SLOT(UserRegisterBt()));
}

void UiLogin::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(Qt::gray);
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  if(innerUi)
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

void UiLogin::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(215,0,80,50).contains(event->pos()))
        {
          innerUi = 1;
          uRegister->hide();
          uLogin->show();
        }
      else if(QRect(727,0,807,50).contains(event->pos()))
        {
          innerUi = 0;
          uLogin->hide();
          uRegister->show();
        }
      update();
    }
}



void UiLogin::UserLoginBt()
{
  QSqlQuery query;
  QString name;
  name = uLogin->userNameEdit->text();

  query.prepare("SELECT * FROM Pwd where usrName=:um");
  query.bindValue(":um",name);
  query.exec();
  query.next();
  if(query.isValid())
    {
      if(query.value(0).toString()==name)
        {
          qDebug()<<query.value(0).toString();
          if(name=="root")
            {
              bool isOK;
              QString text = QInputDialog::getText(this, tr("提示"),
                                                   tr("请输入root密码"),
                                                   QLineEdit::Password,
                                                   "",
                                                   &isOK,Qt::Sheet);
              if(isOK)
                {
                  if(text!=query.value(1).toString())
                    QMessageBox::information(this,tr("警告"),tr("密码错误！"));
                  else
                    {
                      emit ChangeUi(2);
                    }
                }
            }

        }
    }
  else
    {
      if(name=="")
        QMessageBox::information(this,tr("警告"),tr("请输入用户名！"));
      else
        QMessageBox::information(this,tr("警告"),tr("用户名不存在！"));
    }
}

void  UiLogin::UserRegisterBt()
{
  qDebug()<<"register";
  QSqlQuery query;
  QString name;
  QString pwd;
  name = uRegister->userNameEdit->text();
  pwd = uRegister->passWdEdit->text();
  query.prepare("SELECT * FROM Pwd where usrName=:um");
  query.bindValue(":um",name);
  query.exec();
  query.next();
  if(query.isValid())
    {
      QMessageBox::information(this,tr("警告"),tr("用户已存在！"));
    }
  else
    {
      if(name=="")
        QMessageBox::information(this,tr("警告"),tr("用户名不能为空！"));
      else
        {
          if(uRegister->passWdEdit->text().size()<6)
            QMessageBox::information(this,tr("警告"),tr("新密码必须大于等于6位!"));
          else
            {
              if(uRegister->passWdEdit->text()!=uRegister->surePassWdEdit->text())
              QMessageBox::information(this,tr("警告"),tr("两次输入密码不一致，请重新输入！"));
              else
                {

                  query.prepare("INSERT INTO Pwd VALUES (:um,:pw)");
                  query.bindValue(":um",name);
                  query.bindValue(":pw",pwd);
                  qDebug()<< query.exec();
                  QMessageBox::information(this,tr("提示"),tr("注册成功,请还回登录！"));
                  innerUi = ~innerUi;
                  uRegister->hide();
                  uLogin->show();
                }
            }
        }
    }
  uRegister->userNameEdit->setText("");
  uRegister->passWdEdit->setText("");
  uRegister->surePassWdEdit->setText("");
}


