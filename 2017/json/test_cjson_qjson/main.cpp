#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include<QtCore>
#include<test_run_time.h>
#include "cJSON.h"
void qjson_test1( int num)
{
    QJsonObject json;
    QJsonObject json1;
    QJsonArray jary;
    jary = {1.3,4.6,7.8,3.5,9.3,8.8};

    json1.insert("name",QJsonValue("XX_SB"));
    json1.insert("data",QJsonValue(jary));
    T_RUN_START
            for(int i=0;i<num;i++)
    {
        json.insert(QString("arg%1").arg(QString::number(i)) ,QJsonValue(json1));
    }
    T_RUN_END("Qjson loop insert time")
            QFile jsonFile;
    jsonFile.setFileName("t1.json");
    jsonFile.open(QFile::WriteOnly);
    QJsonDocument qdj;
    qdj.setObject(json);
    //测试序列化时间
    T_RUN_START
            QByteArray out_data =  qdj.toJson();
    T_RUN_END("Qjson to data:")
            jsonFile.write(out_data);

    jsonFile.close();
    jsonFile.setFileName("t1.json");
    jsonFile.open(QFile::ReadOnly);
    QByteArray in_data = jsonFile.readAll();

    //测试文件加载时间
    T_RUN_START
            qdj =  QJsonDocument().fromJson(in_data);
    T_RUN_END("Qjson form data:")




}

void cjson_test1(int num)
{
    double jary[] = {1.3,4.6,7.8,3.5,9.3,8.8};
    cJSON *cjson = cJSON_CreateObject();
    cJSON *cjson1 = cJSON_CreateObject();
    cJSON *data =cJSON_CreateDoubleArray(jary,sizeof(jary)/sizeof(double));
    cJSON_AddStringToObject(cjson1,"name","XX_SB");
    cJSON_AddItemToObject(cjson1,"data",data);

    QByteArray qbt;
    T_RUN_START
            for(int i=0;i<num;i++)
    {
        QString("arg%1").arg(QString::number(i)).toLatin1().data();
        cJSON *cjson2 = cJSON_Duplicate(cjson1,1);
        cJSON_AddItemToObject(cjson,QString("arg%1").arg(QString::number(i)).toLatin1().data(),cjson2);
    }
    T_RUN_END("Cjson loop insert time:")

            T_RUN_START
            char* buf = cJSON_Print(cjson);
    T_RUN_END("Cjson to data:")
            qbt.clear();
    qbt= buf;
    QFile jsonFile;
    jsonFile.setFileName("t2.json");
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(qbt);

    jsonFile.close();
    jsonFile.setFileName("t1.json");
    jsonFile.open(QFile::ReadOnly);
    qbt = jsonFile.readAll();
    T_RUN_START
            cJSON *injson = cJSON_Parse(qbt.data());
    T_RUN_END("Cjson from data:")
}

void cjson_test2()
{
    QFile jsonFile;
     QByteArray qbt;
    jsonFile.setFileName("t1.json");
    jsonFile.open(QFile::ReadOnly);
    qbt = jsonFile.readAll();
    T_RUN_START
            cJSON *injson = cJSON_Parse(qbt.data());
    T_RUN_END("Cjson from data:")
      jsonFile.close();

            T_RUN_START
            char* buf = cJSON_Print(injson);
    T_RUN_END("Cjson to data:")
            qbt.clear();
    qbt= buf;

    jsonFile.setFileName("t3.json");
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(qbt);
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qjson_test1(10000);
//    cjson_test2();
    cjson_test1(10000);
    printf("out\n");
    return a.exec();
}
