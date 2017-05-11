#include "pwd_thread.h"
#include <QDataStream>
#include <QFile>
#include <dialog.h>
#include<QDebug>
PwdThread::PwdThread(QObject *parent)
{
    this->moveToThread(this);
}

void PwdThread::run()
{
    exec();
}
#define BUFSZIE 1024
void Encrypt(char* src,char* dir,int len)
{
    int i;
    for(i=0;i<len;i++)
         dir[i] = src[i]^(i*3+8);

}
//加密文件 每次处理BUFSZIE字节数据。
void PwdThread::FilePwd(QString src,QString pwd)
{

    QObject * obj = sender();
    Dialog* dlg =qobject_cast<Dialog *>(obj);

    qint64 fileSize;
    qint64 lastSize;

    int magicNum = 0x23232323;
    char *rbuf =new char[BUFSZIE];
    char *wbuf =new char[BUFSZIE];

    QFile rfile(src);
    QDataStream rf(&rfile);

    QFile wfile(pwd);
    QDataStream wf(&wfile);

    rfile.open(QIODevice::ReadWrite);
    wfile.open(QIODevice::ReadWrite);
    lastSize = fileSize = rfile.size();
    wf<<magicNum;
    while(lastSize)
    {
        qDebug()<<"lastSize is "<<lastSize;
        int len;
        int nowRate;
        int lastRate;
        if(dlg->qpd->wasCanceled())
                {
                    wfile.remove();
                    goto end;
                }


        if(lastSize>=BUFSZIE)
        {
            len = BUFSZIE;
            rf.readRawData(rbuf,BUFSZIE);
            lastSize = lastSize - BUFSZIE;
        }
        else
        {
            len = lastSize;
            rf.readRawData(rbuf,lastSize);
            lastSize = 0;
        }
        Encrypt(rbuf,wbuf,BUFSZIE);
        wf.writeRawData(wbuf,len);

        nowRate = 100 - (lastSize*100)/fileSize;
        if(nowRate!=lastRate)
        {
        emit SendQPd(nowRate);
            lastRate = nowRate;
        }

    }
 end:
     qDebug()<<"end";
    emit SendQPd(100);
    rfile.close();
    wfile.close();
    delete(rbuf);
    delete(wbuf);
}


