#include <QCoreApplication>
#include "mail.h"
int pp=9;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //    Mail m1;
    //    m1.insertMsg("opo",QJsonValue("hh"));
    //    Mail m2(m1);
    //    Mail m3 = m1;

    //    m1.insertMsg("opo",QJsonValue(9));
    //    int h =90;
    //    qDebug("%d\n",h);
    //    qDebug()<<m1.isNULL()
    //           <<m2.isNULL()
    //           <<m1.getMsg("opo")
    //           <<m2.getMsg("opo")
    //           <<m3.getMsg("opo");

    MailBox* mbx1 = postOffice.applyMailbox("bx1");
    MailBox* mbx2 = postOffice.applyMailbox("bx2");
    MailBox* mbx3 = postOffice.applyMailbox("bx3");

    Mail mail;
    Mail mail2;
    mail.insertMsg("name",QJsonValue("jjj"));
    mail.insertMsg("country",QJsonValue("China"));
    mbx2->postMail(mail,"bx1");
    mbx2->postMail(mail,"bx1");

//    mbx3->postMail(mail,"bx1");
    qDebug()<<mbx1->getAddr()<<mbx2->getAddr()<<mbx3->getAddr();
    qDebug()<<postOffice.count()<<mbx1->count()<<mbx2->count()<<mbx3->count();
    Mail mail1 = mbx1->getMail();
    qDebug()<<mail1.msg;
    qDebug()<< mail1.getMsg("from");
//    Mail mail3 = mbx1->getMail();
//    qDebug()<<mail3.getMsg("name")<<mail3.getMsg("from")<<mail3.getMsg("fd").isUndefined();

    return a.exec();
}
