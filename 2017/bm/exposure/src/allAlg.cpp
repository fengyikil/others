#include "allAlg.h"
#include "QDebug"
int test_ex;
allAlg::allAlg()
{
    alg1 = new CDUTTrayLocation();
    qDebug()<<"load param res"<<alg1->LoadParameter("..\\ModelPara\\DUTInTrayLocation");

    alg2 = new CSocketLocation();
    qDebug()<<"load param res"<<alg2->ReadParam("..\\ModelPara\\SocketLocationZeQin");

    alg3 = new CDUTSocketLocation();
    qDebug()<<"load param res"<<alg3->LoadParameter("..\\ModelPara\\DUTInSocketLocation");

    alg4 = new CPocketLocation();
    qDebug()<<"load param res"<<alg4->LoadParameter("..\\ModelPara\\PocketStatus");

    alg5 = new CTrayLocation();
    qDebug()<<"load param res"<<alg5->LoadParameter("..\\ModelPara\\TrayLocation");

}

bool allAlg::test_exposure(Alg alg, HImage image)
{
    int res;
    switch (alg) {
    case ALG_TEST:
    {
        if(test_ex>=3000&&test_ex<=7000)
            return true;
        else
            return false;
    }
        break;
    case ALG_DUTTrayLocation:
    {
        if(alg1!=NULL)
        {
            OutPutParam param;
            res = alg1->DUTLocation(image,0,param,true);
            if(res==0)
                return true;
            else
                return false;
        }
    }
        break;
    case ALG_SocketLocation:
    {
        double x,y,r;
        if(alg2!=NULL)
        {
            res = alg2->SocketLocation(image,0,180,x,y,r);
            if(res==0)
                return true;
            else
                return false;
        }
    }
        break;
    case ALG_DUTSocketLocation:{
        if(alg3!=NULL)
        {
            OutPutParam param;
            int angleFlg = 0;
            bool bForcePickUp=false;
            res = alg3->DUTLocation(image,angleFlg,bForcePickUp,param);
            if(res==0)
                return true;
            else
                return false;
        }
    }
        break;
    case ALG_PocketLocation:
    {
        OutPutParam param;
        res = alg4->PocketLocation(image,param);
        if(res==0)
            return true;
        else
            return false;
    }
        break;

    case ALG_TrayLocation:
    {
        double x,y,r;
        if(alg5!=NULL)
        {
            res = alg5->TrayLocation(image,x,y,r);
            return false;
        }
    }
        break;

    default:
        return false;
        break;
    }
}
