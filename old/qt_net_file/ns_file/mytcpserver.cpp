#include "mytcpserver.h"
#include "QDebug"
MyTcpServer::MyTcpServer(QObject *parent, int numConnections)
{
  tcpClient  = new QHash<int,MyTcpSocket*>;
  setMaxPendingConnections(numConnections);
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"come in";
    if (tcpClient->size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
      {
          QTcpSocket tcp;
          tcp.setSocketDescriptor(socketDescriptor);
          tcp.disconnectFromHost();
          return;
      }
    else
    {
    MyTcpSocket* tcpTemp = new MyTcpSocket(socketDescriptor);
     tcpClient->insert(socketDescriptor,tcpTemp);//插入到连接信息中
    emit newConnection();
    }
       qDebug()<<tcpClient->size();
}
