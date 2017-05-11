#ifndef TOP_H
#define TOP_H
#include"curve.h"
#include <QWidget>

class top : public QWidget
{
  Q_OBJECT
  
public:
  top(QWidget *parent = 0);
  ~top();
  curve* ce;
};

#endif // TOP_H
