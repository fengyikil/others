#ifndef SPIN_H
#define SPIN_H

#include <QWidget>
#include <ui/UiLogin.h>
#include <ui/UiRoot.h>
#include <ui/UiHistory.h>
#include <ui/UiChoose.h>
#include <ui/UiMode.h>
#include <ui/UiRun.h>
class Top : public QWidget
{
  Q_OBJECT
  
public:
  Top(QWidget *parent = 0);
  ~Top();
  UiLogin* uiLogin;
  UiRoot* uiRoot;
  UiChoose*  uiChoose;
  UiHistory*  uiHistory;
  UiMode* uiMode;
  UiRun* uiRun;
signals:

public slots:
  void SwitchUi(int ui);
};

#endif // SPIN_H
