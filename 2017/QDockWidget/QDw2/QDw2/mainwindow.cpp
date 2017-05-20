#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* p = takeCentralWidget();
    if(p)
    delete p;
    reset_layout();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset_layout()
{
    removeDockWidget(ui->dockWidget1);
    removeDockWidget(ui->dockWidget2);
    removeDockWidget(ui->dockWidget3);
    removeDockWidget(ui->dockWidget4);

//    ui->dockWidget1->setMaximumWidth(50);
//    ui->dockWidget1->setMinimumWidth(50);
    ui->dockWidget1->setFixedWidth(50);

    ui->dockWidget3->setMaximumWidth(50);
    ui->dockWidget1->setMinimumWidth(50);

    ui->dockWidget4->setMaximumHeight(100);
    ui->dockWidget1->setMinimumHeight(100);

    addDockWidget(Qt::LeftDockWidgetArea,ui->dockWidget1);
    splitDockWidget(ui->dockWidget1,ui->dockWidget2,Qt::Horizontal);
    splitDockWidget(ui->dockWidget2,ui->dockWidget3,Qt::Horizontal);
    splitDockWidget(ui->dockWidget2,ui->dockWidget4,Qt::Vertical);

    ui->dockWidget1->show();
    ui->dockWidget2->show();
    ui->dockWidget3->show();
    ui->dockWidget4->show();


}

void MainWindow::showEvent(QShowEvent *event)
{
//    ui->dockWidget1->setMaximumWidth(3000);
//    ui->dockWidget1->setMinimumWidth(50);

    ui->dockWidget3->setMaximumWidth(3000);
    ui->dockWidget1->setMinimumWidth(50);

    ui->dockWidget4->setMaximumHeight(3000);
    ui->dockWidget4->setMinimumHeight(100);
}

void MainWindow::on_actionreset_triggered()
{
    reset_layout();
    ui->dockWidget1->setMaximumWidth(3000);
    ui->dockWidget1->setMinimumWidth(50);

    ui->dockWidget3->setMaximumWidth(3000);
    ui->dockWidget1->setMinimumWidth(50);

    ui->dockWidget4->setMaximumHeight(3000);
    ui->dockWidget4->setMinimumHeight(100);
}
