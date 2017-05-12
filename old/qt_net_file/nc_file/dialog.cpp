#include "dialog.h"
#include "ui_dialog.h"
#include "QFileDialog"
#include<QDebug>
#include<QMessageBox>
#include<stdio.h>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText("192.168.10.1");
    client = new QTcpSocket(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("All (*);;Exe(*.exe *.bin);;Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"));
    if(!dir.isEmpty())
    {
        ui->lineEdit_2->setText(dir);
    }
}

void Dialog::on_pushButton_conect_clicked()
{
    QString ip_addr = ui->lineEdit->text();
    client->connectToHost(QHostAddress(ip_addr),6666);

    if(client->waitForConnected(3000))
    {
        QMessageBox::about(NULL, "提示", "连接成功");
    }
    else
    {
        QMessageBox::about(NULL, "提示", "连接失败");
    }
}

void Dialog::on_pushButton_disconect_clicked()
{
    client->close();
}
struct file_head
{
    char name[30];
    int size;
};
void Dialog::on_pushButton_send_clicked()
{
    QByteArray data;

    dir_file.setFileName(ui->lineEdit_2->text());
    QFileInfo fi;
    dir_file.open(QIODevice::ReadWrite);
    fi = QFileInfo(dir_file);
    int file_name_size = fi.fileName().toUtf8().size();
    int file_size=fi.size();
    client->write((char*)&file_name_size,4);
    client->write(fi.fileName().toUtf8());
    client->write((char*)&file_size,4);
    client->write(dir_file.readAll());
    dir_file.close();

    //   const char *p =  fi.fileName().toUtf8().toStdString().data();
    //    memset(fh.name,0,30);
    //    memcpy(fh.name,p,fi.fileName().size()+1);

    //    fh.size=fi.size();
    //    qDebug()<<  fi.fileName();
    //    qDebug()<<fi.fileName().size();
    //    qDebug()<<  fi.size();

    //    client->write((char*)&fh,sizeof(fh));
    //    client->write(dir_file.readAll());
    //    dir_file.close();


}
