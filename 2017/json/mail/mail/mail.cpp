#include "mail.h"

Mail::Mail()
{
}

Mail::addMsg(QString name, QJsonValue value)
{
    msg.insert(name,value);
}

Mail::getMsg(QString name, QJsonValue value)
{
    return msg.value(name);
}

Mail::setMsg(QJsonObject mg)
{
    msg = mg;
}

MailBox PoxtOffice::applyMailbox(QString addr)
{
    MailBox mb;
    if(allQue.contains(addr))
        mb
}
