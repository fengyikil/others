#ifndef     _MAP_H
#define    _MAP_H
//CMD
#define IO_0    1
#define IO_1    2
#define IO_2    3
#define B1_PU	4
#define B2_PU	5
#define B4_PU	7
#define B5_PU	8
#define B6_PU	9
#define V27_JR	10
#define XP_PU	11
#define ZP_PU	12
#define GP_PU	13
#define RE_DA   14
//IO value
#define F1_ON 	|= 0x0020;//2
#define F1_OFF 	&= 0xffdf;
#define F2_ON 	|= 0x0040;//2
#define F2_OFF 	&= 0xffbf;
#define F3_ON 	|= 0x0008;//2
#define F3_OFF 	&= 0xfff7;
#define F4_ON 	|= 0x0008;//1
#define F4_OFF 	&= 0xfff7;
#define F5_ON	|= 0x0800;//0
#define F5_OFF	&= 0xf7ff;
#define F6_ON	|= 0x0400;//0
#define F6_OFF	&= 0xfbff;
#define F7_ON	|= 0x0100;//0
#define F7_OFF	&= 0xfeff;
#define F8_ON	|= 0x1000;//0
#define F8_OFF	&= 0xefff;
#define F9_ON	|= 0x8000;//0
#define F9_OFF	&= 0x7fff;
#define F10_ON	|= 0x4000;//0
#define F10_OFF	&= 0xbfff;
#define F11_ON	|= 0x2000;//0
#define F11_OFF	&= 0xdfff;
#define F12_ON	|= 0x0200;//0
#define F12_OFF	&= 0xfdff;
#define F13_ON	|= 0x1000;//1
#define F13_OFF	&= 0xefff;
#define F14_ON	|= 0x0008;//0
#define F14_OFF	&= 0xfff7;
#define F15_ON 	|= 0x8000;//1
#define F15_OFF	&= 0x7fff;
#define F16_ON	31
#define F16_OFF	32
#define F17_ON	33
#define F17_OFF	34
#define F18_ON	35
#define F18_OFF	36
#define F19_ON	|= 0x0010;//1
#define F19_OFF	&= 0xffef;
#define F20_ON	|= 0x0001;//1
#define F20_OFF	&= 0xfffe;
#define F21_ON	|= 0x0002;//1
#define F21_OFF	&= 0xfffd;
#define F22_ON	|= 0x0004;//0
#define F22_OFF	&= 0xfffb;
#define F23_ON	|= 0x0004;//2
#define F23_OFF	&= 0xfffb;
#define F24_ON	|= 0x0040;//1
#define F24_OFF	&= 0xffbf;
#define F25_ON	|= 0x4000;//1
#define F25_OFF	&= 0xbfff;
#define F26_ON	|= 0x0800;//1
#define F26_OFF	&= 0xf7ff;
#define F27_ON	|= 0x0002;//2
#define F27_OFF	&= 0xfffd;
#define F28_ON	|= 0x0001;//2
#define F28_OFF	&= 0xfffe;
#define F29_ON	57
#define F29_OFF	58
#define F30_ON	59
#define F30_OFF	60
#define F31_ON	|= 0x0020;//1
#define F31_OFF	&= 0xffdf;
#define F32_ON	|= 0x0080;//2
#define F32_OFF	&= 0xff7f;
#define F33_ON	|= 0x0080;//1
#define F33_OFF	&= 0xff7f;
#define F34_ON	|= 0x0002;//0
#define F34_OFF	&= 0xfffd;
#define F35_ON	|= 0x0004;//1
#define F35_OFF	&= 0xfffb;
#define F36_ON
#define F36_OFF
#define B1_ON 	|= 0x0200;//1
#define B1_OFF	&= 0xfdff;
//#define B2_ON 	|= 0x2000;//1
//#define B2_OFF	&=  0xdfff;
#define GB_ON 	|= 0x2000;//1
#define GB_OFF	&=  0xdfff;

#define B3_ON 	|= 0x0100;//1
#define B3_OFF	&= 0xfeff;

#define V5_ON	|=0x0001;//0
#define V5_OFF 	&=0xfffe;

#define Z1_ON	|= 0x0040;//0
#define Z1_OFF	&= 0xffbf;

#define POW24v_ON |= 0x0080;//0
#define POW24v_OFF &= 0xff7f;//0

//OUT
#define FU_A         0x0002
#define FU_B         0x0001
#define FU_IN         0x0004
#define FU_OUT       0x0008
#define XB_DOOR      0x0020
#define XLB_DOOR     0x0010
#define KUAI_HY       0x0040
#define KUAI_GY       0x0080
#define YE_WEI        0x4000
#define QI_PAO         0x8000
#endif
