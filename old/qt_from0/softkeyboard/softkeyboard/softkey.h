#ifndef SOFTKEY_H
#define SOFTKEY_H
#include<QMouseEvent>
#include <QWidget>
#include<QMap>
#include<keyset.h>
class KeySet;
class SoftKey : public QWidget
{
  Q_OBJECT
  
public:
  SoftKey(QWidget *parent = 0);
  ~SoftKey();
  KeySet* nowSet;
  int inputState;// 0 初始状态 空 1 有，无小数点 2 有，有小数点
  QString text;
  QString clickIndex;
  QRect textRect;
  QMap<QString,QRect> mapRect;

   protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void mouseReleaseEvent(QMouseEvent*event);
  void hideEvent(QHideEvent *);
public slots:
  void ShowMove(QPoint);
};

#endif // SOFTKEY_H
