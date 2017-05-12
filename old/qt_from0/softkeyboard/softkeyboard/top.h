#ifndef TOP_H
#define TOP_H

#include <QWidget>
#include <keyset.h>
#include <softkey.h>
class Top : public QWidget
{
  Q_OBJECT
public:
  explicit Top(QWidget *parent = 0);
  ~Top();
  KeySet* keyTest;
  KeySet* keyTest1;
  KeySet* keyTest2;
  SoftKey* g_softKey;
//  SoftKey* softKey;
signals:
  
public slots:
  
};

#endif // TOP_H
