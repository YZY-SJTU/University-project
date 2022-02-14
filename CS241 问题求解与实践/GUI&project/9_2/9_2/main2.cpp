
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "righttriangle.h"
 
//------------------------------------------------------------------------------


//*****************************************************************************//
//真正的程序应当如此，但是我在本地时输入后再创建，图像变为空了，所以截图为变量在程序中定值后的结果
//希望助教能讲一讲或者文件发在canvas上，指出我的错误在哪里
//截图为长边定为80，短边定为60时的正八边形
//*****************************************************************************//

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    
    Point vertex[8];
    double length_longer = 80, length_shorter = 60;
    std::cout << "Please input the lengths of two right-edge" << endl;
    //std::cin >> length_longer >> length_shorter;
    if (length_longer < length_shorter)
    {
        double tmp = length_shorter;
        length_shorter = length_longer;
        length_longer = tmp;
    }
    //计算八边形各个顶点坐标
    vertex[0].x = 200;
    vertex[0].y = 100;
    vertex[1].x = vertex[0].x + int(length_longer);
    vertex[1].y = vertex[0].y;
    vertex[2].x = vertex[1].x + int(length_longer / sqrt(2));
    vertex[2].y = vertex[1].y + int(length_longer / sqrt(2));
    vertex[3].x = vertex[2].x;
    vertex[3].y = vertex[2].y + int(length_longer);
    vertex[4].x = vertex[3].x - int(length_longer / sqrt(2));
    vertex[4].y = vertex[3].y + int(length_longer / sqrt(2));
    vertex[5].x = vertex[4].x - int(length_longer);
    vertex[5].y = vertex[4].y;
    vertex[6].x = vertex[5].x - int(length_longer / sqrt(2));
    vertex[6].y = vertex[5].y - int(length_longer / sqrt(2));
    vertex[7].x = vertex[6].x;
    vertex[7].y = vertex[6].y - int(length_longer);

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window
    for (int i = 0; i < 8; ++i)
    {
        if (i == 7)
        {
            righttriangle a(length_longer, length_shorter, vertex[7]);
            a.addPosition(vertex[0], 'l');
            a.display(i+1);
        }
        else
        {
            righttriangle a(length_longer, length_shorter, vertex[i]);
            a.addPosition(vertex[i+1], 'l');
            a.display(i+1);
        }
    }    
    
    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
