#ifndef UIMODE_H
#define UIMODE_H

#include <QtGui>
#include <QtSql>
#include "EditBt.h"
class UiMode : public QWidget
{
  Q_OBJECT
public:
  explicit UiMode(QWidget *parent = 0);
  QSqlTableModel *model ;
  QTableView *tabView;
  QPushButton* lockButton;
  QPushButton* deleteModeButton;
  QPushButton* newModeButton;
  QPushButton* saveModeButton;
  QPushButton* runModeButton;

  bool isLock;
  QSqlRecord nowRecord;

  QLabel* l[4];
  EditBt* arrayEditBt[19];

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
  void showEvent(QShowEvent *);
  void hideEvent(QHideEvent *);
signals:
  void ChangeUi(int ui);
public slots:
  void ModeItemClicked();
  void DeleteMode();
  void NewMode();
  void LockMode();
  void SaveMode();
  void RunMode();
};
#endif // UIMODE_H
