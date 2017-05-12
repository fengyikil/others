#include <iostream>
#include <stdio.h>
#include<QList>
#include<QMap>
#include <Windows.h>
using namespace std;
typedef void (*MYFUN)(void*);
typedef void (*MYFUN1)(int,int);


void add(int a,int b)
{
    int c = a+b;
    printf("res is %d\n",c);
}
void sub(int a,int b)
{
    int c = a-b;
    printf("res is %d\n",c);
}
void multi(int a,int b)
{
    int c = a*b;
    printf("res is %d\n",c);
}
QList<void*> *funList;
QMap<QString,void*> allVar;
DWORD WINAPI Threadloop(LPVOID lpParameter)
{
    void* fun;
    while (1) {
        printf("\n\n\n");
        printf("thread is run\n");
        foreach (fun, *funList) {
            (*(MYFUN1)fun)(5,6);
        }
        Sleep(1000);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    funList = new QList<void*>;
    QList<void*>* ml ;
    void* fun;
    //    cout << "Hello World!" << endl;
    //    printf("Helo World!\n");
    //    void* mf = (void*)add;
    //    MYFUN1 mf1 = (MYFUN1)mf;
    allVar.insert("funList",(void*)funList);
    allVar.insert("add",add);
    allVar.insert("sub",sub);
    allVar.insert("multi",multi);
    HANDLE HOne;
    HOne=CreateThread(NULL,0,Threadloop,NULL,0,NULL);
    funList->append(add);
    funList->append(sub);
    funList->append(multi);


    Sleep(5000);

    ml =(QList<void*>*) allVar["funList"];
    fun = allVar["add"];
    ml->removeOne(fun);

    Sleep(5000);

    //        ml =(QList<void*>*) allVar["funList"];
    fun = allVar["sub"];
    ml->removeOne(fun);

    Sleep(10000);

    return 0;
}
