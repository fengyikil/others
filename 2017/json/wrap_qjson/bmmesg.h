#ifndef BMMESG_H
#define BMMESG_H

#include<QtCore>
#define BMPARAM(arg){QJsonValue(arg)}
#define BMPARAM_ARRY(arg){QJsonArray(arg)}

class Bmmsg
{
public:
    Bmmsg(int mscope=0xffffffff,int mid=0, QJsonObject mjson=QJsonObject());
    Bmmsg(const Bmmsg &other);
    Bmmsg &operator =(const Bmmsg &other);
    ~Bmmsg();
    operator QString() const {
        if(scope!=0xffffffff)
            return QString("<Bmmsg scope: %1 id: %2>")
                    .arg(QString::number(scope))
                    .arg(QString::number(id));
        else
            return QString("<Bmmsg NULL >");

    }
    bool isNULL();
    void setScope(int sp);
    void setId(int mid);
    void add(QString name,QJsonValue value);


    void setJson(QJsonObject jn);

    int scope;
    int id;
    QJsonObject json;
};
//Q_DECLARE_METATYPE(Bmmsg)

class Bmque
{
public:
    Bmque();
    ~Bmque();

    QQueue<Bmmsg> que;
    QMutex mtx;
    int size();
    void insert(Bmmsg&);
    Bmmsg out();
    Bmmsg get(int scope,int id);
};
extern class Bmque BMQue;

#endif // BMMESG_H
