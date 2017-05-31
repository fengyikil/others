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
    bool operator ==(const Mail &other);
    ~Mail();
    void insertMsg(const QString &name,const QJsonValue &value);
    QJsonValue getMsg(const QString &name);
    void setMsg(const QJsonObject &other);
    bool isNULL();
     QJsonObject msg;
private:
//    QJsonObject msg;
};

class PoxtOffice;
class MailBox
{
public:
    friend class PoxtOffice;
    MailBox();
    int count();
    QString& getAddr();
    void setFilter(QStringList &strlist);
    void addFilter(QString &str);
    void postMail(Mail mail,QString to=QString("all"));
    Mail getMail(QString from=QString("all"));
//    Mail& getMail(QString &from=QString("all"),QString &checkname,QJsonValue &value);
    void setPoxtOffice(PoxtOffice* pf){pxtf = pf;}
private:
    void insert(Mail mail);
    PoxtOffice* pxtf;
    QString addr;
    QStringList filter;
    QMutex mtx;
    QQueue<Mail> que;
};

class PoxtOffice
{
public:
    PoxtOffice(){office.clear();}
    int count(){return office.count();}
    QMap<QString,MailBox*> office;
    MailBox* applyMailbox(QString addr){
        MailBox* mb;
        if(office.contains(addr))
            mb = office.value(addr);
        else
        {
            mb = new MailBox();
            mb->addr = addr;
            mb->setPoxtOffice(this);
            office.insert(addr,mb);
        }
        return mb;
    }
};

extern PoxtOffice postOffice;




#endif // MAIL_H
