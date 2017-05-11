#ifndef ROOTVIEW_H
#define ROOTVIEW_H

#include <QtGui>
#include <QtSql>
//root 修改密码界面
class RootPwd : public QWidget
{
  Q_OBJECT
public:
  explicit RootPwd(QWidget *parent = 0);
  QLabel* passWdLabel;
  QLabel* surePassWdLabel;
  QLineEdit* passWdEdit;
  QLineEdit* surePassWdEdit;
  QPushButton* okButton;

signals:

public slots:
  void ChangeRootPwd();
};
//root用户管理界面
class RootUser : public QWidget
{
  Q_OBJECT
public:
 explicit RootUser(QWidget *parent = 0);
private:
  QSqlRelationalTableModel *pwdModel;
  QSqlRelationalTableModel *modeModel;
  QSqlRelationalTableModel *historyModel;
  QTableView *pwdView;
  QTableView *modeView;
  QTableView *historyView;
  QPushButton *deleteUserBt;
  QPushButton *deleteModeBt;
  QPushButton *deleteHistoryBt;
private slots:
  void updateMHView();
  void DeleteUser();
protected:
  bool event(QEvent*e);
  
};
//root主界面
class UiRoot : public QWidget
{
  Q_OBJECT
public:
  explicit UiRoot(QWidget *parent = 0);
  RootPwd* rootPwd;
  RootUser* rootUser;
  int innerUi;
protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*event);
signals:
void ChangeUi(int ui);
public slots:

};
#endif // ROOTVIEW_H
