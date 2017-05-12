#include "UiTop.h"
#include <QtSql>
Top::Top(QWidget *parent)
  : QWidget(parent)
{
  this->resize(1024,768);
  uiLogin = new UiLogin(this);
  uiRoot =  new UiRoot(this);
  uiLogin->hide();
  connect(uiLogin,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
  connect(uiRoot,SIGNAL(ChangeUi(int)),this,SLOT(SwitchUi(int)));
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
    default:
      break;
    }
}
