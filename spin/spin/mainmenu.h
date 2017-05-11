#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QTimer>
#include "type.h"
namespace Ui {
  class MainMenu;
}

class MainMenu : public QWidget
{
  Q_OBJECT
  
public:
  explicit MainMenu(QWidget *parent = 0);
   QTimer *timer;
  ~MainMenu();
  
private:
  Ui::MainMenu *ui;
private slots:
  void Update();
  void on_toolButton_taida1_toggled(bool checked);
  void on_toolButton_taida2_toggled(bool checked);
  void on_toolButton_taida3_toggled(bool checked);
  void on_toolButton_taida4_toggled(bool checked);
  void on_toolButton_taida5_toggled(bool checked);

  void on_toolButton_freq1_toggled(bool checked);
  void on_toolButton_freq2_toggled(bool checked);
  void on_toolButton_freq3_toggled(bool checked);
  void on_toolButton_freq4_toggled(bool checked);
  void on_toolButton_freq5_toggled(bool checked);

  void on_toolButton_tem1_toggled(bool checked);
  void on_toolButton_tem2_toggled(bool checked);
  void on_toolButton_tem3_toggled(bool checked);
  void on_toolButton_tem4_toggled(bool checked);
  void on_toolButton_tem5_toggled(bool checked);

  void on_toolButton_bj1_toggled(bool checked);
  void on_toolButton_bj2_toggled(bool checked);
  void on_toolButton_bj3_toggled(bool checked);
  void on_toolButton_bj4_toggled(bool checked);
  void on_toolButton_bj5_toggled(bool checked);

signals:
  void SendMesg(struct MdMesg);
};

#endif // MAINMENU_H
