#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
#include <type.h>
extern struct AdData adData;
extern unsigned  short bjData;
MainMenu::MainMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainMenu)
{
  ui->setupUi(this);
  timer = new QTimer(this);
  timer->start(1000);
  connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
}

MainMenu::~MainMenu()
{
  delete ui;
}

void MainMenu::Update()
{

  ui->label_t1->setText(QString::number(adData.us[0]));
  ui->label_t2->setText(QString::number(adData.us[1]));
  ui->label_t3->setText(QString::number(adData.us[2]));
  ui->label_t4->setText(QString::number(adData.us[3]));
  ui->label_t5->setText(QString::number(adData.us[4]));
  ui->label_t6->setText(QString::number(adData.us[5]));
  ui->label_t7->setText(QString::number(adData.us[6]));
  ui->label_t8->setText(QString::number(adData.us[7]));
  ui->label_t9->setText(QString::number(adData.us[8]));
  ui->label_t10->setText(QString::number(adData.us[9]));
  ui->label_t11->setText(QString::number(adData.us[10]));
  ui->label_t12->setText(QString::number(adData.us[11]));
  ui->label_t13->setText(QString::number(adData.us[12]));
  ui->label_t14->setText(QString::number(adData.us[13]));
  ui->label_t15->setText(QString::number(adData.us[14]));
  ui->label_t16->setText(QString::number(adData.us[15]));
  ui->label_t17->setText(QString::number(adData.us[16]));
  ui->label_t18->setText(QString::number(adData.us[17]));
  ui->label_t19->setText(QString::number(adData.us[18]));
  ui->label_t20->setText(QString::number(adData.us[19]));
  ui->label_t21->setText(QString::number(adData.us[20]));
  ui->label_t22->setText(QString::number(adData.us[21]));
  ui->label_t23->setText(QString::number(adData.us[22]));
  ui->label_t24->setText(QString::number(adData.us[23]));
  ui->label_t25->setText(QString::number(adData.us[24]));
  ui->label_t26->setText(QString::number(adData.us[25]));
  ui->label_t27->setText(QString::number(adData.us[26]));
  ui->label_t28->setText(QString::number(adData.us[27]));
  ui->label_t29->setText(QString::number(adData.us[28]));
  ui->label_t30->setText(QString::number(adData.us[29]));
  ui->label_t31->setText(QString::number(adData.us[30]));
  ui->label_t32->setText(QString::number(adData.us[31]));
  ui->label_t33->setText(QString::number(adData.us[32]));

  ui->label_ts1->setText(QString::number(adData.ui[0]));
  ui->label_ts2->setText(QString::number(adData.ui[1]));
  ui->label_ts3->setText(QString::number(adData.ui[2]));

  ui->label_tb->setText(QString::number(bjData));

  double tmp;
  tmp = adData.us[22];
  tmp =((tmp - 819)/3176)*10.0;
  ui->label_xy->setText(QString::number(tmp,'g',5));

  tmp = adData.us[23];
  tmp =((tmp - 819)/3176)*10.0;
  ui->label_my->setText(QString::number(tmp,'g',5));

  tmp = adData.us[24];
  tmp =(tmp/2457)*100.0;
  ui->label_kx->setText(QString::number(tmp,'g',5));

  tmp = adData.us[17];
  tmp =(tmp/4095)*250.0;
  ui->label_kw->setText(QString::number(tmp,'g',5));

  tmp = adData.us[25];
  tmp =(tmp/4095)*100.0;
  ui->label_dmac->setText(QString::number(tmp,'g',5));

}

void MainMenu::on_toolButton_taida1_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 1;
  if(checked)
    {
      mmsg.value = ui->lineEdit_taida1->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_taida2_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 2;
  if(checked)
    {
      mmsg.value = ui->lineEdit_taida2->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_taida3_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 3;
  if(checked)
    {
      mmsg.value = ui->lineEdit_taida3->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_taida4_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 4;
  if(checked)
    {
      mmsg.value = ui->lineEdit_taida4->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_taida5_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 5;
  if(checked)
    {
      mmsg.value = ui->lineEdit_taida5->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_freq1_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 11;
  if(checked)
    {
      mmsg.value = ui->lineEdit_freq1->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_freq2_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 12;
  if(checked)
    {
      mmsg.value = ui->lineEdit_freq2->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_freq3_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 13;
  if(checked)
    {
      mmsg.value = ui->lineEdit_freq3->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_freq4_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 14;
  if(checked)
    {
      mmsg.value = ui->lineEdit_freq4->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_freq5_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 15;
  if(checked)
    {
      mmsg.value = ui->lineEdit_freq5->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_tem1_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 21;
  if(checked)
    {
      mmsg.value = ui->lineEdit_tem1->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_tem2_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 22;
  if(checked)
    {
      mmsg.value = ui->lineEdit_tem2->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_tem3_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 23;
  if(checked)
    {
      mmsg.value = ui->lineEdit_tem3->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_tem4_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 24;
  if(checked)
    {
      mmsg.value = ui->lineEdit_tem4->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_tem5_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 25;
  if(checked)
    {
      mmsg.value = ui->lineEdit_tem5->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_bj1_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 51;
  if(checked)
    {
      mmsg.value = ui->lineEdit_bj1->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_bj2_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 52;
  if(checked)
    {
      mmsg.value = ui->lineEdit_bj2->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_bj3_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 53;
  if(checked)
    {
      mmsg.value = ui->lineEdit_bj3->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_bj4_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 54;
  if(checked)
    {
      mmsg.value = ui->lineEdit_bj4->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}

void MainMenu::on_toolButton_bj5_toggled(bool checked)
{
  struct MdMesg mmsg;
  mmsg.slave = 55;
  if(checked)
    {
      mmsg.value = ui->lineEdit_bj5->text().toFloat();

      qDebug()<<"checked";
    }
  else
    {
      mmsg.value = 0;
      qDebug()<<"unchecked";
    }
  emit SendMesg(mmsg);
}


