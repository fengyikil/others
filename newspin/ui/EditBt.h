#ifndef EDITBT_H
#define EDITBT_H

#include <QWidget>
#include <QKeyEvent>
class EditBt : public QWidget
{
  Q_OBJECT
public:
  explicit EditBt(QString IName,QString UName,bool isinput,QWidget *parent = 0);
  QString itemName;
  QString unitName;
  QString textValue;
  float   value;
  bool isInput;
  bool isLock;
  int inputState;// 0 初始状态 空 1 有，无小数点 2 有，有小数点

   void SetIuput(bool);
   void SetText(QString);
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void keyPressEvent(QKeyEvent *e);
signals:
  void SendEnter(float);
public slots:

};

#endif // EDITBT_H
