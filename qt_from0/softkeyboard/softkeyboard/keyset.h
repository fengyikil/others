#ifndef KEYSET_H
#define KEYSET_H
#include <softkey.h>
#include <QWidget>
#include <linux/input.h>
class KeySet : public QWidget
{
  Q_OBJECT
public:
  explicit KeySet(QWidget *parent = 0);
  QPoint keyPoint;
  QString itemName;
  QString unitName;
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
signals:
  void clicked(QPoint);
public slots:
  
};

#endif // KEYSET_H
