#ifndef ULOG_H
#define ULOG_H

#include <QWidget>

namespace Ui {
class ulog;
}

class ulog : public QWidget
{
    Q_OBJECT

public:
    explicit ulog(QWidget *parent = 0);
    ~ulog();

private:
    Ui::ulog *ui;
};

#endif // ULOG_H
