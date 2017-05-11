#include "menu_top.h"

MenuTop::MenuTop(QWidget *parent) :
  QWidget(parent)
{
  resize(1024,768);
     this->setAutoFillBackground(true);
       QPalette palette;
       QPixmap pixmap( "/home/kil/share/pic/b10.jpg");
       palette.setBrush(QPalette::Window, QBrush(pixmap));
       this->setPalette(palette);
       head = new Head(this);
  sampleValue= new SampleValue(this);
  sampleValue->move(70,100);

  bt1 = new EditBt(this);
  bt1->slave = 1;
  bt1->SetItemName(QObject::tr("凝固域水温"));
  bt1->SetUnitName(tr("℃"));
  bt1->SetValue(0);
  bt1->move(110,180);


  bt2 = new EditBt(this);
  bt2->slave = 1;
  bt2->SetItemName(QObject::tr("DMC浓度"));
  bt2->SetUnitName(tr("%"));
  bt2->SetValue(0);
  bt2->move(270,180);

  bt3 = new EditBt(this);
  bt3->SetItemName(QObject::tr("喷丝板高度"));
  bt3->SetUnitName(tr("cm"));
  bt3->SetValue(0);
  bt3->move(430,180);

  bt4 = new EditBt(this);
  bt4->SetItemName(QObject::tr("导丝轮1高度"));
  bt4->SetUnitName(tr("cm"));
  bt4->SetValue(0);
  bt4->move(590,180);

  bt5 = new EditBt(this);
  bt5->SetItemName(QObject::tr("导丝轮1速度"));
  bt5->SetUnitName(tr("m/min"));
  bt5->SetValue(0);
  bt5->move(750,180);


  bt6 = new EditBt(this);
  bt6->SetItemName(QObject::tr("循环水泵流速"));
  bt6->SetUnitName(tr("ml/min"));
  bt6->SetValue(0);
  bt6->move(110,280);

  bt7 = new EditBt(this);
  bt7->SetItemName(QObject::tr("补充水泵流速"));
  bt7->SetUnitName(tr("ml/min"));
  bt7->SetValue(0);
  bt7->move(270,280);

  bt8 = new EditBt(this);
  bt8->SetItemName(QObject::tr("清洗槽水温"));
  bt8->SetUnitName(tr("cm"));
  bt8->SetValue(0);
  bt8->move(110,380);

  bt9 = new EditBt(this);
  bt9->SetItemName(QObject::tr("导丝轮2高度"));
  bt9->SetUnitName(tr("cm"));
  bt9->SetValue(0);
  bt9->move(270,380);

  bt10 = new EditBt(this);
  bt10->SetItemName(QObject::tr("导丝轮2速度"));
  bt10->SetUnitName(tr("m/min"));
  bt10->SetValue(0);
  bt10->move(430,380);

  bt11 = new EditBt(this);
  bt11->SetItemName(QObject::tr("循环水泵1流速"));
  bt11->SetUnitName(tr("ml/min"));
  bt11->SetValue(0);
  bt11->move(590,380);

  bt12 = new EditBt(this);
  bt12->SetItemName(QObject::tr("收丝槽水温"));
  bt12->SetUnitName(tr("℃"));
  bt12->SetValue(0);
  bt12->move(110,480);

  bt13 = new EditBt(this);
  bt13->SetItemName(QObject::tr("收丝轮速度"));
  bt13->SetUnitName(tr("cm"));
  bt13->SetValue(0);
  bt13->move(270,480);

  bt14 = new EditBt(this);
  bt14->SetItemName(QObject::tr("收丝轮循环速度"));
  bt14->SetUnitName(tr("m/min"));
  bt14->SetValue(0);
  bt14->move(430,480);

  bt15 = new EditBt(this);
  bt15->SetItemName(QObject::tr("循环水泵2流速"));
  bt15->SetUnitName(tr("ml/min"));
  bt15->SetValue(0);
  bt15->move(590,480);

  bt16 = new EditBt(this);
  bt16->SetItemName(QObject::tr("膜液泵流速"));
  bt16->SetUnitName(tr("ml/min"));
  bt16->SetValue(0);
  bt16->move(110,580);

  bt17 = new EditBt(this);
  bt17->SetItemName(QObject::tr("新液泵流速"));
  bt17->SetUnitName(tr("ml/min"));
  bt17->SetValue(0);
  bt17->move(270,580);

  connect(bt1,SIGNAL(SendMesg(MdMesg)),this,SIGNAL(SendMesg(MdMesg)));
}
