#include "UiMode.h"
#include "global.h"

UiMode::UiMode(QWidget *parent) : QWidget(parent)
{
  this->resize(1024,768);
  isLock = true;
  model = new QSqlTableModel(this);
  model->setTable("Mode");
  model->setHeaderData(0, Qt::Horizontal,tr("模式"));

  model->select();
  tabView = new QTableView(this);
  tabView->setModel(model);
  //  tabView->setColumnHidden(0,true);
  for(int i=1;i<22;i++)
    tabView->setColumnHidden(i,true);
  tabView->setColumnWidth(0,230);
  tabView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  deleteModeButton = new QPushButton(tr("删除模式"),this);
  lockButton  =new QPushButton(tr("解锁"),this);
  newModeButton = new QPushButton(tr("新建模式"),this);
  saveModeButton = new QPushButton(tr("保存编辑"),this);
  runModeButton = new QPushButton(tr("开始运行"),this);
  deleteModeButton->setEnabled(false);
  newModeButton->setEnabled(false);
  saveModeButton->setEnabled(false);

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
  deleteModeButton->setGeometry(10,570,250,50);
  newModeButton->setGeometry(10,640,250,50);

  saveModeButton->setGeometry(440,520,130,80);
  runModeButton->setGeometry(720,520,130,80);
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




  connect(tabView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this, SLOT(ModeItemClicked()));
  connect(lockButton,SIGNAL(clicked()),this,SLOT(LockMode()));
  connect(deleteModeButton,SIGNAL(clicked()),this,SLOT(DeleteMode()));
  connect(newModeButton,SIGNAL(clicked()),this,SLOT(NewMode()));
  connect(saveModeButton,SIGNAL(clicked()),this,SLOT(SaveMode()));
  connect(runModeButton,SIGNAL(clicked()),this,SLOT(RunMode()));



}

void UiMode::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();

  painter.setBrush(QColor(85, 196, 255));
  painter.setPen(Qt::NoPen);
  painter.drawRect(QRect(0,0,1024,50));

  painter.setPen(Qt::green);
  painter.setFont(QFont("Times", 15));
  painter.drawText(QRect(190,10,341,25),Qt::AlignCenter,tr("模式"));
//  painter.drawLine(295,40,405,40);

  painter.setPen(Qt::red);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawArc(QRect(900,10,35,35),90*16,-270*16);

  painter.restore();
}

void UiMode::mousePressEvent(QMouseEvent *event)
{

  if(event->button() & Qt::LeftButton)
    {
      if(QRect(900,0,40,40).contains(event->pos()))
        {
          qDebug()<<"commmmmmmmmmmmm";
          ChangeUi(3);
        }
    }
  update();
}

void UiMode::showEvent(QShowEvent *)
{
  model->setFilter(QString("usrName = '%1'").arg(global->loginName));

  tabView->selectRow(1);

}

void UiMode::hideEvent(QHideEvent *)
{
  isLock = true;
  lockButton->setText(tr("解锁"));
  deleteModeButton->setEnabled(false);
  newModeButton->setEnabled(false);
  saveModeButton->setEnabled(false);
  isLock = true;
  for(int i =0;i<19;i++)
    arrayEditBt[i]->SetIuput(false);
  qDebug()<<"hide"<<isLock;
}


void UiMode::ModeItemClicked()
{
  nowRecord = model->record(tabView->currentIndex().row());
  //  qDebug()<< tabView->currentIndex().row();
  //  qDebug()<<nowRecord.value(1);
  int i=0;
  if(!isLock)
    {
      while(nowRecord.value(i+2).toString()!=NULL)
        {
          //          arrayEditBt[i]->textValue = nowRecord.value(i+2).toString();
          arrayEditBt[i]->SetText(nowRecord.value(i+2).toString());
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
          //          arrayEditBt[i]->textValue ="";
          arrayEditBt[i]->SetText("");
          //                 arrayEditBt[i]->update();
          //          qDebug()<<nowRecord.value(i)<<i;
          i++;
        }
    }
  //QSqlRecord recd = model
  update();
}

void UiMode::DeleteMode()
{
  int row = tabView->currentIndex().row();
  model->removeRow(tabView->currentIndex().row());
  //   tabView->setCurrentIndex();
  tabView->selectRow(row-1);
}
void UiMode::SaveMode()
{
  QSqlQuery query;
  int index= tabView->currentIndex().row();
  nowRecord = model->record(index);
  qDebug()<<nowRecord.value(0).toString();
  query.prepare("UPDATE Mode SET j1=:j1,j2=:j2,j3=:j3,j4=:j4,\
                l1=:l1,l2=:l2,l3=:l3,l4=:l4,l5=:l5,l6=:l6,l7=:l7,\
                q1=:q1,q2=:q2,q3=:q3,q4=:q4,\
                s1=:s1,s2=:s2,s3=:s3,s4=:s4\
      where modeName=:modeName");

      query.bindValue(":j1",arrayEditBt[0]->value);
      query.bindValue(":j2",arrayEditBt[1]->value);
  query.bindValue(":j3",arrayEditBt[2]->value);
  query.bindValue(":j4",arrayEditBt[3]->value);

  query.bindValue(":l1",arrayEditBt[4]->value);
  query.bindValue(":l2",arrayEditBt[5]->value);
  query.bindValue(":l3",arrayEditBt[6]->value);
  query.bindValue(":l4",arrayEditBt[7]->value);
  query.bindValue(":l5",arrayEditBt[8]->value);
  query.bindValue(":l6",arrayEditBt[9]->value);
  query.bindValue(":l7",arrayEditBt[10]->value);

  query.bindValue(":q1",arrayEditBt[11]->value);
  query.bindValue(":q2",arrayEditBt[12]->value);
  query.bindValue(":q3",arrayEditBt[13]->value);
  query.bindValue(":q4",arrayEditBt[14]->value);

  query.bindValue(":s1",arrayEditBt[15]->value);
  query.bindValue(":s2",arrayEditBt[16]->value);
  query.bindValue(":s3",arrayEditBt[17]->value);
  query.bindValue(":s4",arrayEditBt[18]->value);

  query.bindValue(":modeName",nowRecord.value(0).toString());
  qDebug()<<query.exec();
  model->select();
  tabView->update();
  tabView->selectRow(index);

}

void UiMode::RunMode()
{
  QMessageBox::information(this,tr("提示"),tr("你选择了"),QMessageBox::Yes,QMessageBox::No);
  ChangeUi(6);
}
void UiMode::NewMode()
{
  QSqlQuery query;
  bool isOK;
  QString text = QInputDialog::getText(this, tr("提示"),
                                       tr("请输入模式名称"),
                                       QLineEdit::Normal,
                                       "",
                                       &isOK,Qt::Sheet);
  query.exec(QString("SELECT * FROM Mode where modeName = '%1' and usrName ='%2'").arg(text).arg(global->loginName));
  query.next();
  qDebug()<<query.value(0);
  if(text=="")
    {
      QMessageBox::information(this,tr("警告"),tr("名称不能为空"));
      return;
    }
  else if(query.isValid())
    {
      QMessageBox::information(this,tr("警告"),tr("名称已经存在"));
    }
  else
    {
      query.exec(QString("INSERT INTO Mode VALUES ('%1','%2',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(text).arg(global->loginName));
      model->select();
      tabView->update();
      tabView->selectRow(model->rowCount()-1);
    }
}


void UiMode::LockMode()
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
              deleteModeButton->setEnabled(true);
              newModeButton->setEnabled(true);
              saveModeButton->setEnabled(true);
              isLock = false;
              for(int i =0;i<19;i++)
                arrayEditBt[i]->SetIuput(true);
              ModeItemClicked();
            }
        }

    }
  else
    {
      lockButton->setText(tr("解锁"));
      deleteModeButton->setEnabled(false);
      newModeButton->setEnabled(false);
      saveModeButton->setEnabled(false);
      isLock = true;
      for(int i =0;i<19;i++)
        arrayEditBt[i]->SetIuput(false);

      ModeItemClicked();
    }
}

