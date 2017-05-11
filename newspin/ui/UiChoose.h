#ifndef UICHOOSE_H
#define UICHOOSE_H

#include <QtGui>
#include <QtSql>
#include "EditBt.h"
class UiChoose : public QWidget
{
  Q_OBJECT
public:
  explicit UiChoose(QWidget *parent = 0);
  QPushButton* historyButton;
  QPushButton* modeButton;
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
signals:
  void ChangeUi(int ui);
public slots:
    void ChooseHistory();
    void ChooseMode();
};

#endif // UICHOOSE_H
