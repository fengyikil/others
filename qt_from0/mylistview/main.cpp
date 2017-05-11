#include "mylistview.h"
#include <QtGui>
#include <QtSql>
#include <QApplication>
bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("spin.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}
void createFakeData()
{
    QSqlQuery query;
    query.exec("DROP TABLE Pwd");
    query.exec("DROP TABLE Mode");
    query.exec("DROP TABLE History");

    qDebug()<<query.exec("CREATE TABLE Pwd ("
                         "usrName VARCHAR(40) PRIMARY KEY NOT NULL, "
                         "pwd VARCHAR(40) NOT NULL)");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'kil', '123')");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'jj', '123')");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'kp', '193')");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'po', '163')");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'kiu', '133')");
    query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
               "'puj', '133')");
    QString s="133";
    query.prepare("select * from Pwd where pwd=:pwd");
    query.bindValue(":pwd",s);
    query.exec();
    while(query.next())
      {
        qDebug()<< query.isActive();
             qDebug()<< query.record().count();
        QString name = query.value(0).toString();
         qDebug()<<name;
//        qDebug()<<query.value(0)<<query.value(1)<<query.value(2);
      }

    qDebug()<<query.exec("CREATE TABLE mode ("
                         "id INTEGER PRIMARY KEY NOT NULL, "
                         "modeName VARCHAR(40) NOT NULL,"
                         "usrName VARCHAR(40) NOT NULL,"
                         "j1 FLOAT NOT NULL,"
                         "j2 FLOAT NOT NULL,"
                         "j3 FLOAT NOT NULL,"
                         "j4 FLOAT NOT NULL,"
                         "l1 FLOAT NOT NULL,"
                         "l2 FLOAT NOT NULL,"
                         "l3 FLOAT NOT NULL,"
                         "l4 FLOAT NOT NULL,"
                         "l5 FLOAT NOT NULL,"
                         "l6 FLOAT NOT NULL,"
                         "l7 FLOAT NOT NULL,"
                         "q1 FLOAT NOT NULL,"
                         "q2 FLOAT NOT NULL,"
                         "q3 FLOAT NOT NULL,"
                         "q4 FLOAT NOT NULL)"
                         );
    qDebug()<<query.exec("CREATE TABLE history ("
                         "id INTEGER PRIMARY KEY NOT NULL, "
                         "usrName VARCHAR(40) NOT NULL,"
                         "date  DATETIME NOT NULL,"
                         "j1 FLOAT NOT NULL,"
                         "j2 FLOAT NOT NULL,"
                         "j3 FLOAT NOT NULL,"
                         "j4 FLOAT NOT NULL,"
                         "l1 FLOAT NOT NULL,"
                         "l2 FLOAT NOT NULL,"
                         "l3 FLOAT NOT NULL,"
                         "l4 FLOAT NOT NULL,"
                         "l5 FLOAT NOT NULL,"
                         "l6 FLOAT NOT NULL,"
                         "l7 FLOAT NOT NULL,"
                         "q1 FLOAT NOT NULL,"
                         "q2 FLOAT NOT NULL,"
                         "q3 FLOAT NOT NULL,"
                         "q4 FLOAT NOT NULL)"
                         );
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bool existingData = QFile::exists("spin.dat");
    if (!createConnection())
        return 1;
    if (!existingData)
        createFakeData();
    MyListView w;
    w.show();
    
    return app.exec();
}
