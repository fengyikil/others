#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QtNetwork>
#include <QFile>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QTcpSocket *client;
    QFile dir_file;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_conect_clicked();

    void on_pushButton_disconect_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
