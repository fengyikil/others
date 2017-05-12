#include "myinputpanelcontext.h"

MyInputPanelContext::MyInputPanelContext()
{
  inputPanel = new MyInputPanel;
  connect(inputPanel, SIGNAL(stringGenerated(QString)), SLOT(sendString(QString)));
}
MyInputPanelContext::~MyInputPanelContext()
{
    delete inputPanel;
}
bool MyInputPanelContext::filterEvent(const QEvent* event)
{
  qDebug()<<"event type is"<<event->type();
    if (event->type() == QEvent::RequestSoftwareInputPanel) {
        updatePosition();
        inputPanel->show();
        return true;
    } else if (event->type() == QEvent::CloseSoftwareInputPanel) {
        inputPanel->hide();
        return true;
    }
    return false;
}
QString MyInputPanelContext::identifierName()
{
    return "MyInputPanelContext";
}

void MyInputPanelContext::reset()
{
}
bool MyInputPanelContext::isComposing() const
{
    return false;
}

QString MyInputPanelContext::language()
{
    return "en_US";
}
void MyInputPanelContext::sendString(QString text)
{
  qDebug()<<"sendString";
  //    QPointer<QWidget> w = focusWidget();
QPointer<QWidget> w = inputPanel->getFocusedWidget();
    if (!w)
        return;

    QKeyEvent keyPress(QEvent::KeyPress, QChar('o').unicode(), Qt::NoModifier, text);
    QApplication::sendEvent(w, &keyPress);

    if (!w)
        return;

//    QKeyEvent keyRelease(QEvent::KeyPress, QChar('o').unicode(), Qt::NoModifier, text);
//    QApplication::sendEvent(w, &keyRelease);
}
void MyInputPanelContext::updatePosition()
{
  int x,y;
    QWidget *widget = focusWidget();
    if (!widget)
        return;

    QRect widgetRect = widget->rect();
    QPoint panelPos = QPoint(widgetRect.left(), widgetRect.top());

    panelPos = widget->mapToGlobal(panelPos);
    if(panelPos.x()+widget->width()+inputPanel->width()+5<1024)
      {
        panelPos.setX(panelPos.x()+widget->width()+5);
      }
    else
      {
          panelPos.setX(panelPos.x()-inputPanel->width()-5);
      }
    if(panelPos.y()+inputPanel->height()+5>=768)
      {
        panelPos.setY(768-5-inputPanel->height());
      }
    inputPanel->move(panelPos);
}
