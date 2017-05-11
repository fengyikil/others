#include <QApplication>
#include "UiTop.h"
#include "myinputpanelcontext.h"
#include<QTextCodec>
#include<QObject>
#include <QtSql>
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
             "'root', '123456')");
  query.exec("INSERT INTO Pwd (usrName, pwd) VALUES ("
             "'kil', '123')");
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

  qDebug()<<query.exec("CREATE TABLE Mode ("
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
                       "q4 FLOAT NOT NULL,"
                       "s1 FLOAT NOT NULL,"
                       "s2 FLOAT NOT NULL,"
                       "s3 FLOAT NOT NULL,"
                       "s4 FLOAT NOT NULL)"
                       );
  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");
  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kp',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");
  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");
  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");
  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kiu',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");

  qDebug()<<query.exec("CREATE TABLE History ("
                       "date VARCHAR(40) NOT NULL,"
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
                       "q4 FLOAT NOT NULL,"
                       "s1 FLOAT NOT NULL,"
                       "s2 FLOAT NOT NULL,"
                       "s3 FLOAT NOT NULL,"
                       "s4 FLOAT NOT NULL)"
                       );
//  query.exec("INSERT INTO Mode VALUES ('<puj>', 'kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)");

  qDebug()<<query.exec(QString("INSERT INTO  History VALUES ('%1','kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(QDateTime::currentDateTime().date().toString("yyyy-MM-dd")));
   qDebug()<<query.exec(QString("INSERT INTO  History VALUES ('%1','kp',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(QDateTime::currentDateTime().date().toString("yyyy-MM-dd")));
  qDebug()<< query.exec(QString("INSERT INTO  History VALUES ('%1','kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(QDateTime::currentDateTime().date().toString("yyyy-MM-dd")));
   qDebug()<<query.exec(QString("INSERT INTO  History VALUES ('%1','kiu',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(QDateTime::currentDateTime().date().toString("yyyy-MM-dd")));
   qDebug()<<query.exec(QString("INSERT INTO  History VALUES ('%1','kil',1,2,3,4,1,2,3,4,1,2,3,4,5,6,7,1,2,3,4)").arg(QDateTime::currentDateTime().date().toString("yyyy-MM-dd")));

}
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));//设置编码以支持中文格式
  MyInputPanelContext *ic = new MyInputPanelContext;
  a.setInputContext(ic);
  //初始化数据库
  bool existingData = QFile::exists("spin.dat");
  if (!createConnection())
    return 1;
  if (!existingData)
    createFakeData();
  //设置全局文字大小
  QFont font  = a.font();
  font.setPointSize(15);
  a.setFont(font);
  Top w;
  w.show();
  
  return a.exec();
}
