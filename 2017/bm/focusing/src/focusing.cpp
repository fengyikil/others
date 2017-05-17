#include "ui_Focusing.h"
#include<QFileDialog>
#include <QFile>
#include <QDebug>
#include<QPixmap>
#include <windows.h>
#include <QThread>
#include <QMessageBox>
#include "focusing.h"
#include"picview.h"
static char dllDir[260];
//开发调试用,改变dll的查找路径
void dll_change_dir(const char* dir)
{
    GetCurrentDirectoryA(260, dllDir);
    SetCurrentDirectoryA(dir);
}
void dll_restore_dir()
{
    SetCurrentDirectoryA(dllDir);
}

void __stdcall Focusing::ImageGrabedCallBack1(void * callBackOwner, unsigned char* pData, int nDataSize, int w, int h, int c)
{

    Focusing* f = (Focusing*)callBackOwner;
    pimage = QImage(pData, w, h, QImage::Format_Grayscale8);
    qDebug()<<"ImageGrabedCallBack1"<<QThread::currentThreadId();
    f->cammer();
}



Focusing::Focusing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Focusing)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    find_dir="D:/";
    realtime_qxd =0;
    best_qxd = 0;
    best_hdz = 0;
    realtime_hdz = 0;

    ui->setupUi(this);
    serialnumer.clear();
    init_camer();
    connect(this,SIGNAL(cammer()),this,SLOT(re_cammer()));
    connect(this,SIGNAL(s_image()),ui->pvw,SLOT(update()));
    connect(ui->pvw,SIGNAL(s_change_rec(double,double,double,double)),this,SLOT(r_change_rec(double,double,double,double)));
    ui->pvw->init();
}

Focusing::~Focusing()
{
    delete ui;
}

int Focusing::init_camer()
{
    std::string strReply;
    int nCamCount= 0;

//        dll_change_dir("D:\\jjj\\978_fit\\lib\\");

    if (!BmLoadManagerFromDll("BummerCamera.dll", &m_pGigESystem, strReply))
    {
        QMessageBox::about(NULL,"警告","加载相机动态库 BummerCamera.dll异常");
        qDebug()<<QString::fromStdString(strReply);
        exit(0);
    }
    m_pGigESystem->Open(strReply);
    m_pGigESystem->GetCameraCount(nCamCount, strReply);
    m_pGigESystem->EnumAllCamName(serialnumer,strReply);
    qDebug()<<"nCamCount is " <<nCamCount;
    for (int i=0; i<nCamCount; i++)
    {

        std::string ser_num;
        pCam = m_pGigESystem->GetCameraByIndex(i, strReply);

        if (pCam == NULL)
        {

            m_pGigESystem->Close(strReply);
            m_pGigESystem = NULL;
            return FALSE;
        }

        if (!pCam->InitializeCamera(strReply))
        {

             qDebug()<<"InitializeCamera";
            m_pGigESystem->Close(strReply);
            m_pGigESystem = NULL;
            pCam = NULL;
            return FALSE;
        }
        //ui add

        ser_num = serialnumer.at(i);
        qDebug()<<QString::fromStdString(ser_num);
        ui->comboBox_cam->addItem(QString::fromStdString(ser_num));
        pCam->RegisterGrabedCallBack(this,Focusing::ImageGrabedCallBack1);
        pCam->StopCapture(strReply);
    }

    pCam = NULL;
    if(nCamCount==0)
        QMessageBox::about(NULL,"警告","找不到相机！");
    qDebug()<< "strReply is "<<strReply.c_str();

}

void Focusing::pro_bt_color(int i)
{
    ui->pushButton_pro_free->setStyleSheet("");
    ui->pushButton_pro_training->setStyleSheet("");
    ui->pushButton_pro_manual->setStyleSheet("");
    switch (i) {
    case PRO_FREE:
        ui->pushButton_pro_free->setStyleSheet("background-color: rgb(255, 85, 0);");
        break;
    case PRO_TRAINING_FOCUS:
        ui->pushButton_pro_training->setStyleSheet("background-color: rgb(255, 85, 0);");
        break;
    case PRO_MANUAL_FOCUS:
        ui->pushButton_pro_manual->setStyleSheet("background-color: rgb(255, 85, 0);");
        break;
    default:
        break;
    }
}

void Focusing::cal_pic()
{
    HObject m_SrcImage;
    if(!pimage.isNull())
    {
        GenImage1Extern(&m_SrcImage,"byte",pimage.width(),pimage.height(),(Hlong)pimage.bits(),0);
        int res;
        if(state == PRO_TRAINING_FOCUS )
            res = cme.PicProcess(m_SrcImage,0,best_qxd,realtime_qxd,best_hdz,realtime_hdz,rec_x,rec_y,rec_w,rec_h);
        else
            res = cme.PicProcess(m_SrcImage,1,best_qxd,realtime_qxd,best_hdz,realtime_hdz,rec_x,rec_y,rec_w,rec_h);
    }
}

void Focusing::re_cammer()
{
    cal_pic();
    update_data();
    emit s_image();
}

void Focusing::update_data()
{
    int per;

    ui->label_best_qxd->setText(QString::number(best_qxd,'g',3));
    ui->label_realtime_qxd->setText(QString::number(realtime_qxd,'g',3));
    ui->label_best_hdz->setText(QString::number(best_hdz,'g',3));
    ui->label_realtime_hdz->setText(QString::number(realtime_hdz,'g',3));


    if(state==PRO_MANUAL_FOCUS)
    {
        if(best_qxd>0.001)
            per = (qAbs(realtime_qxd)/best_qxd)*100;
        else
            per = 0;
    }
    else
    {
        per = 0;
    }
    ui->label_qxd_per->setText(QString::number(per)+"%");
    if(per>=95&&per<=100)
        ui->label_qxd_per->setStyleSheet("color:green");
    else
        ui->label_qxd_per->setStyleSheet("color:red");

}


void Focusing::on_pushButton_load_clicked()
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StopCapture(strReply);
    }

    QString dir = QFileDialog::getOpenFileName(this, tr("Open File"),find_dir,tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if(dir.isEmpty())
        return;
    else
        find_dir = dir;
    pimage.load(dir);
    emit s_image();
    cal_pic();
    update_data();
}






void Focusing::on_pushButton_realtime_clicked()
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StartCapture(strReply);
    }

}

void Focusing::on_pushButton_one_clicked()
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StopCapture(strReply);
        pCam->GrabOne(strReply);
    }
}



void Focusing::on_pushButton_pro_free_clicked()
{
    state = PRO_FREE;
    pro_bt_color(PRO_FREE);

    cme.InitMeasureDistance();
    best_qxd = 0;
    best_hdz = 0;
    realtime_hdz = 0;
    realtime_qxd = 0;
    update_data();

}

void Focusing::on_pushButton_pro_training_clicked()
{
    state = PRO_TRAINING_FOCUS;
    pro_bt_color(PRO_TRAINING_FOCUS);
    cme.InitMeasureDistance();
    std::string strReply;
    if(pCam!=NULL)
        pCam->StartCapture(strReply);
}

void Focusing::on_pushButton_pro_manual_clicked()
{
    state = PRO_MANUAL_FOCUS;
    pro_bt_color(PRO_MANUAL_FOCUS);
}

void Focusing::r_change_rec(double x,double y,double w, double h)
{
    rec_x = x;
    rec_y = y;
    rec_w = w;
    rec_h = h;
    cal_pic();
    update_data();

}

void Focusing::on_comboBox_cam_currentIndexChanged(const QString &arg1)
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StopCapture(strReply);
    }
    std::string ser_num = arg1.toUtf8().constData();
    pCam = m_pGigESystem->GetCameraBySerialNumer(ser_num,strReply);
    if(pCam!=NULL)
    {
        pCam->StartCapture(strReply);
    }
}


