#ifndef HEAD_H
#define HEAD_H

#include <QWidget>
#include<QTimer>
#include<QDateTime>
class Head : public QWidget
{
  Q_OBJECT
public:
  explicit Head(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
private:
    QString Atext;
    QString Btext;
    QString Ctext;
    QTimer *tim;
    QDateTime current_date_time;
signals:
  
public slots:
  void get_time();
};

#endif // HEAD_H
