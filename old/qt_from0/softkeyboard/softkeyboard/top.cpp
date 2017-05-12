#include "top.h"

Top::Top(QWidget *parent)
  : QWidget(parent)
{
  resize(1024,768);
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Background,QColor(97,174,229)));//设置背景颜色
  keyTest = new KeySet(this);
  keyTest->keyPoint = QPoint(10,135);
  keyTest->SetItemName(tr("分频器"));
  keyTest->SetUnitName(tr("(r/min)"));
  keyTest->SetValue(89.99);
  keyTest->move(50,50);

  keyTest1 = new KeySet(this);
  keyTest1->keyPoint = QPoint(140,135);
  keyTest1->SetItemName(tr("台达电机"));
  keyTest1->SetUnitName(tr("(r/min)"));
  keyTest1->SetValue(500);
  keyTest1->move(211,50);

  keyTest2 = new KeySet(this);
  keyTest2->keyPoint = QPoint(270,135);
  keyTest2->SetItemName(tr("温控器"));
  keyTest2->SetUnitName(tr("(℃)"));
  keyTest2->SetValue(500);
  keyTest2->move(372,50);

  g_softKey = new SoftKey(this);
  g_softKey->move(200,200);
  g_softKey->hide();

  connect(keyTest,SIGNAL(clicked(QPoint)),g_softKey,SLOT(ShowMove(QPoint)));
  connect(keyTest1,SIGNAL(clicked(QPoint)),g_softKey,SLOT(ShowMove(QPoint)));
  connect(keyTest2,SIGNAL(clicked(QPoint)),g_softKey,SLOT(ShowMove(QPoint)));

}

Top::~Top()
{
  
}
