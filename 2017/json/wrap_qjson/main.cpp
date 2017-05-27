#include <QCoreApplication>
#include <QtCore>
#include <bmmesg.h>
#include <Windows.h>

DWORD WINAPI ThreadMsg1(LPVOID lpParameter)
{
    Bmmsg bm;
    while (1) {
        bm = BMQue.out();
        if(!bm.isNULL())
          qDebug()<<"ThreadMsg1"<<bm<<bm.json;
    }

    return 0;
}
DWORD WINAPI ThreadMsg2(LPVOID lpParameter)
{
    Bmmsg bm;
    while (1) {
        bm = BMQue.out();
        if(!bm.isNULL())
          qDebug()<<"ThreadMsg2"<<bm<<bm.json;
    }

    return 0;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HANDLE HOne,HTwo;
    HOne=CreateThread(NULL,0,ThreadMsg1,NULL,0,NULL);
    HTwo=CreateThread(NULL,0,ThreadMsg2,NULL,0,NULL);

    int i;
    while(1)
    {
        Bmmsg bm(50,i);
        bm.add("hello",BMPARAM(9.9));
        QJsonArray jf{1,2,3,4,"sssssssssss"};
        bm.add("gfd",BMPARAM(jf));

        BMQue.insert(bm);
        i++;
        Sleep(1000);
    }

//    QJsonObject qj1,qj2;
//    qj2.insert("name1",QJsonValue(9));
//    qj1 =qj2;
//    qj2.insert("name2",QJsonValue(8));
//    qDebug()<<qj1<<qj2;

    return a.exec();
}
