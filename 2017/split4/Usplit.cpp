#include "ui_usplit.h"
#include "usplit.h"
#include <QPainter>
#include <QDebug>
#include <qmath.h>
Canvas::Canvas(QString m_id, QWidget *parent)
{
    //    px = QPixmap(1024,768);
    //    px.fill(Qt::black);
    px = nullptr;
    id = m_id;
    n_id = id.toInt();
    const_id = n_id;
}

Canvas::Canvas(int n, QWidget *parent)
{
    //    px = QPixmap(1024,768);
    //    px.fill(Qt::black);
    px = nullptr;
    id = QString::number(n);
    n_id = n;
    const_id = n_id;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    int w = this->width();
    int h = this->height();

    if(px!=nullptr)
    {
        //伸缩
        QPixmap pm = px->scaledToWidth(w); //按宽度伸缩 保持宽高比
        //    QPixmap pm = px.scaled(w,h);


        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing, true);

        //画pixmap
        paint.drawPixmap(0,0,pm);

        //画 id
        if(n_id!=0)
        {
            QPen p;
            p.setColor(Qt::red);
            p.setWidth(3);
            paint.setPen(p);
            paint.setFont(QFont("Arial", 10));
            paint.drawText(6,15,id);
        }
    }
}

void Canvas::setId(int i)
{
    n_id = i;
    id = QString::number(i);
}

void Canvas::setId(QString s)
{
    id = s;
    n_id = s.toInt();
}


Split::Split(int n,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Split)
{
    ui->setupUi(this);
    count = n;
    //初始化右键菜单栏
    menu = new QMenu();
    QAction* act;
    for(int i=1;i<=count;i++)
    {
        act = new QAction(QString::number(i), this);
        menu->addAction(act);
    }
    //初始化画布,pixmap
    for(int i=1;i<=count;i++)
    {
        QPixmap* p = new QPixmap(1024,768);
        p->fill(Qt::black);
        pixmpVector.append(p);

        Canvas* s = new Canvas(QString::number(i));
        s->px = p;
        s->installEventFilter(this);
        //        s->px = QPixmap::fromImage(QImage(":/image/1.jpg"));
        //        connect(s,SIGNAL(SendNum(int)),this,SLOT(canvas_double_clicked(int)));
        lst.append(s);
    }
    for(int i=0;i<8;i++)
    {
        Canvas* s = new Canvas(0);
        lst.append(s);
    }

    ui->gridLayout->addWidget(lst[0],0,0);
    ui->gridLayout->setSizeConstraint(QLayout::SetMinimumSize);

    phead = 0;
    mode = 1;
    old_mode = 1;
}


void Split::contextMenuEvent(QContextMenuEvent *e)
{

}

bool Split::eventFilter(QObject *watched, QEvent *event)
{
    qDebug()<<"Split::eventFilter";
    Canvas *obj = qobject_cast<Canvas*>(watched);
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        canvas_double_clicked(obj->const_id);
    }
    else if(event->type()==QEvent::ContextMenu)
    {
        QContextMenuEvent* cntEvent = static_cast<QContextMenuEvent*>(event);
        QAction* act = menu->exec(cntEvent->globalPos());
        if(act!=nullptr)
        {
//            obj->n_id = act->text().toInt();
//            obj->id = act->text();
            obj->setId(act->text());
            obj->px = pixmpVector[obj->n_id - 1];
            obj->update();
            qDebug()<<act->text();
        }
        else
            qDebug()<<"nullptr";

        qDebug()<<"QEvent::ContextMenu";
    }
    return QWidget::eventFilter(watched, event);
}

Split::~Split()
{
    delete ui;
}

void Split::resetCanvas()
{
//    foreach (Canvas* it, lst) {
//        it->setId(it->const_id);
//        qDebug()<<it->const_id;
//        it->px = pixmpVector[it->const_id -1];
//    }
    for(int i=1;i<=count;i++)
    {
        lst[i-1]->setId(i);
        lst[i-1]->px = pixmpVector[i-1];
    }
    update();
}

void Split::canvas_double_clicked(int num)
{
    int tmp;
    if(mode!=1&&old_mode!=1)
    {
        tmp=mode;
        mode =1;
        old_mode =tmp;
    }
    else
    {
        tmp = mode;
        mode = old_mode;
        old_mode =tmp;
    }

    if(mode==1)
    {
        tmp = phead;
        phead = num-1;
        old_phead = tmp;
    }
    else
    {
        phead = old_phead;
    }

    calGrid(phead,mode);
}

void Split::on_pushButton_front_clicked()
{
    if(phead!=0)
    {
        phead = phead - mode;
        if(phead<0)
            phead = 0;
        calGrid(phead,mode);
    }
}

void Split::on_pushButton_back_clicked()
{
    if(phead + mode <= count-1)
    {
        phead = phead + mode;
        calGrid(phead,mode);
    }
}

void Split::on_radioButton_1_clicked()
{
    mode = 1;
    old_mode =1;
    calGrid(phead,mode);
}

void Split::on_radioButton_4_clicked()
{
    mode = 4;
    old_mode =4;
    calGrid(phead,mode);
}

void Split::on_radioButton_9_clicked()
{
    mode = 9;
    old_mode =9;
    calGrid(phead,mode);
}

void Split::on_pushButton_draw_clicked()
{
    qDebug()<<"on_pushButton_draw_clicked";
    QPainter painter(&(*lst[phead]->px));
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen p;
    p.setWidth(2);
    p.setColor(Qt::green);
    painter.setPen(p);
    painter.drawLine(QPoint(50,0),QPoint(50,768));
    //        painter.drawLine(QPoint(50,0),QPoint(50,768));
    painter.drawEllipse(200,200,50,80);
    update();
}

void Split::on_pushButton_erase_clicked()
{
    lst[phead]->px->fill(Qt::black);
    update();
}

void Split::calGrid(int head, int md)
{
    int i,j,k;
    //hide
    for(int i = 0;i<lst.length();i++)
    {
        ui->gridLayout->removeWidget(lst[i]);
        lst[i]->hide();
    }

    //    ptail = phead+mode-1;
    //    if(ptail>=count)
    //        ptail = count;
    //show
    for(i=head,j=0,k=0;i<= head+md-1;i++)
    {
        ui->gridLayout->addWidget(lst[i],j,k);
        lst[i]->show();
        k++;
        if(k==qSqrt(md))
        {
            k=0;
            j++;
        }
    }
}
