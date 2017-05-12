#include "UiRoot.h"
#include <QtSql>
#include <QtCore>

/**************************************************************************/
RootUser::RootUser(QWidget *parent) :QWidget(parent)
{
  this->resize(950,700);
  pwdModel  = new QSqlRelationalTableModel(this);
  pwdModel->setTable("Pwd");
  pwdModel->setHeaderData(0, Qt::Horizontal,tr("用户"));
  pwdModel->setHeaderData(1,Qt::Horizontal, tr("密码"));
  pwdModel->select();

  pwdView = new QTableView(this);
  pwdView->setModel(pwdModel);
  pwdView->setSelectionMode(QAbstractItemView::SingleSelection);
  pwdView->setSelectionBehavior(QAbstractItemView::SelectRows);
  pwdView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  pwdView->setColumnWidth(1,100);


  /******************************************************/
  modeModel  = new QSqlRelationalTableModel(this);
  modeModel->setTable("Mode");
  modeModel->setHeaderData(0, Qt::Horizontal,tr("模式名称"));
  modeModel->setHeaderData(1,Qt::Horizontal, tr("所属用户"));
  modeModel->setHeaderData(2,Qt::Horizontal, tr("膜泵"));
  modeModel->setHeaderData(3,Qt::Horizontal, tr("芯泵"));
  modeModel->setHeaderData(4,Qt::Horizontal, tr("膜温"));
  modeModel->setHeaderData(5,Qt::Horizontal, tr("芯温"));
  modeModel->setHeaderData(6,Qt::Horizontal, tr("水槽温1"));
  modeModel->setHeaderData(7,Qt::Horizontal, tr("空气间隙"));
  modeModel->setHeaderData(8,Qt::Horizontal, tr("DMAC"));
  modeModel->setHeaderData(9,Qt::Horizontal, tr("导丝速度1"));
  modeModel->setHeaderData(10,Qt::Horizontal, tr("导丝升降1"));
  modeModel->setHeaderData(11,Qt::Horizontal, tr("循环泵1"));
  modeModel->setHeaderData(12,Qt::Horizontal, tr("补液泵"));
  modeModel->setHeaderData(13,Qt::Horizontal, tr("水槽温2"));
  modeModel->setHeaderData(14,Qt::Horizontal, tr("导丝速度2"));
  modeModel->setHeaderData(15,Qt::Horizontal, tr("导丝升降2"));
  modeModel->setHeaderData(16,Qt::Horizontal, tr("循环泵2"));
  modeModel->setHeaderData(17,Qt::Horizontal, tr("水槽温3"));
  modeModel->setHeaderData(18,Qt::Horizontal, tr("收丝速度2"));
  modeModel->setHeaderData(19,Qt::Horizontal, tr("收丝升降2"));
  modeModel->setHeaderData(20,Qt::Horizontal, tr("循环泵3"));
  modeModel->select();

  modeView = new QTableView(this);
  modeView->setModel(modeModel);
  modeView->setColumnWidth(1,100);
  modeView->setSelectionMode(QAbstractItemView::SingleSelection);
  modeView->setSelectionBehavior(QAbstractItemView::SelectRows);
  modeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  /******************************************************/
  historyModel  = new QSqlRelationalTableModel(this);
  historyModel->setTable("History");
  historyModel->setHeaderData(0, Qt::Horizontal,tr("历史日期"));
  historyModel->setHeaderData(1,Qt::Horizontal, tr("所属用户"));
  historyModel->setHeaderData(2,Qt::Horizontal, tr("膜泵"));
  historyModel->setHeaderData(3,Qt::Horizontal, tr("芯泵"));
  historyModel->setHeaderData(4,Qt::Horizontal, tr("膜温"));
  historyModel->setHeaderData(5,Qt::Horizontal, tr("芯温"));
  historyModel->setHeaderData(6,Qt::Horizontal, tr("水槽温1"));
  historyModel->setHeaderData(7,Qt::Horizontal, tr("空气间隙"));
  historyModel->setHeaderData(8,Qt::Horizontal, tr("DMAC"));
  historyModel->setHeaderData(9,Qt::Horizontal, tr("导丝速度1"));
  historyModel->setHeaderData(10,Qt::Horizontal, tr("导丝升降1"));
  historyModel->setHeaderData(11,Qt::Horizontal, tr("循环泵1"));
  historyModel->setHeaderData(12,Qt::Horizontal, tr("补液泵"));
  historyModel->setHeaderData(13,Qt::Horizontal, tr("水槽温2"));
  historyModel->setHeaderData(14,Qt::Horizontal, tr("导丝速度2"));
  historyModel->setHeaderData(15,Qt::Horizontal, tr("导丝升降2"));
  historyModel->setHeaderData(16,Qt::Horizontal, tr("循环泵2"));
  historyModel->setHeaderData(17,Qt::Horizontal, tr("水槽温3"));
  historyModel->setHeaderData(18,Qt::Horizontal, tr("收丝速度2"));
  historyModel->setHeaderData(19,Qt::Horizontal, tr("收丝升降2"));
  historyModel->setHeaderData(20,Qt::Horizontal, tr("循环泵3"));
  historyModel->select();

  historyView = new QTableView(this);
  historyView->setModel(historyModel);
  historyView->setColumnWidth(0,300);
  historyView->setSelectionMode(QAbstractItemView::SingleSelection);
  historyView->setSelectionBehavior(QAbstractItemView::SelectRows);
  historyView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  deleteUserBt= new QPushButton(tr("删除用户"),this);
  deleteModeBt=new QPushButton(tr("删除模式"),this);
  deleteHistoryBt=new QPushButton(tr("删除历史"),this);
  /********************************************/
  pwdView->setGeometry(20,20,250,150);
  deleteUserBt->setGeometry(290,20,120,60);
  deleteModeBt->setGeometry(430,20,120,60);
  deleteHistoryBt->setGeometry(570,20,120,60);
  modeView->setGeometry(20,200,900,200);
  historyView->setGeometry(20,430,900,200);

  connect(pwdView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this, SLOT(updateMHView()));
  connect(deleteUserBt,SIGNAL(clicked()),this,SLOT(DeleteUser()));
}

void RootUser::updateMHView()
{
  QModelIndex index = pwdView->currentIndex();
  if (index.isValid()) {
      QSqlRecord record = pwdModel->record(index.row());
      QString name = record.value("usrName").toString();
      modeModel->setFilter(QString("usrName = '%1'").arg(name));
      historyModel->setFilter(QString("usrName = '%1'").arg(name));
    } else {
      modeModel->setFilter("departmentid = -1");
      historyModel->setFilter("departmentid = -1");
    }
  modeModel->select();
  modeView->horizontalHeader()->setVisible(modeModel->rowCount() > 0);
  historyModel->select();
  historyView->horizontalHeader()->setVisible(modeModel->rowCount() > 0);
}

void RootUser::DeleteUser()
{
  QModelIndex index = pwdView->currentIndex();
  QSqlQuery query;
  QString name;
  if (index.isValid())
    {
      QSqlRecord record = pwdModel->record(index.row());
      name = record.value("usrName").toString();
      if(name=="root")
        QMessageBox::information(this,tr("警告"),tr("root不能删除"));
      else
        {
          if(QMessageBox::information(this, tr("警告"), tr("确定删除用户以及用户数据?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)==QMessageBox::Yes)
            {
              query.exec(QString("DELETE FROM Pwd WHERE usrName = '%1'" ).arg(name));
              query.exec(QString("DELETE FROM Mode WHERE usrName = '%1'" ).arg(name));
              query.exec(QString("DELETE FROM History WHERE usrName = '%1'" ).arg(name));
              pwdModel->select();
              pwdView->update();
              modeModel->select();
              modeView->update();
              historyModel->select();
              historyView->update();
            }
        }
    }
  else
    {
    QMessageBox::information(this,tr("警告"),tr("请选择要删除用户"));
    }
}

bool RootUser::event(QEvent *e)
{
  if(e->type()==QEvent::Show)
    {
      qDebug()<< e->type();
      pwdModel->select();
      pwdView->update();
    }
}

/**************************************************************************/
RootPwd::RootPwd(QWidget *parent):QWidget(parent)
{
  this->resize(400,400);
  passWdLabel = new QLabel(tr("新密码 :"),this);
  passWdEdit =  new QLineEdit(this);
  surePassWdLabel = new QLabel(tr("确认密码 :"),this);
  surePassWdEdit =  new QLineEdit(this);
  okButton = new QPushButton(tr("确定修改"),this);

  passWdEdit->setEchoMode(QLineEdit::Password);
  surePassWdEdit->setEchoMode(QLineEdit::Password);


  passWdLabel->setGeometry(5,80,90,50);
  surePassWdLabel->setGeometry(5,140,90,50);

  passWdEdit->setGeometry(100,80,150,50);
  surePassWdEdit->setGeometry(100,140,150,50);
  okButton->setGeometry(100,200,150,50);

  connect(okButton,SIGNAL(clicked()),this,SLOT(ChangeRootPwd()));
}

void RootPwd::ChangeRootPwd()
{
  QSqlQuery query;
  QString pwd ;
  query.exec("select pwd from Pwd where usrName='root'");
  query.next();
  pwd = query.value(0).toString();
  if(passWdEdit->text()==surePassWdEdit->text())
    {
      qDebug()<<pwd;
      if(passWdEdit->text().size()<6)
        QMessageBox::information(this,tr("警告"),tr("新密码必须大于等于6位!"));
      else if(passWdEdit->text()==pwd)
        QMessageBox::information(this,tr("警告"),tr("新密码不能与旧密码相同!"));
      else
        {
          query.prepare("UPDATE Pwd SET pwd = :pw WHERE usrName='root' ");
          query.bindValue(":pw",passWdEdit->text());
          query.exec();
          QMessageBox::information(this,tr("提示"),tr("密码修改成功！"));
          update();
        }
    }
  else
    {
      QMessageBox::information(this,tr("警告"),tr("两次输入不一致，请重新输入！"));
    }

  passWdEdit->setText("");
  surePassWdEdit->setText("");
}
/**************************************************************************/
UiRoot::UiRoot(QWidget *parent) :QWidget(parent)
{
  this->resize(1024,768);
  innerUi =1 ;
  rootPwd = new RootPwd(this);
  rootPwd->move(100,100);
  rootUser = new RootUser(this);
  rootUser->move(50,50);
  rootUser->hide();
}

void UiRoot::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(Qt::gray);
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  if(innerUi)
    {
      painter.setPen(Qt::green);
      painter.setFont(QFont("Times", 15));
      painter.drawText(QRect(0,10,341,25),Qt::AlignCenter,tr("修改root密码"));
      painter.drawLine(115,40,225,40);
      painter.setPen(Qt::black);
      painter.drawText(QRect(341,10,341,25),Qt::AlignCenter,tr("用户管理"));
      painter.drawLine(470,40,550,40);
    }
  else
    {
      painter.setPen(Qt::black);
      painter.setFont(QFont("Times", 15));
      painter.drawText(QRect(0,10,341,25),Qt::AlignCenter,tr("修改root密码"));
      painter.drawLine(115,40,225,40);
      painter.setPen(Qt::green);
      painter.drawText(QRect(341,10,341,25),Qt::AlignCenter,tr("用户管理"));
      painter.drawLine(470,40,550,40);
    }
  painter.setPen(Qt::darkBlue);
  painter.drawText(QRect(682,10,341,25),Qt::AlignCenter,tr("还回登录"));
  painter.drawLine(815,40,890,40);

  painter.restore();
}

void UiRoot::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(115,0,110,50).contains(event->pos()))
        {
          innerUi = 1;
          rootUser->hide();
          rootPwd->show();
        }
      else if(QRect(470,0,80,50).contains(event->pos()))
        {
          innerUi = 0;
          rootPwd->hide();
          rootUser->show();
        }
      else if(QRect(815,0,75,50).contains(event->pos()))
        {
          emit ChangeUi(1);
        }
      update();
    }
}



