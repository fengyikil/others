#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) :
    QObject(parent)
{

}

void SocketTest::Test()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
//    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));

    qDebug() << "Connecting...";

    socket->connectToHost("192.168.0.4",9090);

    if(!socket->waitForConnected(5000))
    {
       qDebug() << "Error: " <<  socket->errorString();
    }

//    socket1 = new QTcpSocket(this);
//    connect(socket1,SIGNAL(connected()), this, SLOT(connected()));
//    connect(socket1,SIGNAL(disconnected()), this, SLOT(disconnected()));
//    connect(socket1,SIGNAL(readyRead()), this, SLOT(readyRead()));
//    connect(socket1,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));

//    qDebug() << "Connecting...";

//    socket1->connectToHost("192.168.0.4",9090);

//    if(!socket->waitForConnected(5000))
//    {
//       qDebug() << "Error: " <<  socket->errorString();
//    }
}

void SocketTest::connected()
{
    qDebug() << "Connected!";
    QObject * obj = sender();
    QTcpSocket *tsocket = qobject_cast<QTcpSocket *>(obj);
    tsocket->write("HEAD / HTTP/1.0\r\n\r\n\r\n");
}


void SocketTest::disconnected()
{
    qDebug() << "Disconnected!";
}


void SocketTest::bytesWritten (qint64 bytes)
{
    qDebug() << "we wrote: " << bytes;
}

#include<Windows.h>
void SocketTest::readyRead()
{
//    qDebug() << "Reading...";
    QObject * obj = sender();
    QTcpSocket *tsocket = qobject_cast<QTcpSocket *>(obj);

    qDebug() << tsocket->readAll();
    Sleep(1000);
    tsocket->write("client reponse\n");
}
