#include "mainwindow.h"
#include <QApplication>
#include <usplit.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Split sp(10);
//    sp.show();

    return a.exec();
}
