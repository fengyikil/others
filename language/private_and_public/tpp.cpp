//#include <QCoreApplication>
#include<stdio.h>
class Man
{
public:
    Man(){}
    Man* test();
    int getOld();
private:
    int old;
};
Man* Man::test()
{
    Man* pj = new Man;
    pj->old = 5;
    return pj;
}

int Man::getOld()
{
    return old;
}

int main(int argc, char *argv[])
{
    //    QCoreApplication a(argc, argv);

    Man *p1,*p2;
    p1 = new Man();
    p2 = p1->test();
    printf("p2.old is %d\n",p2->getOld());
    while (1) ;
    //    return a.exec();
}


