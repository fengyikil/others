#include "UiHistory.h"
#include "global.h"
#include<QPainter>
UiHistory::UiHistory(QWidget *parent):QWidget(parent)
{
  this->resize(1024,768);
  isLock = true;
  model = new QSqlTableModel(this);
  model->setTable("History");
  model->setHeaderData(1, Qt::Horizontal,tr("历史记录"));
  model->select();
  tabView = new QTableView(this);
  tabView->setModel(model);
  tabView->setColumnHidden(0,true);
  for(int i=2;i<23;i++)
    tabView->setColumnHidden(i,true);
  tabView->setColumnWidth(1,230);
  tabView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  deleteHisButton = new QPushButton(tr("删除记录"),this);
  lockButton  =new QPushButton(tr("解锁"),this);
  deleteHisButton->setEnabled(false);


  arrayEditBt[0] = new EditBt(tr("膜液泵流速"),tr("ml/min"),false,this);
  arrayEditBt[1] =  new EditBt(tr("芯液泵流速"),tr("ml/min"),false,this);
  arrayEditBt[2] =  new EditBt(tr("膜液泵温度"),tr("℃"),false,this);
  arrayEditBt[3] =  new EditBt(tr("芯液泵温度"),tr("℃"),false,this);

  arrayEditBt[4] =  new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[5] =  new EditBt(tr("空气间隙"),tr("mm"),false,this);
  arrayEditBt[6] =  new EditBt(tr("DMAC浓度"),tr("%"),false,this);
  arrayEditBt[7] =  new EditBt(tr("导丝轮速度"),tr("m/min"),false,this);


  arrayEditBt[8] =  new EditBt(tr("导丝轮升降"),tr("个/秒"),false,this);
  arrayEditBt[9] =  new EditBt(tr("循环泵流速"),tr("l/min"),false,this);
  arrayEditBt[10] =  new EditBt(tr("补充泵流速"),tr("l/min"),false,this);


  arrayEditBt[11] =   new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[12] =   new EditBt(tr("导丝轮升降"),tr("个/秒"),false,this);
  arrayEditBt[13] =  new EditBt(tr("导丝轮速度"),tr("m/min"),false,this);
  arrayEditBt[14] =   new EditBt(tr("循环泵流速"),tr("l/min"),false,this);

  arrayEditBt[15] =   new EditBt(tr("水槽温度"),tr("℃"),false,this);
  arrayEditBt[16] =   new EditBt(tr("收丝轮循环"),tr("cm/min"),false,this);
  arrayEditBt[17] =   new EditBt(tr("收丝轮速度"),tr("m/min"),false,this);
  arrayEditBt[18] =   new EditBt(tr("循环泵流速"),tr("℃"),false,this);

  l[0] = new QLabel(tr("计量泵"),this);
  l[1] = new QLabel(tr("凝固域"),this);
  l[2] = new QLabel(tr("清洗槽"),this);
  l[3] = new QLabel(tr("收丝槽"),this);
  QPalette pe;
  pe.setColor(QPalette::WindowText,Qt::blue);
  l[0]->setPalette(pe);
  l[1]->setPalette(pe);
  l[2]->setPalette(pe);
  l[3]->setPalette(pe);
  //  arrayEditBt[4] =  new EditBt(tr("水槽温度"),tr("℃"),false,this);
  tabView->setGeometry(10,70,250,400);
  lockButton->setGeometry(10,500,250,50);
  deleteHisButton->setGeometry(10,570,250,50);

  l[0]->setGeometry(330,70,100,25);
  l[1]->setGeometry(471,70,100,25);

  l[2]->setGeometry(753,70,100,25);
  l[3]->setGeometry(894,70,100,25);
  arrayEditBt[0]->setGeometry(300,120,131,81);
  arrayEditBt[1]->setGeometry(300,220,131,81);
  arrayEditBt[2]->setGeometry(300,320,131,81);
  arrayEditBt[3]->setGeometry(300,420,131,81);

  arrayEditBt[4]->setGeometry(441,120,131,81);
  arrayEditBt[5]->setGeometry(441,220,131,81);
  arrayEditBt[6]->setGeometry(441,320,131,81);
  arrayEditBt[7]->setGeometry(441,420,131,81);

  arrayEditBt[8]->setGeometry(582,120,131,81);
  arrayEditBt[9]->setGeometry(582,220,131,81);
  arrayEditBt[10]->setGeometry(582,320,131,81);

  arrayEditBt[11]->setGeometry(723,120,131,81);
  arrayEditBt[12]->setGeometry(723,220,131,81);
  arrayEditBt[13]->setGeometry(723,320,131,81);
  arrayEditBt[14]->setGeometry(723,420,131,81);

  arrayEditBt[15]->setGeometry(864,120,131,81);
  arrayEditBt[16]->setGeometry(864,220,131,81);
  arrayEditBt[17]->setGeometry(864,320,131,81);
  arrayEditBt[18]->setGeometry(864,420,131,81);




  connect(tabView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this, SLOT(HistoryItemClicked()));
  connect(deleteHisButton,SIGNAL(clicked()),this,SLOT(DeleteHistory()));
  connect(lockButton,SIGNAL(clicked()),this,SLOT(LockHistory()));
}

void UiHistory::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(QColor(85, 196, 255));
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  painter.setPen(Qt::green);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(190,10,341,25),Qt::AlignCenter,tr("历史"));
//  painter.setPen(Qt::blue);
//  painter.setFont(QFont("Times", 15));
//  painter.drawText(QRect(768,10,256,25),Qt::AlignCenter,tr("还回"));
//  painter.drawLine(870,40,920,40);
  painter.setPen(Qt::red);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawArc(QRect(900,10,35,35),90*16,-270*16);

  painter.restore();
  //   QWidget::paintEvent(e);

  qDebug()<<"parent";
}

void UiHistory::mousePressEvent(QMouseEvent *event)
{
  if(event->button() & Qt::LeftButton)
    {
      if(QRect(900,0,40,40).contains(event->pos()))
        {
          ChangeUi(3);
        }
    }
  update();
}

void UiHistory::showEvent(QShowEvent *)
{
  model->setFilter(QString("usrName = '%1'").arg(global->loginName));
}

void UiHistory::hideEvent(QHideEvent *)
{
  isLock = true;
  lockButton->setText(tr("解锁"));
  deleteHisButton->setEnabled(false);
  qDebug()<<"hide"<<isLock;
}


void UiHistory::HistoryItemClicked()
{
  nowRecord = model->record(tabView->currentIndex().row());
  //  qDebug()<< tabView->currentIndex().row();
  //  qDebug()<<nowRecord.value(1);
  int i=0;
  if(!isLock)
    {
      while(nowRecord.value(i+3).toString()!=NULL)
        {
          arrayEditBt[i]->textValue = nowRecord.value(i+3).toString();
          //           arrayEditBt[i]->update();
          //          qDebug()<<nowRecord.value(i)<<i;
          i++;
        }
      //      update();
    }
  else
    {
      while(i<19)
        {
          arrayEditBt[i]->textValue ="";
          //                 arrayEditBt[i]->update();
          //          qDebug()<<nowRecord.value(i)<<i;
          i++;
        }
    }
  //QSqlRecord recd = model
  update();
}

void UiHistory::DeleteHistory()
{
    model->removeRow(tabView->currentIndex().row());
}

void UiHistory::LockHistory()
{
  QSqlQuery query;


  if(isLock)
    {
      query.prepare("SELECT * FROM Pwd where usrName=:um");
      query.bindValue(":um",global->loginName);
      query.exec();
      query.next();

      bool isOK;
      QString text = QInputDialog::getText(this, tr("提示"),
                                           tr("请输入用户密码"),
                                           QLineEdit::Password,
                                           "",
                                           &isOK,Qt::Sheet);
      if(isOK)
        {
          if(text!=query.value(1).toString())
            QMessageBox::information(this,tr("警告"),tr("密码错误！"));
          else
            {
              lockButton->setText(tr("关锁"));
              isLock = false;
              deleteHisButton->setEnabled(true);

              HistoryItemClicked();
            }
        }

    }
  else
    {
      lockButton->setText(tr("解锁"));
      //      int i =0;

      isLock = true;
      deleteHisButton->setEnabled(false);
      HistoryItemClicked();
    }
  //  UpDate();
}







