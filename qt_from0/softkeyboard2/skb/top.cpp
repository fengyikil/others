#include "top.h"

Top::Top(QWidget *parent)
  : QWidget(parent)
{
  this->resize(1024,768);
  login = new Login(this);
  connect(login->uLogin->okButton,SIGNAL(clicked()),this,SLOT(UserLogin()));
  connect(login->uLogin->okButton,SIGNAL(clicked()),this,SLOT(UserRegister()));
}

Top::~Top()
{
  
}

void Top::UserLogin()
{
//  QTextEdit *displayTextEdit=new QTextEdit(this);
//  displayTextEdit->show();
  bool ok;

     QString name = QInputDialog::getText(this,
                                          tr("用户名"),
                                          tr("请输入新的用户名:"),
                                          QLineEdit::Normal,
                                          "name",
                                          &ok,Qt::Dialog);
     if(ok && !name.isEmpty()) {
        qDebug()<<name;
     }

//  QInputDialog myDlg(this);

//myDlg.getDouble(this, tr("QInputDialog::getDouble()"),tr("Amount:"), 37.56,0x00000004);

}

void Top::UserRegister()
{
}
