#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include<QtCore>
#include<test_run_time.h>

void json_test1()
{


            QJsonObject js{
        {"property1",1568},
        {"property2",2},
        //    {"dsf",{{"1",3},{"2",4}}},
        ////    {"property3",[1,2,3,4,5,6,7,8]}
    };

    QJsonObject js1;
    js1.insert("3",QJsonValue("str_json"));
    QJsonValue qv(js1);
    js.insert("property3",qv);
    js.insert("property4",QJsonValue(58));

    for(int i=0;i<100000;i++)
   {
       js.insert(QString("arg%1").arg(QString::number(i)) ,QJsonValue(i));
   }

    QJsonObject::iterator it;
    for(it = js.begin();it!=js.end();it++)
    {
//        qDebug()<<it.key();
//        qDebug()<<it.value();
        it.key();
    }
//    qDebug()<<js.length();
//    qDebug()<<js.count();
//    qDebug()<<js.size();
//    qDebug()<<js.take("property3").toObject().take("3");
     T_RUN_START
             QJsonDocument qdj(js);
       QFile jsonFile("t1.json");
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(qdj.toJson());
    T_RUN_END




}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    json_test1();
    QString ss = "fokkg";
    qDebug()<<"qjson test"<<ss;
    return a.exec();
}
