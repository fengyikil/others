#ifndef SPIN_H
#define SPIN_H

#include <QWidget>
#include <login.h>
class Top : public QWidget
{
  Q_OBJECT
  
public:
  Top(QWidget *parent = 0);
  ~Top();
  Login* login;
signals:

public slots:
  void UserLogin();
  void UserRegister();
};

#endif // SPIN_H
