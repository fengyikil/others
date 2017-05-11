#ifndef UIRUN_H
#define UIRUN_H

#include <QtGui>
#include "EditBt.h"
class UiRun : public QWidget
{
  Q_OBJECT
public:
  explicit UiRun(QWidget *parent = 0);
  float value1;
  float value2;
  float value3;
  float value4;
  float value5;
  float value6;
  QLabel* l[4];
  EditBt* arrayEditBt[19];
  QPushButton* lockButton;
  QPushButton* pauseButton;
  QPushButton* shutDownButton;
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void showEvent(QShowEvent *);
  void hideEvent(QHideEvent *);
signals:
  void ChangeUi(int ui);
  
public slots:
  
};

#endif // UIRUN_H
