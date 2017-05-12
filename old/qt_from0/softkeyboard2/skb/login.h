#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtGui>
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

class UserRegister : public QWidget
{
  Q_OBJECT
public:
  explicit UserRegister(QWidget *parent = 0);
  QLabel* userNameLabel;
  QLabel* passWdLabel;
  QLabel* rpassWdLabel;
  QLineEdit* userNameEdit;
  QLineEdit* passWdEdit;
  QLineEdit* rpassWdEdit;
  QPushButton* okButton;
signals:

public slots:

};
class Login : public QWidget
{
  Q_OBJECT
public:
  explicit Login(QWidget *parent = 0);
  UserLogin* uLogin;
  UserRegister* uRegister;
  int lor;
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
signals:
  
public slots:
  
};

#endif // LOGIN_H
