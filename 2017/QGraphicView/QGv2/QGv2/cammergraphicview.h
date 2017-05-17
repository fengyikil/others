#ifndef CAMMERGRAPHICVIEW_H
#define CAMMERGRAPHICVIEW_H
#include<QGraphicsView>
class QWdiget;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsItem;
class QGraphicsPixmapItem;
//#include<QtWidgets>
class CammerGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit  CammerGraphicView(QWidget *parent = 0);
    QGraphicsPixmapItem* ghit;
private:
    QGraphicsScene* sence;
};
//class CammerGraphicView : public QGraphicsView
//{
//    Q_OBJECT
//public:
//    explicit CammerGraphicView(QWidget *parent = 0);

//protected:

//signals:

//public slots:

//};
#endif // CAMMERGRAPHICVIEW_H
