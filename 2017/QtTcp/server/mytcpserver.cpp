#include "mytcpserver.h"
#include <QDebug>



MyTcpServer::MyTcpServer(QString addr, int port, QObject *parent):
    QThread(parent)
{
    moveToThread(this);
maddr = addr;
mport = port;
}

void MyTcpServer::run()
{

    server = new QTcpServer();
    server->setMaxPendingConnections(1);
    server->listen( QHostAddress(maddr), mport );
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
   exec();
}

//MyTcpServer::MyTcpServer(QObject *parent):
//    QObject(parent)
//{
//    server = new QTcpServer(this);
//    server->setMaxPendingConnections(1);
//    server->listen( QHostAddress("192.168.0.4"), 9090 );
//    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
//}

void MyTcpServer::newConnection()
{
    qDebug()<<"newCon com in";

        socket = server->nextPendingConnection();
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
//        server->pauseAccepting();

}

void MyTcpServer::readyRead()
{
    qDebug()<< socket->readAll();
    socket->write("Hello\n");
}
//MyServer::MyServer(QObject *parent) :
//    QObject(parent)
//{
//    server = new QTcpServer(this);

//    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

//    if(!server->listen(QHostAddress::Any,80))
//    {
//        qDebug() << "Server could not start!";
//    }
//    else
//    {
//        qDebug() << "Server started";
//    }
//}

//void MyServer::newConnection()
//{
//    QTcpSocket *socket = server->nextPendingConnection();

//    socket->write("hello client\r\n");
//    socket->flush();

//    socket->waitForBytesWritten(3000);

//    socket->close();
//}
