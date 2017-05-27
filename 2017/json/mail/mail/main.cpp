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

    int al=13131313;
    int& b =al;
    int *p= &b ;
    int *q =&al;
    *p=pp;



        return a.exec();
}
