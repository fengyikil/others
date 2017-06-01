#include <QCoreApplication>
#include <Windows.h>
#include "mail.h"

//测试mail的基本操作
void test1()
{
    Mail m1;
    //插入
    m1.insertMsg("num",QJsonValue(888));
    m1.insertMsg("str",QJsonValue("jjj"));
    QJsonObject obj;
    obj.insert("obj_num",QJsonValue(999));
    obj.insert("obj_str",QJsonValue("space"));
    m1.insertMsg("obj",QJsonValue(obj));
    QJsonArray arry{1,2,3,4,5,"ssss"};
    m1.insertMsg("arry",QJsonValue(arry));
    qDebug()<<"m1.msg is"<<m1.msg<<"\n";

    //取出
    QJsonValue value;
    value= m1.getMsg("num");
    qDebug()<<"num is "<<value;
    value = m1.getMsg("str");
    qDebug()<<"str is "<<value;
    value = m1.getMsg("obj");
    qDebug()<<"obj is "<<value;
    value = m1.getMsg("arry");
    qDebug()<<"arry is "<<value<<"\n";

    //赋值
    Mail m2;
    qDebug()<<"m2 empty"<<m2.isEmpty();
    m2 = m1;
    qDebug()<<"m2 empty"<<m2.isEmpty();

    qDebug()<<"m2.msg is"<<m1.msg;
    bool res =(m2==m1);
    qDebug()<<"m2==m1 is"<<res<<"\n";

}
//测试MailBox的创建，第一种
void test2()
{

    PoxtOffice* pof =new PoxtOffice();
    //第一种创建方式
    qDebug()<<"pof count is"<<pof->count();
    MailBox* mb1 = pof->createMailBox("mb1");
    MailBox* mb2 = pof->createMailBox("mb2");
    MailBox* mb3 = pof->createMailBox("mb3");
    qDebug()<<"pof count is"<<pof->count();
    qDebug()<<"mb1 addr is"<<mb1->getAddr();
    qDebug()<<"mb2 addr is"<<mb2->getAddr();
    qDebug()<<"mb3 addr is"<<mb3->getAddr();



    //删除
    delete(mb1);
    delete(mb2);
    delete(mb3);

    qDebug()<<"pof count is"<<pof->count()<<"\n\n";



}
//测试MailBox的创建，第二种
void test3()
{
    PoxtOffice* pof =new PoxtOffice();
    //第二种创建方式
    MailBox* mb1 = new MailBox("mb1");
    MailBox* mb2 = new MailBox("mb2");
    MailBox* mb3 = new MailBox("mb3");
    qDebug()<<"pof count is"<<pof->count();

    mb1->registerPoxtOffice(pof);
    mb2->registerPoxtOffice(pof);
    mb3->registerPoxtOffice(pof);

    qDebug()<<"pof count is"<<pof->count();
    //    qDebug()<<"Box"<<mb1<<mb2<<mb3;

    qDebug()<<"mb1 addr is"<<mb1->getAddr();
    qDebug()<<"mb2 addr is"<<mb2->getAddr();
    qDebug()<<"mb3 addr is"<<mb3->getAddr();

    //删除
    delete(mb1);
    delete(mb2);
    delete(mb3);

    qDebug()<<"pof count is"<<pof->count()<<"\n\n";
}
//测试单线程 收发邮件
void test4()
{
    PoxtOffice* pof =new PoxtOffice();


    MailBox* mb1 = pof->createMailBox("mb1");
    MailBox* mb2 = pof->createMailBox("mb2");
    MailBox* mb3 = pof->createMailBox("mb3");
    MailBox* mb4 = pof->createMailBox("mb4");

    //创建一份邮件
    Mail tm;
    tm.insertMsg("old",QJsonValue(88));
    /***********************************/
    //mb1 发送tm给所有人
    mb1->postMail(tm);
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"mb4 count:"<<mb4->count();
    //取信
   qDebug()<< mb2->getMail().msg;
   qDebug()<< mb3->getMail().msg;
   qDebug()<< mb4->getMail().msg;

    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"mb4 count:"<<mb4->count();
    qDebug()<<"\n**********\n";

    /***********************************/
    //mb1 发送tm给mb3
    mb1->postMail(tm,"mb3");
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"mb4 count:"<<mb4->count();
    //取信
   qDebug()<< mb2->getMail().msg;
   qDebug()<< mb3->getMail().msg;
   qDebug()<< mb4->getMail().msg;

    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"mb4 count:"<<mb4->count();

}
//测试单线程 收发邮件 god邮箱 devil邮箱
void test5()
{
    PoxtOffice* pof =new PoxtOffice();


    MailBox* mb1 = pof->createMailBox("mb1");
    MailBox* mb2 = pof->createMailBox("mb2");
    MailBox* mb3 = pof->createMailBox("mb3");
    MailBox* god = pof->getMailBox("god");
    MailBox* devil = pof->getMailBox("devil");

    //开启监听模式，god邮箱则可以收到所有邮件
    pof->setGodMonitor(true);

    //创建一份邮件
    Mail tm;
    tm.insertMsg("old",QJsonValue(88));
    /***********************************/
    //mb1 发送tm给所有人
    mb1->postMail(tm);
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"god count:"<<god->count()
        <<"devil count:"<<devil->count();

    qDebug()<<"mb2"<<mb2->getMail().msg;
    qDebug()<<"mb3"<< mb3->getMail().msg;
    qDebug()<<"god"<<god->getMail().msg;
    qDebug()<<"devil"<<devil->getMail().msg;


    qDebug()<<"\n**********\n";
    //mb1 发送tm给mb3
    mb1->postMail(tm,"mb3");
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"god count:"<<god->count()
        <<"devil count:"<<devil->count();


    qDebug()<<"mb2"<<mb2->getMail().msg;
    qDebug()<<"mb3"<< mb3->getMail().msg;
    qDebug()<<"god"<<god->getMail().msg;
    qDebug()<<"devil"<<devil->getMail().msg;

}
//测试单线程 收发邮件 添加过滤器
void test6()
{
    PoxtOffice* pof =new PoxtOffice();

    MailBox* mb1 = pof->createMailBox("mb1");
    MailBox* mb2 = pof->createMailBox("mb2");
    MailBox* mb3 = pof->createMailBox("mb3");
    MailBox* god = pof->getMailBox("god");
    MailBox* devil = pof->getMailBox("devil");

    //开启监听模式，god邮箱则可以收到所有邮件
    pof->setGodMonitor(true);
    //创建一份邮件
    Mail tm;
    tm.insertMsg("old",QJsonValue(88));
    /******************************/
    //mb3设置mb1的过滤器
    mb3->addFilter("mb1");
    //mb1 发送tm给所有人
    mb1->postMail(tm);
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"god count:"<<god->count()
        <<"devil count:"<<devil->count();

    qDebug()<<"mb2"<<mb2->getMail().msg;
    qDebug()<<"mb3"<< mb3->getMail().msg;
    qDebug()<<"god"<<god->getMail().msg;
    qDebug()<<"devil"<<devil->getMail().msg;


    qDebug()<<"\n**********\n";
    /******************************/
    //mb3设置mb1的过滤器
    mb3->subFilter("mb1");
    //mb1 发送tm给mb3
    mb1->postMail(tm,"mb3");
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"god count:"<<god->count()
        <<"devil count:"<<devil->count();

    qDebug()<<"mb2"<<mb2->getMail().msg;
    qDebug()<<"mb3"<< mb3->getMail().msg;
    qDebug()<<"god"<<god->getMail().msg;
    qDebug()<<"devil"<<devil->getMail().msg;

    qDebug()<<"\n**********\n";
    /******************************/

    //mb3设置mb1的过滤器
    mb3->subFilter("god");
    //god 发送tm给mb3
    god->postMail(tm,"mb3");//god强发
    qDebug()<<"mb1 count:"<<mb1->count()
           <<"mb2 count:"<<mb2->count()
          <<"mb3 count:"<<mb3->count()
         <<"god count:"<<god->count()
        <<"devil count:"<<devil->count();

    qDebug()<<"mb2"<<mb2->getMail().msg;
    qDebug()<<"mb3"<< mb3->getMail().msg;
    qDebug()<<"god"<<god->getMail().msg;
    qDebug()<<"devil"<<devil->getMail().msg;

}

//测试多线程 收发邮件 线程1：收两封，回一封； 线程2：隔两秒收一次，发一封。 线程3：凑够3封一起接收
PoxtOffice* gpof;

DWORD WINAPI ThreadMsg1(LPVOID lpParameter)
{
    static int count;
    MailBox* mb1 =gpof->createMailBox("mb1");
    //创建一份邮件
    Mail tm;
    tm.insertMsg("old",QJsonValue(88));

    //收到两封，回一封
    while (1) {
        if(mb1->count())
        {
           count++;
           Mail tm1 = mb1->getMail();
           qDebug()<<"ThreadMsg1"<<mb1->count()<<tm1.msg<<"\n";
           if(count%2)
               mb1->postMail(tm,tm1.getMsg("from").toString());
        }
//        Sleep(2000);
    }
    return 0;

}
DWORD WINAPI ThreadMsg2(LPVOID lpParameter)
{
    MailBox* mb2 =gpof->createMailBox("mb2");
    //创建一份邮件
    Mail tm;
    tm.insertMsg("old",QJsonValue(99));

    //每隔两秒发送给全部
    while (1) {
        if(mb2->count())
        {
           Mail tm1 = mb2->getMail();
           qDebug()<<"ThreadMsg2"<<mb2->count()<<tm1.msg;
        }
        mb2->postMail(tm);
        Sleep(2000);
    }
    return 0;

}
DWORD WINAPI ThreadMsg3(LPVOID lpParameter)
{
    MailBox* mb3 =gpof->createMailBox("mb3");

    //凑够3封一起接收
    while (1) {
        if(mb3->count()==3)
        {
//            mb3->disRepeat(); //去重
            while (mb3->count()) {
                Mail tm3 = mb3->getMail();
                qDebug()<<"ThreadMsg3"<<mb3->count()<<tm3.msg;
            }
            qDebug()<<"\n";
        }
//        Sleep(2000);
    }
    return 0;
}
void test7()
{
    gpof =new PoxtOffice();
    HANDLE H1,H2,H3;
    H1=CreateThread(NULL,0,ThreadMsg1,NULL,0,NULL);
    H2=CreateThread(NULL,0,ThreadMsg2,NULL,0,NULL);
    H3=CreateThread(NULL,0,ThreadMsg3,NULL,0,NULL);

}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
    test7();

    return a.exec();
}
