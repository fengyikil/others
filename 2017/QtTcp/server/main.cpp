#include <QCoreApplication>
#include <QApplication>

#include<QtNetwork>
#include <QDebug>
#include "mytcpserver.h"
#include<Windows.h>
//void hannoi(int n, QString A, QString B, QString C)
//{
//    static int num;
//    if (n == 1)
//    {
//        qDebug()<<num<<"move"<<A<<"to"<<C;
//        num++;
//    }
//    else
//    {
//        hannoi (n-1, A, C, B);

//        qDebug()<<num<<"move"<<A<<"to"<<C;
//        num++;
//        hannoi (n-1, B, A, C);
//    }
//}
//DWORD WINAPI ThreadOne(LPVOID lpParameter)
//{
//    int b = 1;


//     QCoreApplication app(b, NULL);

//    MyTcpServer *ms1 = new MyTcpServer("192.168.0.4",9090);

//    app.exec();


//    return 0;
//}
#include<QtWidgets>
#include "form.h"
int main(int argc, char *argv[])
{
//    HANDLE HOne;
//        HOne=CreateThread(NULL,0,ThreadOne,NULL,0,NULL);
//    hannoi(10,"A","B","C");
    QApplication a(argc, argv);
//        QWidget w;
//        w.show();
    //    qDebug()<< QNetworkInterface::allAddresses() ;

    //MyServer mServer;
        MyTcpServer *ms2 = new MyTcpServer("192.168.0.4",9090);
        ms2->start();
Form f;
f.show();

    //     qDebug()<<serv0.listen( QHostAddress("192.168.0.4"), 8080 );
    //     qDebug()<<serv1.listen( QHostAddress("192.168.0.5"), 8080 );


    //     serv0.close();
    //     serv1.close();


    return a.exec();
}
