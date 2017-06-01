#include "mail.h"
//PoxtOffice postOffice;
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

bool Mail::isEmpty()
{
    if(msg.isEmpty())
        return true;
    else
        return false;
}





MailBox::MailBox(QString ad)
{
    addr = ad;
    filter.clear();
    pxtf=NULL;
}

MailBox::~MailBox()
{
    if(pxtf!=NULL)
    {
        pxtf->disRegisterMailBox(addr);
    }
}

bool MailBox::registerPoxtOffice(PoxtOffice *pf)
{
    bool res;
    if(pxtf!=NULL)
    {
        pxtf->disRegisterMailBox(addr);
    }
    res = pf->RegisterMailBox(this);
    return res;
}

int MailBox::count()
{
    int count;
    mtx.lock();
    count = que.count();
    mtx.unlock();
    return count;
}

QString MailBox::getAddr()
{
    return addr;
}

void MailBox::setFilter(QStringList &strlist)
{
    filter = strlist;
}

void MailBox::addFilter(QString str)
{
    filter.append(str);
}

void MailBox::subFilter(QString str)
{
    filter.removeOne(str);
}

void MailBox::postMail(Mail &mail,QString to)
{
    mail.insertMsg("from",QJsonValue(addr));
    if(pxtf==NULL)
        return;
    if(addr=="god")
    {
        if(to=="all")
        {
            foreach (QString key,pxtf->office.keys())
            {
                if(key!=addr && key != "devil")
                {
                    //                if(!(pxtf->office[key]->filter.contains(addr)))
                    pxtf->office[key]->insert(mail);  //god 无视对方过滤器硬塞消息

                }
            }
        }
        else
        {
            if(pxtf->office.contains(to) && to!=addr && to!="devil")
            {
                //                if(!(pxtf->office[to]->filter.contains(addr)))
                pxtf->office[to]->insert(mail);//god 无视对方过滤器硬塞消息
            }
        }
    }
    else if(addr=="devil")
    {
        return; //devil不准给任何人发消息
    }
    else //普通用户
    {
        if(to=="all")
        {
            foreach (QString key,pxtf->office.keys())
            {
                if(key!=addr && key != "devil" && key!="god")
                {
                    if(!(pxtf->office[key]->filter.contains(addr)))
                    {
                        pxtf->office[key]->insert(mail);
                    }
                }
            }

            if(pxtf->godMonitor) //god监听模式打开可以收所有邮件
                pxtf->office.value("god")->insert(mail);

        }
        else
        {
            if(pxtf->office.contains(to) && to!=addr && to!="devil")
            {
                if(!(pxtf->office[to]->filter.contains(addr)))
                    pxtf->office[to]->insert(mail);

                if(pxtf->godMonitor) //god监听模式打开可以收所有邮件
                    pxtf->office.value("god")->insert(mail);
            }
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

void MailBox::setPoxtOffice(PoxtOffice *pf)
{
    pxtf = pf;
}

void MailBox::disRepeat()
{
    QQueue<Mail> tque;
    foreach (Mail mail, que){
        if(tque.contains(mail))
            que.removeOne(mail);
        else
            tque.append(mail);
    }
}

void MailBox::insert(Mail &mail)
{
    mtx.lock();
    que.enqueue(mail);
    mtx.unlock();
}

PoxtOffice::PoxtOffice(){
    office.clear();
    godMonitor =false;
    createMailBox("devil"); //创建失败的情况，被限制给任何人发消息
    createMailBox("god"); //上帝模式，可以给任何人发消息，并且不受过滤器影响
}

int PoxtOffice::count(){
    return office.count();
}

MailBox *PoxtOffice::createMailBox(QString addr){
    MailBox* mb = NULL;
    mtx.lock();
    if(office.contains(addr))
    {
        mb = office.value("devil");
    }
    else
    {
        mb = new MailBox(addr);
        mb->setPoxtOffice(this);
        office.insert(addr,mb);
    }
    mtx.unlock();
    return mb;
}

MailBox *PoxtOffice::getMailBox(QString addr)
{
    MailBox* mb = NULL;
    mtx.lock();
    if(office.contains(addr))
    {
        mb = office.value(addr);
    }
    else
    {
        mb = office.value("devil");
    }
    mtx.unlock();
    return mb;
}

bool PoxtOffice::RegisterMailBox(MailBox* mb)
{
    bool res;
    mtx.lock();
    if(mb==NULL||office.contains(mb->addr))
    {
        res =  false;
    }
    else
    {
        office.insert(mb->addr,mb);
        mb->pxtf = this;
        res = true;
    }
    mtx.unlock();
    return res;

}

void PoxtOffice::disRegisterMailBox(QString addr)
{
    if(addr!="god"&&addr!="devil")
    {
        mtx.lock();
        if(office.contains(addr))
            office.remove(addr);
        mtx.unlock();

    }
}

void PoxtOffice::setGodMonitor(bool gmt)
{
    godMonitor=gmt;
}

bool PoxtOffice::getGodMonitor()
{
    return godMonitor;
}
