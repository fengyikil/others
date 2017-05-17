#pragma once
#include "HalconCpp.h"
using namespace HalconCpp;


enum IMAGE_ERRO
{
	IMAGE_PRO_OK,
	IMAGE_PRO_TARGET_ERROR,
	IMAGE_PRO_CODE_ERROR,
	IMAGE_ERROR
};
class CMeasureDistance 
{
public:
	CMeasureDistance(void);
	~CMeasureDistance(void);

private:
	HObject image;
	HTuple Mean, hv_FocusMeanTuple, MaxGray;
    HTuple Deviation, hv_Indices,Row2,Column2;
    HObject  ho_Image,Rectangle,ImageReduced;
	HTuple   hv_FocusGradientTuple, hv_FocusGradient, hv_Max;
	int Num ;
	double Maxcontrast, Bestgray;
	void action_calculate_edge_gradient(HObject ho_Image, HTuple *hv_Mean);

public:
	//初始化变量函数
	void InitMeasureDistance();
	//图像处理函数
	/*
	 Index 为图片处理选择方式
	 MaxContrast 为返回的最大对比度基数
	 RealtimeContrast 为返回的实时对比度
	 BestGray 为返回的最佳灰度值
	 RealtimeGray 为返回的实时灰度值
	*/
    int  CMeasureDistance::PicProcess(HObject ho_Image, int Index,double &MaxContrast,double &RealtimeContrast ,double &BestGray,double &RealtimeGray,double column,double row,double Width,double Height);
};
