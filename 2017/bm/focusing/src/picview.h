#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>
#include <QImage>
#include <QRect>
#include <QPainter>
#define PIC_RED_RECT
extern QImage pimage;
#ifdef PIC_RED_RECT
// 选中矩形8个拖拽点小矩形的宽高;
#define STRETCH_RECT_WIDTH 10
#define STRETCH_RECT_HEIGHT 10
// 当前鼠标所在顶点状态;
enum StretchRectState{
    NotSelect = 0,
    MainRect,
    TopLeftRect,
    TopRightRect,
    BottomLeftRect,
    BottomRightRect,
    LeftCenterRect,
    TopCenterRect,
    RightCenterRect,
    BottomCenterRect
};
//矩形框状态
enum RectState{
    RECT_NORMAL = 0,
    RECT_MOVE,
    RECT_STRETCH
};
#endif
class picView : public QWidget
{
    Q_OBJECT
public:
    explicit picView(QWidget *parent = 0);
    void init();
protected:
    void paintEvent(QPaintEvent *event);
#ifdef PIC_RED_RECT
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent  *event);
signals:
    void s_change_rec(double x,double y,double w, double h);
public slots:
    //保留,可以用做多种不同比例伸缩图片的矩形框连动,比如用一个不伸缩的picview连动伸缩picview来确定矩形框选中位置转换后正确。
    void r_change_rec(double x,double y,double w, double h);
#endif

private:
    QPainter m_painter;
#ifdef PIC_RED_RECT
    bool leftBt;
    StretchRectState m_stretchRectState;

    QPoint m_end,mov_pos;
    RectState recState;
    QRect m_curRect;
    QRect m_topLeftRect, m_topRightRect, m_bottomLeftRect, m_bottomRightRect;
    QRect m_leftCenterRect, m_topCenterRect, m_rightCenterRect, m_bottomCenterRect;

    //计算矩形红框对应实际image的位置（所见图片是经过伸缩显示的）
    void cal_real_rec();
    //重新计算显示矩形框位置、大小
    QRect recalculate_rect(QPoint now);
    //重新计算显示矩形框伸缩区域位置、大小
    void recalculate_corner_rect();

    StretchRectState getStrethRectState(QPoint &point);
    void setStretchCursorStyle(StretchRectState stretchRectState);
    QRect m_getRect(const QPoint &beginPoint, const QPoint &endPoint);
#endif
};


#endif // PICVIEW_H
