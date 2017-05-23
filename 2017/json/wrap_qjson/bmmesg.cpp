#include "bmmesg.h"
Bmmsg::Bmmsg(int mscope, int mid, QJsonObject mjson)
{
    scope = mscope;
    id = mid;
    json = mjson;

}

Bmmsg::Bmmsg(const Bmmsg &other)
{
    scope = other.scope;
    id = other.id;
    json = other.json;
}

Bmmsg &Bmmsg::operator =(const Bmmsg &other)
{
    scope = other.scope;
    id = other.id;
    json = other.json;
    return *this;
}

Bmmsg::~Bmmsg()
{

}

bool Bmmsg::isNULL()
{
    if(scope==0xffffffff)
        return true;
    else
        return false;
}

void Bmmsg::setJson(QJsonObject jn)
{
    json = jn;
}

void Bmmsg::setScope(int sp)
{
    scope = sp;
}

void Bmmsg::setId(int mid)
{
    id = mid;
}

void Bmmsg::add(QString name, QJsonValue value)
{
    json.insert(name,value);
}




Bmque::Bmque()
{
}

Bmque::~Bmque()
{

}

int Bmque::size()
{
    mtx.lock();
    int len = que.length();
    mtx.unlock();
    return len;
}

Bmmsg Bmque::out()
{
    Bmmsg bm;
    mtx.lock();
    if(!que.isEmpty())
    {
        bm = que.dequeue();
    }
    mtx.unlock();
    return bm;

}

Bmmsg Bmque::get(int scope, int id)
{
    Bmmsg bm;
    QList<Bmmsg>::iterator iter;
    mtx.lock();
    for(iter=que.begin();iter!=que.end();iter++)
    {
        if((*iter).id==id&&(*iter).scope==scope)
        {
            bm = (*iter);
            que.removeOne(*iter);
            break;
        }
    }
    mtx.unlock();

    return bm;
}

void Bmque::insert(Bmmsg &msg)
{
    if(!msg.isNULL())
    {
        mtx.lock();
        que.enqueue(msg);
        mtx.unlock();
    }
}

Bmque BMQue;
