#ifndef MYSCROLL_H
#define MYSCROLL_H

#include <QWidget>

class myscroll : public QWidget
{
  Q_OBJECT
public:
  explicit myscroll(QWidget *parent = 0);
  
signals:
protected:
  void paintEvent(QPaintEvent *);
  void timerEvent(QTimerEvent *);
  void showEvent(QShowEvent *);
  void hideEvent(QHideEvent *);
  QPixmap* p1;
  QPixmap* p2;
  int myTimerId;
  QPoint save;
  QPoint now;
public slots:
  void draw_p1();
  
};

#endif // MYSCROLL_H
