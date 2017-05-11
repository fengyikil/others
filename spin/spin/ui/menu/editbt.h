#ifndef EDITBT_H
#define EDITBT_H

#include <QWidget>
#include <QKeyEvent>
#include <type.h>
class EditBt : public QWidget
{
  Q_OBJECT
public:
  explicit EditBt(QWidget *parent = 0);
  QString itemName;
  QString unitName;
  int slave;
  float   value;
  void SetItemName(QString s){itemName = s;}
  QString GetItemName(){return itemName;}
  void SetUnitName(QString s){unitName = s;}
  QString GetUnitName(){return unitName;}
  void SetValue(float v){value=v;}
  float GetValue(){return value;}
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
   void keyPressEvent(QKeyEvent *e);
signals:
  void SendMesg(struct MdMesg);
public slots:
  
};

#endif // EDITBT_H
