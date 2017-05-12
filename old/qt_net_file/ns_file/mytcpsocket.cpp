#include "mytcpsocket.h"
#include <QDebug>

MyTcpSocket::MyTcpSocket(qintptr socketDescriptor, QObject *parent):
    QTcpSocket(parent),socketID(socketDescriptor)
{
    rec_state = 0;
    rec_size = 0;
    this->setSocketDescriptor(socketDescriptor);
    connect(this,SIGNAL(readyRead()),this,SLOT(handle_Data()));
}

void MyTcpSocket::handle_Data()
{
    QByteArray file_name;
    QByteArray data;
    int file_name_size;
    int file_size;

    if(rec_state==0)
    {
        read((char *)&file_name_size,4);
        printf("%x\n",file_name_size);
        file_name=read(file_name_size);

        rec_file.setFileName(QString(file_name));
       qDebug()<<QString(file_name);
            read((char *)&file_size,4);
               qDebug()<<file_size;
            rec_size = file_size;
        rec_file.open(QIODevice::ReadWrite);
        data = this->readAll();
        rec_size =rec_size - data.size();
        rec_file.write(data);
        rec_state=1;
    }
    else
    {
        data = this->readAll();
        rec_size =rec_size - data.size();
        rec_file.write(data);
        if(rec_size==0)
        {
            rec_file.close();
            rec_state=0;
        }
    }
    QString ip =this->peerAddress().toString();
        qDebug()<<"ip is"<< ip<<"last size"<<rec_size;
}
