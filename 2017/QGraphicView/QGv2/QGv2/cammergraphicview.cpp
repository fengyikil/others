#include "cammergraphicview.h"
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QTime>
#include<QDebug>
CammerGraphicView::CammerGraphicView(QWidget *parent) :
    QGraphicsView(parent)
{
    sence = new QGraphicsScene;
    //    sence->addText("hello\n");
    //    sence->items()
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QPixmap pxm;
    for(int i =0 ;i<10;i++)
    {
        QString num = QString::number(1+qrand()%(8-1));
        qDebug()<<num;
        pxm.load(QString("F:/worksapce/test/QGraphicView/QGv2/QGv2/image/%1.jpg").arg(num));
        pxm = pxm.scaled(50,50);
        ghit = sence->addPixmap(pxm);
        ghit->setPos(50,i*100);
        sence->addWidget

    }
    sence->setSceneRect(this->rect());
    setScene(sence);
}



