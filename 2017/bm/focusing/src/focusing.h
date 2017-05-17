#ifndef FOCUSING_H
#define FOCUSING_H

#include"BmCameraInterface.h"
#include "MeasureDistance.h"
#include<QDialog>
extern QImage pimage;
//流程状态枚举
enum{
    PRO_FREE=0,
    PRO_TRAINING_FOCUS,
    PRO_MANUAL_FOCUS,
};
namespace Ui {
class Focusing;
}

class Focusing : public QDialog
{
    Q_OBJECT

public:
    explicit Focusing(QWidget *parent = 0);
    ~Focusing();
    static void __stdcall ImageGrabedCallBack1(void * callBackOwner, unsigned char* pData, int nDataSize, int w, int h, int c);

private:
    void pro_bt_color(int i);
    void update_data();

    int init_camer();
    //调用视觉算法计算清晰度、灰度
    void cal_pic();
    int state;
    //最好清晰度
    double best_qxd;
    //实时清晰度
    double realtime_qxd;
    //最好灰度
    double best_hdz;
    //实时灰度
    double realtime_hdz;
    //真实矩形参数
    double rec_x;
    double rec_y;
    double rec_w;
    double rec_h;
    //相机相关
    CBmCameraManager *m_pGigESystem;
    CBmCamera *pCam;
    std::vector<std::string> serialnumer;
    //算法类
    CMeasureDistance  cme;
    //浏览文件
    QString find_dir;

    Ui::Focusing *ui;
signals:
    //发送给自己的re_cammer,用于处理相机回调跨线程执行干扰gui eventloop
    void cammer(void);
    void s_image(void);
private slots:
    void re_cammer();
    void r_change_rec(double x,double y,double w, double h);

    void on_pushButton_load_clicked();
    void on_pushButton_realtime_clicked();
    void on_pushButton_one_clicked();

    void on_pushButton_pro_free_clicked();
    void on_pushButton_pro_training_clicked();
    void on_pushButton_pro_manual_clicked();

    void on_comboBox_cam_currentIndexChanged(const QString &arg1);

};

#endif // FOCUSING_H
