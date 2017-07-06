#include "utitlebar.h"
TitleBar::TitleBar(QString nm,QWidget *parent)
    : QWidget(parent)
{
    name = nm;
    minPix = style()->standardPixmap(QStyle::SP_TitleBarUnshadeButton);
    closePix  = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    floatPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
}

QSize TitleBar::minimumSizeHint() const
{
    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);
    QSize result(200, 21);
    return result;
}



void TitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if(!dw->isFloating())
    {
        floatPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
        minPix = style()->standardPixmap(QStyle::SP_TitleBarUnshadeButton);

    }
    else
    {
        minPix = style()->standardPixmap(QStyle::SP_TitleBarShadeButton);

        if(dw->isMaximized())
        {
            floatPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

        }
        else
        {
            floatPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        }
    }



    painter.fillRect(rect.left(), rect.top(), rect.width(), rect.height(), QColor(206, 206, 206));

    //drawText
       painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
       painter.setBrush(Qt::NoBrush);
       painter.drawText(rect.left() + 10, rect.top(), rect.width(), rect.height(), Qt::AlignVCenter, name);

    painter.drawPixmap(rect.topRight() - QPoint(closePix.width() + 10, -6), closePix);



    painter.drawPixmap(rect.topRight() - QPoint(floatPix.width() + 10
                                                + closePix.width() + 10, -6), floatPix);

    painter.drawPixmap(rect.topRight() - QPoint(minPix.width() + 10 + closePix.width() + 10+floatPix.width() + 10, -6), minPix);


}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) {
        QPoint p = pos;
        pos.setX(rect.left() + rect.bottom() - p.y());
        pos.setY(rect.top() + p.x() - rect.left());

        QSize s = rect.size();
        s.transpose();
        rect.setSize(s);
    }

    const int buttonRight = 10;
    const int buttonWidth = 20;
    int right = rect.right() - pos.x();
    int button = (right - buttonRight)/buttonWidth;

    switch (button) {
    case 0:
        event->accept();
        dw->close();
        break;

    case 1: {
        event->accept();
        if(dw->isMaximized())
        {
            dw->showNormal();
        }
        else
        {
            dw->showMaximized();
        }
        break;
    }
    case 2:
        event->accept();
        dw->setFloating(!dw->isFloating());
        break;
    default:
        event->ignore();
        break;
    }
}

