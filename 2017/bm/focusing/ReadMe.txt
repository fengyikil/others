名称：相机调焦程序(978_focusing)
作者：蒋俊杰
1.编译说明
   开发工具：Qt5.8.0 qtcreator
   依赖：haclcon, BmCameraInterface 依赖路径配置在978工程相关目录下，输出的exe文件在Vision978\Win32\Debug目录，详情参见 978_focusing.pro
2.源码说明
	源码比较简单,
	1.picview为自绘控件，大部分逻辑用来处理橡皮筋效果的红色矩形框，这个矩形框用来选中需要调焦的区域。
	2.focusing为程序的主控制流程逻辑。
	3.MeasureDistance为调焦视觉算法，由halcon导出。

3.注意：git clone下来的978。Vision978\Win32\Debug目录下缺少相机相关dll,需要手动去Vision978\App978\3rdparty\BmCameraInterface\bin将dll拷贝到Vision978\Win32\Debug下。

4.qt工程转vs工程命令: qmake -tp vc 978_exposure.pro

    

