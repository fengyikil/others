#include "mail.h"

Mail::Mail()
{
}

Mail::Mail(const QJsonObject &other)
{
    msg = other;
}

Mail &Mail::operator=(const Mail &other)
{
    msg = other.msg;
    return *this;
}

Mail::~Mail()
{

}

void Mail::insertMsg(const QString &name, const QJsonValue &value)
{
    msg.insert(name,value);
}

 QJsonValue Mail::getMsg(const QString &name)
{
    return msg.value(name);
}

void Mail::setMsg(const QJsonObject &other)
{
    msg = other;
}

bool Mail::isNULL()
{
    if(msg.isEmpty())
        return true;
    else
        return false;
}

//MailBox PoxtOffice::applyMailbox(QString addr)
//{
//    MailBox mb;
//    if(allQue.contains(addr))
//        mb
//}
