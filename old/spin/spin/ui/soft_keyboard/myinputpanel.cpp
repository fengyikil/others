#include "myinputpanel.h"

MyInputPanel::MyInputPanel(QWidget *parent) : QWidget(0, Qt::Tool | Qt::FramelessWindowHint),
  lastFocusedWidget(0)
{
  connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
          this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
  resize(281,231);
  textRect = QRect(5,5,270,30);
  mapRect.insert("7",QRect(5,50,60,35));
  mapRect.insert("8",QRect(75,50,60,35));
  mapRect.insert("9",QRect(145,50,60,35));
  mapRect.insert("C",QRect(215,50,60,35));

  mapRect.insert("4",QRect(5,95,60,35));
  mapRect.insert("5",QRect(75,95,60,35));
  mapRect.insert("6",QRect(145,95,60,35));
  mapRect.insert("Delete",QRect(215,95,60,35));

  mapRect.insert("1",QRect(5,140,60,35));
  mapRect.insert("2",QRect(75,140,60,35));
  mapRect.insert("3",QRect(145,140,60,35));
  mapRect.insert("Cancel",QRect(215,140,60,35));


  mapRect.insert("0",QRect(5,185,60,35));
  mapRect.insert("~",QRect(75,185,60,35));
  mapRect.insert(".",QRect(145,185,60,35));
  mapRect.insert("Enter",QRect(215,185,60,35));
}

MyInputPanel::~MyInputPanel()
{
}

bool MyInputPanel::event(QEvent *e){
//  switch (e->type()) {
////! [1]
//  case QEvent::WindowActivate:
//      if (lastFocusedWidget)
//          lastFocusedWidget->activateWindow();
//      break;
////! [1]
//  default:
//      break;
//  }

  return QWidget::event(e);
}

void MyInputPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.save();
  //画显边框


  painter.drawLine(280,0,280,231);
  painter.drawLine(281,230,0,230);

//  painter.drawLine(281,0,281,231);

  //画背景
  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(177,226,240));
  painter.drawRect(0,0,280,230);

   //画显示框
  painter.setBrush(QColor(186,195,205));
  painter.drawRect(textRect);
  painter.setPen(QColor(0,65,175));
  painter.setFont(QFont("Times", 20,QFont::Bold));

  if(text=="")
    painter.drawText(textRect,Qt::AlignCenter,"0");
  else
    painter.drawText(textRect,Qt::AlignCenter,text);

  painter.restore();
  painter.save();

  //画按钮
  QMap<QString,QRect>::iterator it;
  for ( it = mapRect.begin(); it != mapRect.end(); ++it )
    {
      int x,y,w,h;
      QRect rect = it.value();
      x = rect.x();
      y = rect.y();
      w = rect.width();
      h= rect.height();

      painter.save();
      //填充区域
      if(it.key()==clickIndex)
        {
          painter.setBrush(QBrush(Qt::blue));
          painter.setPen(Qt::NoPen);
          painter.drawRect(it.value());
        }
      else
        {
      QLinearGradient grad(x+w*0.75,y+h*0.5,x+w*0.75,y);
      grad.setColorAt(0,QColor(186,195,205));
      grad.setColorAt(0.4,QColor(230,234,237));
      grad.setColorAt(0.8,QColor(186,195,205));
      painter.setBrush(grad);
      painter.setPen(Qt::NoPen);
      painter.drawRect(it.value());
        }
        //画字
      painter.setPen(Qt::black);
      painter.setFont(QFont("Times", 12,QFont::Bold));
      painter.drawText(it.value(),Qt::AlignCenter,it.key());
      painter.restore();
    }
  painter.restore();
}

void MyInputPanel::mousePressEvent(QMouseEvent *event)
{
  QMap<QString,QRect>::iterator it;
  if(event->button() & Qt::LeftButton)
    {
      for ( it = mapRect.begin(); it != mapRect.end(); ++it )
        {
          QRect rect = it.value();
          if(rect.contains(event->pos()))
            {
              update();
              clickIndex = it.key();
              if(it.key()=="1"||it.key()=="2"||it.key()=="3"||it.key()=="4"||it.key()=="5"||it.key()=="6"||it.key()=="7"||it.key()=="8"||it.key()=="9")
                {
                  qDebug()<<it.key();
                  if(text.isNull())
                    inputState = 1;

                  text.append(it.key());

                }
              else if(it.key()=="0")
                {
                  qDebug()<<"0";
                  if(inputState)
                    {
                      text.append("0");
                    }
                }
              else if(it.key()=="~")
                {
                  if(text!="")
                    {
                      if(text.startsWith("-"))
                        text.remove(0,1);
                      else
                        text.prepend("-");
                    }
                }
              else if(it.key()==".")
                {

                  if(inputState==0)
                    {
                      text.append("0");
                      text.append(it.key());
                      inputState = 2;
                      qDebug()<<".";
                    }
                  else if(inputState==1)
                    {
                      text.append(it.key());
                      inputState = 2;
                    }

                }
              else if(it.key()=="C")
                {
                  inputState = 0;
                  text.clear();
                }
              else if(it.key()=="Delete")
                {
                  if(text.endsWith("."))
                    {
                      text.remove(text.size()-1,1);
                      if(text=="0")
                        {
                          text.clear();
                          inputState = 0;
                        }
                      else
                          inputState = 1;
                    }
                  else
                    {
                    text.remove(text.size()-1,1);
                    if(text=="")
                       inputState = 0;
                    }
                  qDebug()<<inputState;

                }
             else if(it.key()=="Cancel")
                {
                  this->hide();
                }
              else if(it.key()=="Enter")
                {
//                    qDebug()<<"come in";
                    emit stringGenerated(text);

                this->hide();
                }
            }
        }
    }
}

void MyInputPanel::mouseReleaseEvent(QMouseEvent *event)
{
  clickIndex.clear();
  update();
}

void MyInputPanel::hideEvent(QHideEvent *)
{
  text.clear();
  inputState = 0;
  clickIndex="";
}
void MyInputPanel::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
//  qDebug()<<"focus change";
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
        lastFocusedWidget = newFocus;
    }
}
QWidget *MyInputPanel::getFocusedWidget()
{
   return lastFocusedWidget;
}
