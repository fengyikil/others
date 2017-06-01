#ifndef MAIL_H
#define MAIL_H
#include<QtCore>
class PoxtOffice;
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
    bool isEmpty();
    QJsonObject msg;
private:
    //    QJsonObject msg;
};


class MailBox
{
public:
    friend class PoxtOffice;
    MailBox(QString ad);
    ~MailBox();
    bool registerPoxtOffice(PoxtOffice* pf);
    int count();
    QString getAddr();
    void setFilter(QStringList &strlist);
    void addFilter(QString str);
    void subFilter(QString str);
    void postMail(Mail &mail,QString to=QString("all"));
    Mail getMail(QString from=QString("all"));
    //    Mail& getMail(QString &from=QString("all"),QString &checkname,QJsonValue &value);
    void setPoxtOffice(PoxtOffice* pf);
    void disRepeat();
private:
    void insert(Mail &mail);
    PoxtOffice* pxtf;
    QString addr;
    QStringList filter;
    QMutex mtx;
    QQueue<Mail> que;
};

class PoxtOffice
{
public:
    friend class MailBox;
    PoxtOffice();
    int count();//注册的邮箱数
    MailBox* createMailBox(QString addr);
    MailBox* getMailBox(QString addr);
    void setGodMonitor(bool gmt);
    bool getGodMonitor();
private:
    QMutex mtx;
    QMap<QString,MailBox*> office;
    bool godMonitor;//god监听模式打开可以收所有邮件
    bool RegisterMailBox(MailBox* mb);
    void disRegisterMailBox(QString addr);
};

//extern PoxtOffice postOffice;




#endif // MAIL_H
