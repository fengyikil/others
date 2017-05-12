#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
class view : public QWidget
{
  Q_OBJECT
public:
  explicit view(QWidget *parent = 0);
  
signals:
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
public slots:
    void draw_frame();
    void draw_shift();
private:

    QPixmap* p_shift;
    QPixmap* p_frame;
    qreal ro;
    int myTimerId;
//    view_shift *view_s;
};

#endif // VIEW_H
