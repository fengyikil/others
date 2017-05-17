#include "widget.h"
#include "ui_widget.h"
#include<QPixmap>
#include<QTime>
#include "cammergraphicview.h"
#include<QGraphicsPixmapItem>
#include<QGraphicsWidget>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QPixmap pxm;
    QString num = QString::number(1+qrand()%(8-1));

    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));

    pxm.load(QString("F:/worksapce/test/QGraphicView/QGv2/QGv2/image/%1.jpg").arg(num));
    pxm = pxm.scaled(50,50);
    CammerGraphicView* cgv  = ui->graphicsView;
    cgv->ghit->setPixmap(pxm);
//    cgv->hide();

}

void Widget::on_pushButton_2_clicked()
{
   ui->graphicsView->show();
}

void Widget::on_pushButton_3_clicked()
{
    ui->graphicsView->hide();

}
