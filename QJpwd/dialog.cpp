#include "dialog.h"
#include "ui_dialog.h"
#include<QtGui>
#include<QMessageBox>
#include<QDebug>
#include<QProgressDialog>
#include<QFileDialog>
#include <QFile>
extern QString src_dir;
extern QString pwd_dir;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    this->setWindowTitle("康盛解密工具@蒋俊杰");
    qpd = new QProgressDialog(this);
    qpd->setWindowTitle("已完成");
    qpd->setRange(0,100);
    qpd->setModal(true);
    qpd->setLabelText(tr("进行中..."));
    qpd->setValue(100);
    qpd->setCancelButtonText(tr("取消"));
    qpd->setAutoClose(false);
    qpd->setAutoReset(false);

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Browse1()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(Browse2()));

    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(Pwd()));

    qpd->hide();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Browse1()
{
    QString dir = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("All (*);;Exe(*.exe *.bin);;Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"));
    if(!dir.isEmpty())
    {
        ui->lineEdit->setText(dir);
        if(dir.endsWith(".k"))
            dir.chop(2);
        else
            dir.append(".jk");
        ui->lineEdit_2->setText(dir);
    }
}
void Dialog::Browse2()
{
    QString dir= QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    ui->lineEdit_2->setText(dir);
}

void Dialog::UpQpd(int value)
{
    if(value==888)
    {
//        qpd->close();
//        qpd->reset();
      QMessageBox::information(this,"提示","输入文件不是加密文件！");
      return;
    }
    qpd->setValue(value);
    if(value==100)
    {
        qpd->close();
        qpd->reset();
    }
}
void Dialog::Pwd()
{
    QFileInfo  rfile(ui->lineEdit->text());
    QFileInfo wfile(ui->lineEdit_2->text());

    if(!rfile.isFile())
    {
        QMessageBox::information(this,"提示","输入文件不存在");
        return;
    }
    if(wfile.isFile() && !wfile.isDir())
    {
        int result = QMessageBox::information(this,"提示","输出文件已存在，点击继续则覆盖！","继续","取消");

        qDebug()<<result;
        if (result)
        {
            return;
        }
    }
    else if(!wfile.isFile()&& wfile.isDir())
    {
        int result = QMessageBox::information(this,"提示","请补全输出文件名！","确定");
        return;
    }
    emit SendPwd(ui->lineEdit->text(),ui->lineEdit_2->text());
}


