#include "picview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>

picView::picView(QWidget *parent) : QWidget(parent)
{

}
void picView::init()
{
    this->setFocusPolicy(Qt::StrongFocus);

#ifdef PIC_RED_RECT
    this->setMouseTracking(true);
    recState == RECT_NORMAL;
    leftBt = false;
    m_curRect = QRect(QPoint(100,100),QPoint(300,300));
    recalculate_corner_rect();
    cal_real_rec();
#endif

}




void picView::paintEvent(QPaintEvent *event)
{
    QImage img;
    m_painter.begin(this);
    QPen pen(Qt::green, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    m_painter.setPen(pen);
    if(!pimage.isNull())
    {
        img = pimage.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        m_painter.drawImage(0,0,img);
    }
    m_painter.drawRect(0,0,this->width(),this->height());
#ifdef PIC_RED_RECT
    pen.setColor(Qt::red);
    m_painter.setPen(pen);
    m_painter.drawRect(m_curRect);
#endif
    m_painter.end();  //重绘结束;
}
#ifdef PIC_RED_RECT
void picView::cal_real_rec()
{
    double x;
    double y;
    double w;
    double h;
    double wbl,hbl;
    if(!pimage.isNull())
    {
        wbl = pimage.width()*1.0/this->width();
        hbl = pimage.height()*1.0/this->height();
    }
    else
    {
        wbl = 1024*1.0/this->width();
        hbl =768*1.0/this->height();
    }
    x = m_curRect.x() * wbl;
    y = m_curRect.y() * hbl;
    w = m_curRect.width() * wbl;
    h = m_curRect.height() * hbl;
    emit s_change_rec(x,y,w,h);
}
void picView::mousePressEvent(QMouseEvent *event)
{
    leftBt = true;
    m_stretchRectState = getStrethRectState(event->pos());
    if (event->button() == Qt::LeftButton)
    {
        if (m_stretchRectState != NotSelect&&m_stretchRectState!=MainRect)
        {
            recState = RECT_STRETCH;
        }
        // 是否在选中的矩形中;
        else if (m_stretchRectState==MainRect)
        {
            setStretchCursorStyle(m_stretchRectState);
            mov_pos = event->pos();
            recState = RECT_MOVE;
        }
    }
    return QWidget::mousePressEvent(event);
}

void picView::mouseMoveEvent(QMouseEvent *event)
{
    StretchRectState m_stt = getStrethRectState(event->pos());
    QPoint now = event->pos();
    setStretchCursorStyle(m_stt);
    if(recState!=RECT_NORMAL)
    {
        m_curRect = recalculate_rect(now);
        cal_real_rec();
        update();
    }

    return QWidget::mouseMoveEvent(event);
}

void picView::mouseReleaseEvent(QMouseEvent *event)
{

    leftBt=false;
    recState = RECT_NORMAL;
    update();
    cal_real_rec();
    return QWidget::mouseReleaseEvent(event);
}

void picView::wheelEvent(QWheelEvent *event)
{
    double cx,cy;
    cx = m_curRect.x() + m_curRect.width()/2;
    cy = m_curRect.y() + m_curRect.height()/2;
    int size = event->delta();
    if(QApplication::keyboardModifiers () == Qt::ControlModifier)
    {
        if(size<0)
        {
            if(m_curRect.width()>5)
                m_curRect.setWidth(m_curRect.width()-1);
        }
        else
        {
            if(m_curRect.width()<this->width()-5)
                m_curRect.setWidth(m_curRect.width()+1);
        }
    }
    else
    {
        if(size<0)
        {
            if(m_curRect.height()>5)
                m_curRect.setHeight(m_curRect.height()-1);
        }
        else
        {
            if(m_curRect.height()<this->height()-5)
                m_curRect.setHeight(m_curRect.height()+1);
        }
    }
    m_curRect.setX(cx-m_curRect.width()/2);
    m_curRect.setY(cy-m_curRect.height()/2);

    //防止跑出边界
    if(m_curRect.height()<20)
        m_curRect.setHeight(20);
    if(m_curRect.height()>this->height()-10)
        m_curRect.setHeight(this->height()-10);
    if(m_curRect.left()<5)
        m_curRect.adjust(5-m_curRect.left(),0,5-m_curRect.left(),0);
    if(m_curRect.right()>this->width()-5)
        m_curRect.adjust(this->width()-5-m_curRect.right(),0,this->width()-5-m_curRect.right(),0);
    if(m_curRect.top()<5)
        m_curRect.adjust(0,5-m_curRect.top(),0,5-m_curRect.top());
    if(m_curRect.bottom()>this->height()-5)
        m_curRect.adjust(0,this->height()-5-m_curRect.bottom(),0,this->height()-5-m_curRect.bottom());

    recalculate_corner_rect();
    cal_real_rec();
    update();
}

void picView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if(m_curRect.y()-1>=5)
            m_curRect.adjust(0,-1,0,-1);
        break;
    case Qt::Key_Down:
        if(m_curRect.bottomLeft().y()-1<=this->height()-5)
            m_curRect.adjust(0,1,0,1);
        break;
    case Qt::Key_Left:
        if(m_curRect.x()-1>=5)
            m_curRect.adjust(-1,0,-1,0);
        break;
    case Qt::Key_Right:
        if(m_curRect.bottomRight().x()-1<=this->width()-5)
            m_curRect.adjust(1,0,1,0);
        break;
    default:
        break;
    }
    cal_real_rec();
    update();
}



//计算主矩形框区域
QRect picView::recalculate_rect(QPoint mpos)
{

    QPoint pos =mpos;

    QRect tmp_rect=m_curRect;
    QPoint beginPoint;
    QPoint endPoint;
    if(recState == RECT_NORMAL)
        tmp_rect = m_curRect;
    else if(recState == RECT_MOVE )
    {
        QPoint left = m_curRect.topLeft() + pos -mov_pos;
        tmp_rect = QRect(left,m_curRect.size());
        mov_pos =pos;

    }
    else if(recState == RECT_STRETCH )
    {

        switch(m_stretchRectState)
        {
        case NotSelect:
            tmp_rect = m_curRect;
            break;
        case TopLeftRect:
        {
            beginPoint =pos ;
            endPoint = m_curRect.bottomRight();
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case TopRightRect:
        {
            beginPoint = QPoint(m_curRect.topLeft().x(), pos.y());
            endPoint = QPoint(pos.x(), m_curRect.bottomRight().y());
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case BottomLeftRect:
        {
            beginPoint = QPoint(pos.x(), m_curRect.topLeft().y());
            endPoint = QPoint(m_curRect.bottomRight().x(), pos.y());
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case BottomRightRect:
        {
            beginPoint = m_curRect.topLeft();
            endPoint = pos;
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case LeftCenterRect:
        {
            beginPoint = QPoint(pos.x(),m_curRect.topLeft().y());
            endPoint = m_curRect.bottomRight();
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case TopCenterRect:
        {
            beginPoint = QPoint(m_curRect.x(),pos.y());
            endPoint = m_curRect.bottomRight();
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case RightCenterRect:
        {
            beginPoint =m_curRect.topLeft();
            endPoint = QPoint(pos.x(),m_curRect.bottomRight().y());
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        case BottomCenterRect:
        {
            beginPoint =m_curRect.topLeft();
            endPoint = QPoint(m_curRect.bottomRight().x(),pos.y());
            tmp_rect =  m_getRect(beginPoint,endPoint);
        }
            break;
        default:
        {
            tmp_rect = m_curRect;
        }
            break;
        }

    }
    if(tmp_rect!=m_curRect)
    {
        recalculate_corner_rect();

    }

    //防止矩形框跑出边界
    if(tmp_rect.width()<20)
        tmp_rect.setWidth(20);
    if(tmp_rect.width()>this->width()-10)
        tmp_rect.setWidth(this->width()-10);

    if(tmp_rect.height()<20)
        tmp_rect.setHeight(20);
    if(tmp_rect.height()>this->height()-10)
        tmp_rect.setHeight(this->height()-10);
    if(tmp_rect.left()<5)
        tmp_rect.adjust(5-tmp_rect.left(),0,5-tmp_rect.left(),0);
    if(tmp_rect.right()>this->width()-5)
        tmp_rect.adjust(this->width()-5-tmp_rect.right(),0,this->width()-5-tmp_rect.right(),0);
    if(tmp_rect.top()<5)
        tmp_rect.adjust(0,5-tmp_rect.top(),0,5-tmp_rect.top());
    if(tmp_rect.bottom()>this->height()-5)
        tmp_rect.adjust(0,this->height()-5-tmp_rect.bottom(),0,this->height()-5-tmp_rect.bottom());
    return tmp_rect;
}
//计算边角区域
void picView::recalculate_corner_rect()
{
    int t_width = m_curRect.width();
    int t_height = m_curRect.height();
    // 四个角坐标;
    QPoint topLeft = m_curRect.topLeft();
    QPoint topRight = m_curRect.topRight();
    QPoint bottomLeft = m_curRect.bottomLeft();
    QPoint bottomRight = m_curRect.bottomRight();
    // 四条边中间点坐标;
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(topLeft.x()-STRETCH_RECT_WIDTH/2,topLeft.y()+STRETCH_RECT_HEIGHT / 2,STRETCH_RECT_WIDTH,t_height-STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topLeft.x()+STRETCH_RECT_WIDTH/2,topLeft.y()-STRETCH_RECT_HEIGHT/2,t_width-STRETCH_RECT_WIDTH,STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(topRight.x()- STRETCH_RECT_WIDTH/2,topRight.y()+STRETCH_RECT_HEIGHT/2,STRETCH_RECT_WIDTH,t_height-STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomLeft.x()+STRETCH_RECT_WIDTH/2,bottomLeft.y()-STRETCH_RECT_HEIGHT/2,t_width-STRETCH_RECT_WIDTH,STRETCH_RECT_HEIGHT);

}

StretchRectState picView::getStrethRectState(QPoint &point)
{
    StretchRectState stretchRectState = NotSelect;
    QRect main_rec = QRect(m_curRect.topLeft().x()+STRETCH_RECT_WIDTH/2,
                           m_curRect.topLeft().y()+STRETCH_RECT_HEIGHT/2,
                           m_curRect.width() -STRETCH_RECT_WIDTH,
                           m_curRect.height() -STRETCH_RECT_HEIGHT);
    if(main_rec.contains(point))
    {
        stretchRectState = MainRect;

    }
    else if (m_topLeftRect.contains(point))
    {
        stretchRectState = TopLeftRect;
    }
    else if (m_topCenterRect.contains(point))
    {
        stretchRectState = TopCenterRect;
    }
    else if (m_topRightRect.contains(point))
    {
        stretchRectState = TopRightRect;
    }
    else if (m_rightCenterRect.contains(point))
    {
        stretchRectState = RightCenterRect;
    }
    else if (m_bottomRightRect.contains(point))
    {
        stretchRectState = BottomRightRect;
    }
    else if (m_bottomCenterRect.contains(point))
    {
        stretchRectState = BottomCenterRect;
    }
    else if (m_bottomLeftRect.contains(point))
    {
        stretchRectState = BottomLeftRect;
    }
    else if (m_leftCenterRect.contains(point))
    {
        stretchRectState = LeftCenterRect;
    }
    return stretchRectState;
}

void picView::setStretchCursorStyle(StretchRectState stretchRectState)
{
    switch (stretchRectState)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case MainRect:
        if(leftBt)
            setCursor(Qt::SizeAllCursor);
        else
            setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

QRect picView::m_getRect(const QPoint &begin, const QPoint &end)
{
    QPoint p1,p2;
    QRect tmp_rect;
    if(begin.x()<end.x()&&begin.y()<end.y())
        tmp_rect = QRect(begin,end);
    else if(begin.x()<end.x()&&begin.y()>=end.y())
    {
        p1.setX(begin.x());
        p1.setY(end.y());
        p2.setX(end.x());
        p2.setY(begin.y());
        tmp_rect = QRect(p1,p2);
    }
    else if(begin.x()>=end.x()&&begin.y()<end.y())
    {
        p1.setX(end.x());
        p1.setY(begin.y());
        p2.setX(begin.x());
        p2.setY(end.y());
        tmp_rect = QRect(p1,p2);
    }
    else if(begin.x()>=end.x()&&begin.y()>=end.y())
    {
        tmp_rect = QRect(end,begin);
    }
    return tmp_rect;
}


void picView::r_change_rec(double x, double y, double w, double h)
{

    double wbl,hbl;
    if(!pimage.isNull())
    {
        wbl = pimage.width()*1.0/this->width();
        hbl = pimage.height()*1.0/this->height();
    }
    else
    {
        wbl = 1024*1.0/this->width();
        hbl = 768*1.0/this->height();
    }
    m_curRect = QRect(x/wbl,y/hbl,w/wbl,h/hbl);
    recalculate_corner_rect();
    update();
}
#endif





