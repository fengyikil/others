#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtGui>
//Login用户登录界面
class UserLogin : public QWidget
{
  Q_OBJECT
public:
  explicit UserLogin(QWidget *parent = 0);
  QLabel* userNameLabel;
  QLineEdit* userNameEdit;
  QPushButton* okButton;

signals:

public slots:

};
//Login用户注册界面
class UserRegister : public QWidget
{
  Q_OBJECT
public:
  explicit UserRegister(QWidget *parent = 0);
  QLabel* userNameLabel;
  QLabel* passWdLabel;
  QLabel* surePassWdLabel;
  QLineEdit* userNameEdit;
  QLineEdit* passWdEdit;
  QLineEdit* surePassWdEdit;
  QPushButton* okButton;
signals:

public slots:

};
//Login主界面
class UiLogin : public QWidget
{
  Q_OBJECT
public:
  explicit UiLogin(QWidget *parent = 0);
  UserLogin* uLogin;
  UserRegister* uRegister;
  int innerUi;
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
signals:
  void ChangeUi(int ui);
public slots:
  void UserLoginBt();
  void UserRegisterBt();
};

#endif // LOGIN_H



