#ifndef TOP_H
#define TOP_H

#include <QWidget>
#include "myscroll.h"
class top : public QWidget
{
  Q_OBJECT
  
public:
  top(QWidget *parent = 0);
  myscroll* msc;
  ~top();
};

#endif // TOP_H
