#include "myinputpanelcontext.h"

MyInputPanelContext::MyInputPanelContext()
{
  inputPanel = new MyInputPanel;
  connect(inputPanel, SIGNAL(stringGenerated(int)), SLOT(sendString(int)));
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
      inputPanel->exec();
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
void MyInputPanelContext::sendString(int keyCode)
{
//  qDebug()<<"sendString";
  //    QPointer<QWidget> w = focusWidget();
  QPointer<QWidget> w = inputPanel->getFocusedWidget();
  if (!w)
    return;
  QKeyEvent keyPress(QEvent::KeyPress, keyCode, Qt::NoModifier, QChar(keyCode));
  QApplication::sendEvent(w, &keyPress);

//  if (!w)
//    return;

  //    QKeyEvent keyRelease(QEvent::KeyPress, QChar('o').unicode(), Qt::NoModifier, text);
  //    QApplication::sendEvent(w, &keyRelease);
}
void MyInputPanelContext::updatePosition()
{
  QWidget *widget = focusWidget();
  if (!widget)
    return;

  QRect widgetRect = widget->rect();
  QPoint panelPos = QPoint(widgetRect.left(), widgetRect.top());

  if(panelPos.y()+widgetRect.height()>550)
    inputPanel->move(100,50);
  else
    inputPanel->move(100,550);
}
