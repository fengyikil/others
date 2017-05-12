#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <QtSql>
class Global
{
public:
  QString loginName;
  QSqlRecord modeRecord;

};

extern class Global* global;
#endif // GLOBAL_H
