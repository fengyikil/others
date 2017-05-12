#ifndef TOP_H
#define TOP_H

#include <QWidget>
#include "view.h"
class top : public QWidget
{
  Q_OBJECT
public:
  explicit top(QWidget *parent = 0);
  
signals:
protected:
     void mousePressEvent(QMouseEvent *);
public slots:
private:
   view *vw;

};

#endif // TOP_H
