#include <QCoreApplication>
#include <mytcpserver.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer  ns;
    ns.listen(QHostAddress::Any,6666);
    return a.exec();
}
