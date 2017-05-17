#include "exposure.h"
#include "ui_exposure.h"
#include<QFileDialog>
#include <QFile>
#include <QDebug>
#include<QPixmap>
#include <windows.h>
#include <QThread>
#include <QMessageBox>
#include"picview.h"

static char dllDir[260];
void dll_change_dir(const char* dir)
{
    GetCurrentDirectoryA(260, dllDir);
    SetCurrentDirectoryA(dir);
}
void dll_restore_dir()
{
    SetCurrentDirectoryA(dllDir);
}

void __stdcall Exposure::ImageGrabedCallBack1(void * callBackOwner, unsigned char* pData, int nDataSize, int w, int h, int c)
{

    Exposure* f = (Exposure*)callBackOwner;
    pimage = QImage(pData, w, h, QImage::Format_Grayscale8);
    //    qDebug()<<"ImageGrabedCallBack1"<<QThread::currentThreadId();
    f->cammer();
}



Exposure::Exposure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exposure)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    find_dir="D:/";

    ui->setupUi(this);
    serialnumer.clear();
    state = NO_AUTO_TEST;
    nowSet = NULL;
    init_camer();
    connect(this,SIGNAL(cammer()),this,SLOT(re_cammer()));
    connect(this,SIGNAL(s_image()),ui->pvw,SLOT(update()));
    ui->pvw->init();

    myAlg = new allAlg();
}

Exposure::~Exposure()
{
    delete ui;
}

int Exposure::init_camer()
{
    std::string strReply;
    int nCamCount= 0;

    //        dll_change_dir("D:\\jjj\\978_Exposure\\lib\\");

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
        qDebug()<<"*******"<<QString::fromStdString(ser_num);
        ui->comboBox_cam->addItem(QString::fromStdString(ser_num));
        pCam->RegisterGrabedCallBack(this,Exposure::ImageGrabedCallBack1);
        pCam->StopCapture(strReply);
    }

    pCam = NULL;
    if(nCamCount==0)
        QMessageBox::about(NULL,"警告","找不到相机！");
    qDebug()<< "strReply is "<<strReply.c_str();

}


void Exposure::re_cammer()
{

    if(state!=NO_AUTO_TEST)
        auto_test();
    emit s_image();
}

void Exposure::update_data()
{

    ui->label_exposure->setText(QString::number(nowExposure));

}

void Exposure::auto_test()
{
    bool res;
    HObject m_SrcImage;
    std::string strReply;
    GenImage1Extern(&m_SrcImage,"byte",pimage.width(),pimage.height(),(Hlong)pimage.bits(),0);

    if(myAlg!=NULL)
    {
        res =  myAlg->test_exposure((Alg)ui->comboBox_alg->currentIndex(),(HImage)m_SrcImage);

        if(state==AUTO_TEST_MIN)
        {
            if(res)
            {
                ex_min = nowExposure;
                state =AUTO_TEST_MAX;
            }
            nowExposure =  nowExposure + 100;
            pCam->SetExposure(nowExposure,strReply);
            pCam->GrabOne(strReply);

        }
        else if(state ==AUTO_TEST_MAX )
        {
            if(res)
            {
                nowExposure =  nowExposure + 100;
                pCam->SetExposure(nowExposure,strReply);
                pCam->GrabOne(strReply);

            }
            else
            {
                ex_max = nowExposure;
                nowExposure =  (ex_max + ex_min)/2;
                res =  true;
                pCam->SetExposure(nowExposure,strReply);
                emit ui->pushButton_auto->click();
                //                state = NO_AUTO_TEST;
            }
        }
        //模拟测试用
        test_ex = nowExposure;

    }

    //更新界面
    if(res)
        ui->label_test_res->setText("true");
    else
        ui->label_test_res->setText("false");

    update_data();
}



void Exposure::on_pushButton_load_clicked()
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
    qDebug()<<"pimage"<<pimage.width()<<pimage.height();
    emit s_image();
    update_data();

    qDebug()<<dir;
}






void Exposure::on_pushButton_realtime_clicked()
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StartCapture(strReply);
    }

}

void Exposure::on_pushButton_one_clicked()
{
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->StopCapture(strReply);
        pCam->GrabOne(strReply);
    }
    qDebug()<<"pimage size :"<<pimage.width()<<pimage.height();

}


void Exposure::on_comboBox_cam_currentIndexChanged(const QString &arg1)
{
    double fExposMin;
    double fExposMax;
    std::string strReply;
    QVariant param;
    param.clear();

    std::string ser_num = arg1.toUtf8().constData();
    if(pCam!=NULL)
        pCam->StopCapture(strReply);

    pCam = m_pGigESystem->GetCameraBySerialNumer(ser_num,strReply);
    if(pCam!=NULL)
    {
        //配置文件
        if(nowSet!=NULL)
        {
            nowSet->sync();
            free(nowSet);
        }

        nowSet = new QSettings(ui->comboBox_cam->currentText()+".ini",QSettings::IniFormat);
        param =  nowSet->value(ui->comboBox_alg->currentText(),0);
        if(param.toInt()==0)
        {
            pCam->GetExposure(nowExposure,fExposMin,fExposMax,strReply);
        }
        else
        {
            nowExposure = param.toInt();
            pCam->SetExposure(nowExposure,strReply);
        }

        pCam->StartCapture(strReply);
    }
    update_data();
}

void Exposure::on_comboBox_alg_currentIndexChanged(const QString &arg1)
{
    double fExposMin;
    double fExposMax;
    std::string strReply;
    QVariant param;
    if(pCam!=NULL)
    {
        if(nowSet!=NULL)
            param =  nowSet->value(arg1,0);
        if(param.toInt()==0)
        {
            pCam->GetExposure(nowExposure,fExposMin,fExposMax,strReply);
        }
        else
        {
            nowExposure = param.toInt();
            pCam->SetExposure(nowExposure,strReply);
        }
    }
    update_data();
}


void Exposure::on_pushButton_eo_add_clicked()
{
    int nExpos;
    double fExposMin;
    double fExposMax;
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->GetExposure(nExpos,fExposMin,fExposMax,strReply);

        if(nExpos+100<100000)
            pCam->SetExposure(nExpos+100,strReply);

        pCam->GetExposure(nowExposure,fExposMin,fExposMax,strReply);
        test_ex = nowExposure;

    }

    update_data();

}

void Exposure::on_pushButton_eo_sub_clicked()
{
    int nExpos;
    double fExposMin;
    double fExposMax;
    std::string strReply;
    if(pCam!=NULL)
    {
        pCam->GetExposure(nExpos,fExposMin,fExposMax,strReply);

        if(nExpos-100>1000)
            pCam->SetExposure(nExpos-100,strReply);

        pCam->GetExposure(nowExposure,fExposMin,fExposMax,strReply);
        test_ex = nowExposure;
    }

    update_data();

}



void Exposure::on_pushButton_manual_clicked()
{
    bool res;
    HObject m_SrcImage;
    if(!pimage.isNull())
        GenImage1Extern(&m_SrcImage,"byte",pimage.width(),pimage.height(),(Hlong)pimage.bits(),0);
//    if(pCam!=NULL)
//    {

        if(myAlg!=NULL)
        {
            res =  myAlg->test_exposure((Alg)ui->comboBox_alg->currentIndex(),(HImage)m_SrcImage);
        }
        if(res)
            ui->label_test_res->setText("true");
        else
            ui->label_test_res->setText("false");


        qDebug()<<"test res is "<<res;
//    }
}

void Exposure::on_pushButton_save_clicked()
{
    if(nowSet!=NULL)
    {
        nowSet->setValue(ui->comboBox_alg->currentText(),nowExposure);
        nowSet->sync();
    }
}

void Exposure::on_pushButton_auto_clicked()
{
    std::string strReply;
    if(state==NO_AUTO_TEST)
    {
        if(pCam!=NULL)
        {
            nowExposure = 100;
            test_ex = 100;
            pCam->SetExposure(nowExposure,strReply);
            pCam->StopCapture(strReply);
            state = AUTO_TEST_MIN;
            pCam->GrabOne(strReply);
            // ui
            ui->pushButton_auto->setText("停止测试");
            ui->comboBox_alg->setDisabled(true);
            ui->comboBox_cam->setDisabled(true);
            ui->pushButton_manual->setDisabled(true);
            ui->pushButton_eo_add->setDisabled(true);
            ui->pushButton_eo_sub->setDisabled(true);
            ui->pushButton_one->setDisabled(true);
            ui->pushButton_realtime->setDisabled(true);
            ui->pushButton_save->setDisabled(true);
            ui->pushButton_load->setDisabled(true);
        }
    }
    else
    {
        state = NO_AUTO_TEST;
        pCam->StartCapture(strReply);
        // ui
        ui->pushButton_auto->setText("自动测试");
        ui->comboBox_alg->setDisabled(false);
        ui->comboBox_cam->setDisabled(false);
        ui->pushButton_manual->setDisabled(false);
        ui->pushButton_eo_add->setDisabled(false);
        ui->pushButton_eo_sub->setDisabled(false);
        ui->pushButton_one->setDisabled(false);
        ui->pushButton_realtime->setDisabled(false);
        ui->pushButton_save->setDisabled(false);
        ui->pushButton_load->setDisabled(false);

    }

}

