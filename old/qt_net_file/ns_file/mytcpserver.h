#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include "mytcpsocket.h"
#include <QTcpServer>
#include <QHash>
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0,int numConnections = 2);
protected :
    void incomingConnection(qintptr socketDescriptor);
private:
    QHash<int,MyTcpSocket *> * tcpClient;//管理连接的map
};

#endif // MYTCPSERVER_H
