#ifndef SPIN_H
#define SPIN_H

#include <QWidget>
#include <UiLogin.h>
#include <UiRoot.h>
class Top : public QWidget
{
  Q_OBJECT
  
public:
  Top(QWidget *parent = 0);
  ~Top();
  UiLogin* uiLogin;
  UiRoot* uiRoot;
signals:

public slots:
  void SwitchUi(int ui);
};

#endif // SPIN_H
