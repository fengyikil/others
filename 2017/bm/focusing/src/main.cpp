#include "focusing.h"
#include <QApplication>
#include<QImage>
#include <QThread>
#include <QDebug>
QImage pimage;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Focusing w;
    qDebug()<<"main"<<QThread::currentThreadId();
    w.show();
    return a.exec();
}
