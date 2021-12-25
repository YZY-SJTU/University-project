# 计算机图形学 课题8 不同粒度的光线追踪

1.设备相关软件适配检查：//
  （1）在Windows操作系统下搜索dxdiag，检查设备是否安装DirectX12，无则需要进行更新//
![屏幕截图 2021-12-25 144526](https://user-images.githubusercontent.com/66478971/147379267-0e825565-d524-4b3c-be9a-9ce76c7d6ba2.png)//
  （2）在Windows操作系统下检查Windows Kits，至少在软件层面支持Shader Model 6.5（最好Windows Kits为10.0.19041.0及以上）//
  （3）检查本机的显示适配器，需要支持Shader Model 6.5（为20系或者30系显卡即可）//
2.项目源文件与使用//
  （1）所有工程的源文件都位于Project File文件夹下，共有5个项目文件，每个项目文件夹下的Models文件夹下有一个skull.txt文件，记录的是头骨模型的三角面元vertex与indices数据，由于模型载入使用path索引，故请不要移动该文件夹与文件夹下任意文件的位置
  （2）工程项目说明：
      fixed light文件夹使用的是位于(-100.0f,0.0f,0.0f)点光源，使用per pixel粒度的光线追踪，可看见miss部分的渲染情况是什么样的
      tessellation show文件夹pipeline的fillmode设置为D3D12_FILL_MODE_WIREFRAME，仅将三角面片的顶点连线上的像素染色，其余部分为背景色，可以更好地看出面片细分情况，想要查看不同曲面细分因子状况下的渲染情况，可以在HullShder.hlsl文件中改变tess的基值
![屏幕截图 2021-12-25 153628](https://user-images.githubusercontent.com/66478971/147380174-534cdc67-8c4a-41f5-a4e5-5026718a1c58.png)
      per vertex文件夹下使用的是从相机处发射光源，使用per vertex粒度的光线追踪的情况
      per pixel文件夹下使用的是从相机处发射光源，使用per pixel粒度的光线追踪的情况
      per tessellated vertex文件夹使用的是从相机处发射光源，使用per tessellated vertex粒度的光线追踪的情况,同样可以按照上述方法修改tess基值
  tips:运行产生的窗口右上角为对应的工程文件名，fps为对应帧率
  （3）工程项目使用：在对应文件夹下双击BasicTessellation.sln即可打开项目文件，其中主执行函数在main.cpp中，执行函数为WinMain函数，将调试模式转为debug-x64状态即可直接运行调试器，或者可以转为Realease状态，如果产生fxc编译出错信息，请尝试将hlsl文件的相关配置为如下情况（以Pixel Shader为例）：
![屏幕截图 2021-12-25 163656](https://user-images.githubusercontent.com/66478971/147381071-6dffc216-0644-4516-83d9-d2d1fa41c3f4.png)
