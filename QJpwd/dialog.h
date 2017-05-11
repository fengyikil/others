#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QProgressDialog>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QProgressDialog* qpd;
private:
    Ui::Dialog *ui;

 public slots:
    void Browse1();
    void Browse2();
    void Pwd();
    void UpQpd(int);
signals:
  void SendPwd(QString,QString);
};

#endif // DIALOG_H
