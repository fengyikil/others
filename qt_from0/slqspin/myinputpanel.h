#ifndef MYINPUTPANEL_H
#define MYINPUTPANEL_H
#include <QtGui>
#include <QtCore>
#include <QWidget>

class MyInputPanel : public QDialog
{
  Q_OBJECT
public:
  explicit MyInputPanel(QWidget *parent = 0);
  ~MyInputPanel();
   QWidget *getFocusedWidget();
  int capsLock;
  QString clickIndex;
  QMap<QRect,QString> mapRect;

  void changeCaps();
protected:
  bool event(QEvent *e);
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void mouseReleaseEvent(QMouseEvent*event);
  void hideEvent(QHideEvent *);
signals:
  void stringGenerated(int t);
public slots:
   void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);

private:
  QWidget *lastFocusedWidget;
  
};
inline bool operator < (const QRect &key1, const QRect &key2)
{
  if(key1.x()<key2.x())
    return 1;
  else if(key1.x()==key2.x())
    {
      if(key1.y()<key2.y())
         return 1;
      else
        return 0;
    }
  else
    return 0;
};
#endif // MYINPUTPANEL_H
