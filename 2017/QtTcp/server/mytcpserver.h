#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include<QtNetwork>
#include <QThread>
class MyTcpServer : public QThread
{
    Q_OBJECT
public:
    explicit MyTcpServer(QString addr,int port,QObject *parent = 0);
//   explicit MyTcpServer(QObject *parent = 0);
    void incomingConnection();
    void run();
signals:

public slots:
    void newConnection();
    void readyRead();
private:
    QString maddr;
    int mport;
    QTcpServer *server;
    QTcpSocket *socket;
};

//class MyServer : public QObject
//{
//    Q_OBJECT
//public:
//    explicit MyServer(QObject *parent = 0);

//signals:


//public slots:
//    void newConnection();

//private:
//    QTcpServer *server;
//};
#endif // MYTCPSERVER_H
