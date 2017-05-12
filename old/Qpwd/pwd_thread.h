#ifndef PWD_H
#define PWD_H
#include <QThread>

class PwdThread : public QThread
{
    Q_OBJECT
public:
    explicit PwdThread(QObject *parent = 0);
    void run();
public slots:
     void FilePwd(QString src,QString pwd);

signals:
     void SendQPd(int);
};

#endif // PWD_H
