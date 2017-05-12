#include <QApplication>
#include "top.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  top w;
  w.show();
  
  return a.exec();
}
