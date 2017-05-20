#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_p1_clicked()
{
    ui->dockWidgetContents->hide();

}

void MainWindow::on_pushButton_p2_clicked()
{
    ui->dockWidget->hide();

}

void MainWindow::on_pushButton_p3_clicked()
{
    ui->dockWidgetContents->show();

}

void MainWindow::on_pushButton_p4_clicked()
{
    ui->dockWidget->show();

}
