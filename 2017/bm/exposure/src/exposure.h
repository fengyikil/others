#ifndef EXPOSURE_H
#define EXPOSURE_H

#include"BmCameraInterface.h"
#include<QList>
#include<QDialog>
#include <allAlg.h>
#include <QSettings>
extern QImage pimage;
enum{
    NO_AUTO_TEST=0,
    AUTO_TEST_MIN,
    AUTO_TEST_MAX,
};
enum{
    PRO_FREE=0,
    PRO_TRAINING_FOCUS,
    PRO_MANUAL_FOCUS,
};
namespace Ui {
class Exposure;
}

class Exposure : public QDialog
{
    Q_OBJECT

public:
    explicit Exposure(QWidget *parent = 0);
    ~Exposure();
    int init_camer();
    static void __stdcall ImageGrabedCallBack1(void * callBackOwner, unsigned char* pData, int nDataSize, int w, int h, int c);
//    void cal_pic();
    void update_data();

    void auto_test();
public:
    int state;

    //相机相关
    CBmCameraManager *m_pGigESystem;
    CBmCamera *pCam;
    std::vector<std::string> serialnumer;
    //配置参数
    QSettings* nowSet;
    int nowExposure;
    //算法类
    allAlg* myAlg;
    int ex_max;
    int ex_min;

    QString find_dir;
    Ui::Exposure *ui;
private slots:

    void re_cammer();
    void on_pushButton_load_clicked();
    void on_pushButton_realtime_clicked();
    void on_pushButton_one_clicked();

    void on_comboBox_cam_currentIndexChanged(const QString &arg1);


    void on_pushButton_eo_add_clicked();

    void on_pushButton_eo_sub_clicked();

    void on_pushButton_manual_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_auto_clicked();

    void on_comboBox_alg_currentIndexChanged(const QString &arg1);

signals:
    void cammer(void);
    void s_image(void);
};

#endif // EXPOSURE_H
