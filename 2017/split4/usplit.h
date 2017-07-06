#ifndef SPLIT_H
#define SPLIT_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class Split;
}

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QString m_id="0",QWidget *parent = 0);
    explicit Canvas(int n=0,QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *event);

    void setId(int i);
    void setId(QString s);
    QPixmap* px;
    int const_id;
    int n_id;
    QString id;
signals:
    void SendNum(int n_id);
public slots:
};



class Split : public QWidget
{
    Q_OBJECT

public:
    explicit Split(int n,QWidget *parent = 0);
    virtual void contextMenuEvent(QContextMenuEvent *);
    virtual bool eventFilter ( QObject * watched, QEvent * event );
    ~Split();
    void resetCanvas();
private slots:
    void canvas_double_clicked(int num);
    void on_pushButton_front_clicked();
    void on_pushButton_back_clicked();
    void on_radioButton_1_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_9_clicked();
    void on_pushButton_draw_clicked();
    void on_pushButton_erase_clicked();
private:
    void calGrid(int head,int md);
    QMenu *menu;
    QVector<QPixmap*> pixmpVector;
    QVector<Canvas*> lst;
    int mode;
    int old_mode;
    int phead;
    int old_phead;
    int count;
    Ui::Split *ui;
};

#endif // SPLIT_H
