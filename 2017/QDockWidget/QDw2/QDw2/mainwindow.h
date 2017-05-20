#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void reset_layout();
    void showEvent(QShowEvent *event);
private slots:
    void on_actionreset_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
