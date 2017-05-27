#ifndef MAIL_H
#define MAIL_H
#include<QtCore>

//只填写填消息
class Mail
{
public:
    Mail();
    Mail(const QJsonObject &other);
    Mail& operator=(const Mail &other);
    ~Mail();
    void insertMsg(const QString &name,const QJsonValue &value);
    QJsonValue getMsg(const QString &name);
    void setMsg(const QJsonObject &other);
    bool isNULL();
private:
    QJsonObject msg;
};


//class MailBox
//{
//public:
//    MailBox();
//    int count();
//    void setFilter(QStringList);
//    bool addFilter(QString);
//    postMail(Mail mail=Mail(),QString to="all",QString from=addr);
//    Mail getMail(QString from="all");
//    Mail getMail(QString from="all",QString checkname,QJsonValue value);

//    void insert(Mail mail);
//private:
//    PoxtOffice* pxtf;
//    QString addr;
//    QStringList filter;
//    QMutex mtx;
//    QQueue<Mail> que;

//};

//class PoxtOffice
//{
//public:
//    //    PoxtOffice();
//    QMap<QString,MailBox*> allQue;
//    MailBox applyMailbox(QString addr);

//};




#endif // MAIL_H
