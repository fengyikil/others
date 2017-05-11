#ifndef SAMPLEVALUE_H
#define SAMPLEVALUE_H

#include <QWidget>

class SampleValue : public QWidget
{
  Q_OBJECT
public:
  explicit SampleValue(QWidget *parent = 0);
  float value1;
  float value2;
  float value3;
  float value4;
  float value5;
  float value6;
  float value7;
  float value8;
protected:
    void paintEvent(QPaintEvent *);
signals:
  
public slots:
  
};

#endif // SAMPLEVALUE_H
