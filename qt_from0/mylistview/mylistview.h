#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QtGui>

class MyListView : public QWidget
{
        Q_OBJECT
public:
        MyListView();

private:
        QStringListModel *model;
        QListView *listView;

private slots:
        void insertData();
        void deleteData();
        void showData();
        void itemClicked(QModelIndex);
};

#endif // MYLISTVIEW_H
