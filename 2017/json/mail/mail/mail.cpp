#include "mail.h"
PoxtOffice postOffice;
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

bool Mail::operator ==(const Mail &other)
{
    if(msg==other.msg)
        return true;
    else
        return false;
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





MailBox::MailBox()
{
}

int MailBox::count()
{
    int count;
    mtx.lock();
    count = que.count();
    mtx.unlock();
    return count;
}

QString &MailBox::getAddr()
{
    return addr;
}

void MailBox::setFilter(QStringList &strlist)
{
    filter = strlist;
}

void MailBox::addFilter(QString &str)
{
    filter.append(str);
}

void MailBox::postMail(Mail mail,QString to)
{
    mail.insertMsg("from",QJsonValue(addr));
    if(to=="all")
    {
        foreach (QString key,pxtf->office.keys()) {
            if(pxtf->office[key]!=this)
            {
                if(!(pxtf->office[key]->filter.contains(addr)))
                {
                    pxtf->office[key]->insert(mail);
                }
            }
        }

//        QMapIterator<QString, MailBox*> i();
//        while(i.hasNext())
//        {
//            if(!(i.next.value()->filter.contains(addr)))
//                i.value()
//        }

    }
    else
    {
        if(pxtf->office.contains(to))
        {
            if(!(pxtf->office[to]->filter.contains(addr)))
               pxtf->office[to]->insert(mail);
        }
    }
}

Mail MailBox::getMail(QString from)
{
    Mail mail;
   if(from=="all")
   {
       mtx.lock();
       if(!que.isEmpty())
           mail = que.dequeue();
       mtx.unlock();

   }
   else
   {
       mtx.lock();
       foreach (Mail mail1, que) {
           if(!mail1.getMsg("from").isNull())
           {
             mail = mail1;
             que.removeOne(mail1);
             break;
           }
       }
       mtx.unlock();

   }
   return mail;
}

void MailBox::insert(Mail mail)
{
    mtx.lock();
    que.enqueue(mail);
    mtx.unlock();
}
