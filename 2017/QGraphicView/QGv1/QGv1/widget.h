#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
//#include <QGraphicsItem>
//class Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = 0);
//    ~Widget();
//};

class GvItem:public QGraphicsItem
{
public:
    GvItem(QString str);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QString text;
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

};

class GvGraphicview:public QGraphicsView
{
    Q_OBJECT
public:
    GvGraphicview(QWidget *parent=0);
    QGraphicsScene *scene;

};

#endif // WIDGET_H
