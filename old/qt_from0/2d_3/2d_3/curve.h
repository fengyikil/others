#ifndef CURVE_H
#define CURVE_H

#include <QWidget>

class curve : public QWidget
{
  Q_OBJECT
public:
  explicit curve(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

private:
  QPixmap p_buffer;
public slots:
  void draw();
};

#endif // CURVE_H
