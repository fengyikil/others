#include "myinputpanel.h"

MyInputPanel::MyInputPanel(QWidget *parent) : QDialog(0, Qt::Tool | Qt::FramelessWindowHint),
  lastFocusedWidget(0)
{
  connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
          this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
  resize(701,166);
  capsLock = 1;
  mapRect.insert(QRect(5,5,60,35),"1");
  mapRect.insert(QRect(75,5,60,35),"2");
  mapRect.insert(QRect(145,5,60,35),"3");
  mapRect.insert(QRect(215,5,60,35),"4");
  mapRect.insert(QRect(285,5,60,35),"5");
  mapRect.insert(QRect(355,5,60,35),"6");
  mapRect.insert(QRect(425,5,60,35),"7");
  mapRect.insert(QRect(495,5,60,35),"8");
  mapRect.insert(QRect(565,5,60,35),"9");
  mapRect.insert(QRect(635,5,60,35),"0");

  mapRect.insert(QRect(5,45,60,35),"q");
  mapRect.insert(QRect(75,45,60,35),"w");
  mapRect.insert(QRect(145,45,60,35),"e");
  mapRect.insert(QRect(215,45,60,35),"r");
  mapRect.insert(QRect(285,45,60,35),"t");
  mapRect.insert(QRect(355,45,60,35),"y");
  mapRect.insert(QRect(425,45,60,35),"u");
  mapRect.insert(QRect(495,45,60,35),"i");
  mapRect.insert(QRect(565,45,60,35),"o");
  mapRect.insert(QRect(635,45,60,35),"p");

  mapRect.insert(QRect(5,85,60,35),"a");
  mapRect.insert(QRect(75,85,60,35),"s");
  mapRect.insert(QRect(145,85,60,35),"d");
  mapRect.insert(QRect(215,85,60,35),"f");
  mapRect.insert(QRect(285,85,60,35),"g");
  mapRect.insert(QRect(355,85,60,35),"h");
  mapRect.insert(QRect(425,85,60,35),"j");
  mapRect.insert(QRect(495,85,60,35),"k");
  mapRect.insert(QRect(565,85,60,35),"l");
  mapRect.insert(QRect(635,85,60,35),"Caps");

  mapRect.insert(QRect(5,125,60,35),"z");
  mapRect.insert(QRect(75,125,60,35),"x");
  mapRect.insert(QRect(145,125,60,35),"c");
  mapRect.insert(QRect(215,125,60,35),"v");
  mapRect.insert(QRect(285,125,60,35),"b");
  mapRect.insert(QRect(355,125,60,35),"n");
  mapRect.insert(QRect(425,125,60,35),"m");
  mapRect.insert(QRect(495,125,60,35),tr("."));
  mapRect.insert(QRect(565,125,60,35),tr("<--"));
 mapRect.insert(QRect(635,125,60,35),"Enter");
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


  painter.drawLine(700,0,700,165);
  painter.drawLine(700,165,0,165);

  //画背景
  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(177,217,240));
  painter.drawRect(0,0,700,165);

  //画按钮
  QMap<QRect,QString>::iterator it;
  for ( it = mapRect.begin(); it != mapRect.end(); ++it )
    {
      int x,y,w,h;
      QRect rect = it.key();
      x = rect.x();
      y = rect.y();
      w = rect.width();
      h= rect.height();

      painter.save();
      //填充区域
      if(it.value()==clickIndex)
        {
          painter.setBrush(QBrush(Qt::blue));
          painter.setPen(Qt::NoPen);
          painter.drawRect(it.key());
        }
      else
        {
          QLinearGradient grad(x+w*0.75,y+h*0.5,x+w*0.75,y);
          grad.setColorAt(0,QColor(186,195,205));
          grad.setColorAt(0.4,QColor(230,234,237));
          grad.setColorAt(0.8,QColor(186,195,205));
          painter.setBrush(grad);
          painter.setPen(Qt::NoPen);
          painter.drawRect(it.key());
        }
      //画字
      painter.setPen(Qt::black);
//      if(capsLock)
      painter.setFont(QFont("Times", 17,QFont::Bold));
//      else
//      painter.setFont(QFont("Times", 15,QFont::Bold));
      painter.drawText(it.key(),Qt::AlignCenter,it.value());
      painter.restore();
    }
  painter.restore();
}

void MyInputPanel::mousePressEvent(QMouseEvent *event)
{
  QMap<QRect,QString>::iterator it;
  if(event->button() & Qt::LeftButton)
    {
      for ( it = mapRect.begin(); it != mapRect.end(); ++it )
        {
          QRect rect = it.key();
          if(rect.contains(event->pos()))
            {
              update();
              clickIndex = it.value();

              if(it.value()=="<--")
                {
                 emit stringGenerated(Qt::Key_Backspace);
                }
              else if(it.value()=="Enter")
                {
                  qDebug()<<"come in";
//                  emit stringGenerated(Qt::Key_Enter);
                  this->hide();
                }
              else if(it.value()=="Caps")
                {
                  changeCaps();
                }
              else
                {
                  QString s = it.value();
                  emit stringGenerated(s[0].unicode());
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
  clickIndex.clear();
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

void MyInputPanel::changeCaps()
{
  if(!capsLock)
    {
      capsLock=1;
      mapRect[ QRect(5,45,60,35)] ="q";
      mapRect[ QRect(75,45,60,35)] ="w";
      mapRect[ QRect(145,45,60,35)] ="e";
      mapRect[ QRect(215,45,60,35)] ="r";
      mapRect[ QRect(285,45,60,35)] ="t";
      mapRect[ QRect(355,45,60,35)] ="y";
      mapRect[ QRect(425,45,60,35)] ="u";
      mapRect[ QRect(495,45,60,35)] ="i";
      mapRect[ QRect(565,45,60,35)] ="o";
      mapRect[ QRect(635,45,60,35)] ="p";

      mapRect[ QRect(5,85,60,35)] ="a";
      mapRect[ QRect(75,85,60,35)] ="s";
      mapRect[ QRect(145,85,60,35)] ="d";
      mapRect[ QRect(215,85,60,35)] ="f";
      mapRect[ QRect(285,85,60,35)] ="g";
      mapRect[ QRect(355,85,60,35)] ="h";
      mapRect[ QRect(425,85,60,35)] ="j";
      mapRect[ QRect(495,85,60,35)] ="k";
      mapRect[ QRect(565,85,60,35)] ="l";

      mapRect[QRect(5,125,60,35)] ="z";
      mapRect[QRect(75,125,60,35)] ="x";
      mapRect[QRect(145,125,60,35)] ="c";
      mapRect[QRect(215,125,60,35)] ="v";
      mapRect[QRect(285,125,60,35)] ="b";
      mapRect[QRect(355,125,60,35)] ="n";
      mapRect[QRect(425,125,60,35)] ="m";
       mapRect.insert(QRect(495,125,60,35),tr("-"));
    }
  else
    {
      capsLock=0;
      mapRect[ QRect(5,45,60,35)] ="Q";
      mapRect[ QRect(75,45,60,35)] ="W";
      mapRect[ QRect(145,45,60,35)] ="E";
      mapRect[ QRect(215,45,60,35)] ="R";
      mapRect[ QRect(285,45,60,35)] ="T";
      mapRect[ QRect(355,45,60,35)] ="Y";
      mapRect[ QRect(425,45,60,35)] ="U";
      mapRect[ QRect(495,45,60,35)] ="I";
      mapRect[ QRect(565,45,60,35)] ="O";
      mapRect[ QRect(635,45,60,35)] ="P";

      mapRect[ QRect(5,85,60,35)] ="A";
      mapRect[ QRect(75,85,60,35)] ="S";
      mapRect[ QRect(145,85,60,35)] ="D";
      mapRect[ QRect(215,85,60,35)] ="F";
      mapRect[ QRect(285,85,60,35)] ="G";
      mapRect[ QRect(355,85,60,35)] ="H";
      mapRect[ QRect(425,85,60,35)] ="J";
      mapRect[ QRect(495,85,60,35)] ="K";
      mapRect[ QRect(565,85,60,35)] ="L";

      mapRect[QRect(5,125,60,35)] ="Z";
      mapRect[QRect(75,125,60,35)] ="X";
      mapRect[QRect(145,125,60,35)] ="C";
      mapRect[QRect(215,125,60,35)] ="V";
      mapRect[QRect(285,125,60,35)] ="B";
      mapRect[QRect(355,125,60,35)] ="N";
      mapRect[QRect(425,125,60,35)] ="M";
       mapRect.insert(QRect(495,125,60,35),tr("."));
    }
}
