#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDockWidget"
#include <QDebug>
#include <utitlebar.h>
QTableWidgetItem* qti;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    QWidget* p = takeCentralWidget();
    if(p)
        delete p;

    //画布
    split = new Split(12);

    //键值对
    keyValue = new QTableWidget;
    keyValue->setColumnCount(2);
    keyValue->setRowCount(200);

    QStringList horizontalHeader;
    horizontalHeader<<QObject::tr("key")<<QObject::tr("value");

    keyValue->setHorizontalHeaderLabels(horizontalHeader);

    qti = new QTableWidgetItem(QString("jjj"));
    keyValue->setItem(2,0,qti);
    qDebug()<<qti;

    //   for(int i=0;i<100;i++)
    //    keyValue->setItem(i,0,new QTableWidgetItem(QString("fdfd")));

    //日志
    log = new ulog;

    dk_split = new QDockWidget("分屏画布",this);
    dk_split->setTitleBarWidget(new TitleBar("分屏画布",dk_split));
    dk_keyValue = new QDockWidget("键值对",this);
    dk_keyValue->setTitleBarWidget(new TitleBar("键值对",dk_split));
    dk_log = new QDockWidget("日志",this);
    dk_log->setTitleBarWidget(new TitleBar("日志",dk_split));

    //    dk_sp->setAllowedAreas(Qt::AllDockWidgetAreas);
    dk_split->setWidget(split);
    dk_keyValue->setWidget(keyValue);
    dk_log->setWidget(log);
    reLayout();

    //    addDockWidget(Qt::RightDockWidgetArea,dk_sp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    dk_log->setMinimumHeight(70);
    dk_log->setMaximumHeight(3000);
}

void MainWindow::reLayout()
{
    removeDockWidget(dk_split);
    removeDockWidget(dk_keyValue);
    removeDockWidget(dk_log);

    dk_log->setFixedHeight(250);

    addDockWidget(Qt::LeftDockWidgetArea,dk_split);
    splitDockWidget(dk_split,dk_keyValue,Qt::Horizontal);
    splitDockWidget(dk_split,dk_log,Qt::Vertical);
    dk_split->show();
    dk_keyValue->show();
    dk_log->show();


}

void MainWindow::on_action_reset_triggered()
{
    reLayout();
    dk_log->setMinimumHeight(70);
    dk_log->setMaximumHeight(3000);
}

void MainWindow::on_actiont_canvas_triggered()
{
    split->resetCanvas();
}

void MainWindow::on_actiont2_triggered()
{

}


