
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "hyperelliptic.h"



//*****************************************************************************//
//真正的程序应当如此，但是我在本地时输入后再创建，图像变为空了，所以截图为变量在程序中定值后的结果
//希望助教能讲一讲或者文件发在canvas上，指出我的错误在哪里
//截图为a = 200, b = 150, m =2, n = 1.8, N =10的输出结果
//*****************************************************************************//

int main()
{
    using namespace Graph_lib;
    
    Point tl(100, 100);
    double a, b, m, n, N;
    std::cin >> a >> b >> m >> n >> N;
    Simple_window win(tl, 600, 400, "Canvas");
    Point center(300, 200);
    hyperelliptic tmp(a, b, m, n, N, center);
    tmp.display();
    win.wait_for_button();
}