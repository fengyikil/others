#include "ulog.h"
#include "ui_ulog.h"

ulog::ulog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ulog)
{
    ui->setupUi(this);
    ui->plainTextEdit_Alg1->setReadOnly(true);
    for(int i=0;i<1000;i++)
    ui->plainTextEdit_Alg1->appendPlainText("fdfffffff\nfddddd\n");

    ui->plainTextEdit_Alg1->clear();
    ui->plainTextEdit_ALg2->setReadOnly(true);
    ui->plainTextEdit_Alg3->setReadOnly(true);
    ui->plainTextEdit_debug->setReadOnly(true);
    ui->plainTextEdit_Err->setReadOnly(true);
    ui->plainTextEdit_Info->setReadOnly(true);
}

ulog::~ulog()
{
    delete ui;
}
