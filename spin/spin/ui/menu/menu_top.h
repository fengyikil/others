#ifndef MENU_TOP_H
#define MENU_TOP_H

#include <QWidget>
#include "editbt.h"
#include "samplevalue.h"
#include "head.h"
class MenuTop : public QWidget
{
  Q_OBJECT
public:
  explicit MenuTop(QWidget *parent = 0);
  Head* head;
  SampleValue* sampleValue;
  EditBt* bt1;
  EditBt* bt2;
  EditBt* bt3;
  EditBt* bt4;
  EditBt* bt5;
  EditBt* bt6;
  EditBt* bt7;
  EditBt* bt8;
  EditBt* bt9;
  EditBt* bt10;
  EditBt* bt11;
  EditBt* bt12;
  EditBt* bt13;
  EditBt* bt14;
  EditBt* bt15;
  EditBt* bt16;
  EditBt* bt17;
signals:
  void SendMesg(struct MdMesg);
public slots:
  
};

#endif // MENU_TOP_H
