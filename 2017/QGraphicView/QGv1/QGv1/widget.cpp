#include "widget.h"

//Widget::Widget(QWidget *parent)
//    : QWidget(parent)
//{
//}

//Widget::~Widget()
//{

//}
#include<QTimer>
GvItem::GvItem(QString str)
{
    text =str;

}

QRectF GvItem::boundingRect() const
{
    return QRectF(0, 0,30,30);
}

void GvItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::cyan);
    painter->drawRect(this->boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(this->boundingRect(),Qt::AlignCenter,text);
}

void GvItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event<<this->text;
}

GvGraphicview::GvGraphicview(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,500,10000);
    setScene(scene);
    GvItem* gvit;
    for(int i=0;i<100;i++)
    {
        gvit = new GvItem(QString::number(i));
        gvit->setPos(100,i*100);
        gvit->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
        scene->addItem(gvit);
    }
    scene->setBackgroundBrush(Qt::blue);


    //    scene->set
}

