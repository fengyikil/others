#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include <QtNetwork>
#include <QFile>
class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(qintptr socketDescriptor, QObject *parent = 0);
public slots:
    void handle_Data();
private:
    int rec_state;
    QFile rec_file;
    int rec_size;
    qintptr socketID;
};

#endif // MYTCPSOCKET_H
