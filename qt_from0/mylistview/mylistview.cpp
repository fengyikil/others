#include "mylistview.h"
#include <QtSql>
MyListView::MyListView()
{
        model = new QStringListModel(this);
        QStringList data;
        QSqlQuery query;
        query.exec("select usrName from Pwd");
        while(query.next())
          {
            QString name = query.value(0).toString();
           data << name;
          }
//        data << "Letter A" << "Letter B" << "Letter C";
        model->setStringList(data);
        listView = new QListView(this);
        listView->setModel(model);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QHBoxLayout *btnLayout = new QHBoxLayout;
        QPushButton *insertBtn = new QPushButton(tr("insert"), this);
        QPushButton *delBtn = new QPushButton(tr("Delete"), this);
        QPushButton *showBtn = new QPushButton(tr("Show"), this);
        btnLayout->addWidget(insertBtn);
        btnLayout->addWidget(delBtn);
        btnLayout->addWidget(showBtn);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(listView);
        mainLayout->addLayout(btnLayout);
        this->setLayout(mainLayout);

        connect(insertBtn, SIGNAL(clicked()), this, SLOT(insertData()));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteData()));
        connect(showBtn, SIGNAL(clicked()), this, SLOT(showData()));

        connect(listView,SIGNAL(clicked(QModelIndex)),
         this,SLOT(itemClicked(QModelIndex)));

}

void MyListView::insertData()
{
        bool isOK;
        QString text = QInputDialog::getText(NULL, "Insert", "Please input new data:",
                                                                                 QLineEdit::Normal, "You are inserting new data.", &isOK);
        QSqlQuery query;
        if(isOK) {
                int row = listView->currentIndex().row();
                if(row==-1)
                    row = 0;
                qDebug()<<row;
                model->insertRows(row, 1);
                QModelIndex index = model->index(row);
                model->setData(index, text);
                listView->setCurrentIndex(index);
                listView->edit(index);
                query.prepare("INSERT INTO Pwd (usrName, pwd) VALUES ("
                              ":un, '123')");
                query.bindValue(":un",text);
                query.exec();
        }
}

void MyListView::deleteData()
{
      QSqlQuery query;

        query.prepare("DELETE from Pwd where usrName =:un");
        query.bindValue(":un",listView->currentIndex().data().toString());
        query.exec();
        if(model->rowCount() >=1) {
                model->removeRows(listView->currentIndex().row(), 1);
        }

}

void MyListView::showData()
{
        QStringList data = model->stringList();
        QString str;
        foreach(QString s, data) {
                str += s + "\n";
        }

        QMessageBox::information(this, "Data", str);
}

void MyListView::itemClicked(QModelIndex qx)
{
    qDebug()<<qx.data().toString();
}
