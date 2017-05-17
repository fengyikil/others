#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* Widget w;
    w.show()*/;
    GvGraphicview ggv;
//    ggv.setGeometry(200,200,100,100);
    ggv.show();
    return a.exec();
}
