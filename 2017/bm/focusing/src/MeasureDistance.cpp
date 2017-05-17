#include"MeasureDistance.h"


CMeasureDistance::CMeasureDistance(void)
{
    Maxcontrast = 0;
    Bestgray = 0;
}
CMeasureDistance::~CMeasureDistance(void)
{

}

void CMeasureDistance::InitMeasureDistance()
{
    hv_FocusGradientTuple = HTuple();
    hv_FocusMeanTuple = HTuple();
    Num = 0;
    Maxcontrast = 0;
    Bestgray = 0;
}
int  CMeasureDistance::PicProcess(HObject ho_Image, int Index,double &MaxContrast,double &RealtimeContrast ,double &BestGray,double &RealtimeGray,double column,double row,double Width,double Height)
{
    try {

        if (Index == 0)
        {
            SetSystem("flush_graphic", "false");
            Row2 = row + Height;
            Column2 = column + Width;
            GenRectangle1(&Rectangle,row,column,Row2,Column2);
            ReduceDomain(ho_Image,Rectangle,&ImageReduced);
            action_calculate_edge_gradient(ImageReduced, &hv_FocusGradient);
            hv_FocusGradientTuple = hv_FocusGradientTuple.TupleConcat(hv_FocusGradient);
            //计算
            TupleMax(hv_FocusGradientTuple, &hv_Max);
            TupleFind(hv_FocusGradientTuple, hv_Max, &hv_Indices);
            MaxContrast = hv_Max[0].D();//最大对比度基数
            Maxcontrast = MaxContrast;//保存最大对比度基数
            RealtimeContrast = hv_FocusGradient[0].D(); //实时对比度
            Intensity(Rectangle, ho_Image, &Mean, &Deviation);
            RealtimeGray = Mean[0].D();//实时灰度值
            hv_FocusMeanTuple = hv_FocusMeanTuple.TupleConcat(Mean);
            //通过X坐标找出最佳图片对应的灰度值
            //最佳灰度值
            BestGray = hv_FocusMeanTuple.TupleSelect( hv_Indices).D();
            Bestgray = BestGray;//保存最佳灰度值
            Num = 1;

        }
        if(Index == 1)
        {
            SetSystem("flush_graphic", "false");
            Row2 = row + Height;
            Column2 = column + Width;
            GenRectangle1(&Rectangle,row,column,Row2,Column2);
            ReduceDomain(ho_Image,Rectangle,&ImageReduced);

            action_calculate_edge_gradient(ImageReduced, &hv_FocusGradient);
            //hv_FocusGradientTuple = hv_FocusGradientTuple.TupleConcat(hv_FocusGradient);
            // i = (hv_FocusGradient / hv_Max).D();
            RealtimeContrast = hv_FocusGradient[0].D(); //实时对比度
            Intensity(ImageReduced, ho_Image, &Mean, &Deviation);
            RealtimeGray = Mean[0].D();//实时灰度值

            MaxContrast = Maxcontrast;//最大对比度基数
            BestGray = Bestgray;//最佳灰度值



        }
    }
    catch (HException e)
    {
        return false;
    }
    return IMAGE_PRO_OK;
}


void CMeasureDistance::action_calculate_edge_gradient(HObject ho_Image, HTuple *hv_Mean)
{

    // Local iconic variables
    HObject  ho_EdgeAmplitude;

    // Local control variables
    HTuple  hv_Deviation;

    SobelAmp(ho_Image, &ho_EdgeAmplitude, "sum_abs", 3);
    //根据图像的一次导数计算图像的边缘
    Intensity(ho_EdgeAmplitude, ho_EdgeAmplitude, &(*hv_Mean), &hv_Deviation);
    return;
}





