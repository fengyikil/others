#include "UiTop.h"
#include <QtSql>
Top::Top(QWidget *parent)
  : QWidget(parent)
{
  this->resize(1024,768);
  uiLogin = new UiLogin(this);
  uiRoot =  new UiRoot(this);
  uiChoose = new UiChoose(this);
  uiHistory = new UiHistory(this);
  uiMode = new UiMode(this);
  uiRun = new UiRun(this);
//    uiLogin->hide();
  uiRoot->hide();
  uiChoose->hide();
  uiHistory->hide();
  uiMode->hide();
  uiRun->hide();
  connect(uiLogin,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
  connect(uiRoot,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
  connect(uiChoose,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
  connect(uiHistory,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
  connect(uiMode,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
   connect(uiRun,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));

}

Top::~Top()
{
  
}

void Top::SwitchUi(int ui)
{
  QWidget* last = qobject_cast<QWidget*>(sender());
  last->hide();
  switch (ui) {
    case 1:
      uiLogin->show();
      break;
    case 2:
      uiRoot->show();
      break;
    case 3:
      uiChoose->show();
      break;
    case 4:
      uiHistory->show();
      break;
    case 5:
      uiMode->show();
      break;
    case 6:
      uiRun->show();
      break;
    default:
      break;
    }
}
