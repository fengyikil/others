#ifndef UIUSR_H
#define UIUSR_H
#include <QtGui>
#include <QtSql>
#include "EditBt.h"
class UiHistory : public QWidget
{
  Q_OBJECT
public:
  explicit UiHistory(QWidget *parent = 0);
  QSqlTableModel *model ;
  QTableView *tabView;
  QPushButton* deleteHisButton;
  QPushButton* lockButton;

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
  void HistoryItemClicked();
  void DeleteHistory();
  void LockHistory();
};



#endif // UIUSR_H
