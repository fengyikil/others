#include "dialog.h"
#include <QApplication>
#include <pwd_thread.h>
#include<QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    PwdThread pt;
    QObject::connect(&w,SIGNAL(SendPwd(QString,QString)),&pt,SLOT(FilePwd(QString,QString)),Qt::QueuedConnection);
    QObject::connect(&pt,SIGNAL(SendQPd(int)),&w,SLOT(UpQpd(int)));
    pt.start();
    w.show();

    return a.exec();
}
