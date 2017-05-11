#ifndef MYINPUTPANEL_H
#define MYINPUTPANEL_H
#include <QtGui>
#include <QtCore>
#include <QWidget>

class MyInputPanel : public QWidget
{
  Q_OBJECT
public:
  explicit MyInputPanel(QWidget *parent = 0);
  ~MyInputPanel();
   QWidget *getFocusedWidget();
  int inputState;// 0 初始状态 空 1 有，无小数点 2 有，有小数点
  QString text;
  QString clickIndex;
  QRect textRect;
  QMap<QString,QRect> mapRect;
protected:
  bool event(QEvent *e);
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void mouseReleaseEvent(QMouseEvent*event);
  void hideEvent(QHideEvent *);
signals:
  void stringGenerated(QString t);
public slots:
   void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);

private:
  QWidget *lastFocusedWidget;
  
};

#endif // MYINPUTPANEL_H
