#ifndef MYDOCKTITLEBAR_H
#define MYDOCKTITLEBAR_H

#include <QSize>
#include <QDockWidget>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "qdebug.h"
#include <QStyle>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar(QString nm,QWidget *parent = 0);

    QSize sizeHint() const {
        return minimumSizeHint();
    }
    QSize minimumSizeHint() const;


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QString name;
    QPixmap minPix, closePix, floatPix;

};
#endif
