名称：相机自动曝光程序(978_exposure)
作者：蒋俊杰
1.编译说明
   开发工具：Qt5.8.0 qtcreator
   库依赖：haclcon, BmCameraInterface 依赖路径配置在978工程相关目录下，输出的exe文件在Vision978\Win32\Debug目录，详情参见 978_exposure.pro
   源码依赖：Vision978\App978\3rdparty\src\bmVision978\impl_v2 下面的各种视觉算法。
2.源码说明
	源码比较简单,
	1.picview为自绘控件，大部分逻辑用来处理橡皮筋效果的红色矩形框，这个矩形框通过宏 PIC_RED_RECT条件编译，此处为关。
	2.exposure为程序的主控制流程逻辑。
	3.App978\3rdparty\src\bmVision978\impl_v2 下为曝光视觉算法，由halcon导出。

3.注意：git clone下来的978。Vision978\Win32\Debug目录下缺少相机相关dll,需要手动去Vision978\App978\3rdparty\BmCameraInterface\bin将dll拷贝到Vision978\Win32\Debug下。

4.qt工程转vs工程命令: qmake -tp vc 978_exposure.pro


    

