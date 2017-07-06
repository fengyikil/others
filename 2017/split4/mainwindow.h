#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTableView>
#include <QTableWidget>
#include <QPlainTextEdit>
#include <QMap>
#include <usplit.h>
#include <ulog.h>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void showEvent(QShowEvent *event);
    void reLayout();
private slots:
//    void UpdateKeyValue();
//    void UpdateLog(QString);

    void on_action_reset_triggered();
    void on_actiont_canvas_triggered();

    void on_actiont2_triggered();


private:
    Ui::MainWindow *ui;
    Split* split;
    QTableWidget* keyValue;
    ulog* log;

    QDockWidget *dk_split;
    QDockWidget *dk_keyValue;
    QDockWidget *dk_log;
    QMap<QString,QString> kv;
};



#endif // MAINWINDOW_H
