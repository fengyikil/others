#include "exposure.h"
#include <QApplication>
#include<QDebug>
#include"BmCameraInterface.h"
#include <QThread>
#include<QDebug>
#include<QImage>
QImage pimage;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Exposure w;
    qDebug()<<"ImageGrabedCallBack1"<<QThread::currentThreadId();
    w.show();
    return a.exec();
}
