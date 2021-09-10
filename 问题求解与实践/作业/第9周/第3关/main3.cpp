
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Binary_tree.h"
#include "TriangleBinary_tree.h"
//------------------------------------------------------------------------------

//在我正确向VS2019载入了fltk库后，不附带流输入的程序一切正常
//但是我在本地运行时进入输入后再创建window，图像就变为空了，所以截图均为变量在程序中定值后的结果
//希望助教能有时间讲一讲，指出我的错误在哪里
//根结点（300，10），初始dx = 100, dy = 70 
//图一为六层圆形结点满二叉树
//图二为六层三角形结点满二叉树

bool exercise1 = true;
int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    
    int x = 300, y = 10, N=6;
    int dx = 100, dy = 70;
    
    std::cout << "Please input the level of the tree" << endl;
    std::cin  >> N;

    Point tl(100,100);           // to become top left  corner of window
    Simple_window win(tl,600,400,"Canvas");    // make a simple window Point root;
    Point root;
    root.x = x;
    root.y = y;
    if (exercise1)
    {
        Binary_tree a(N, root, dx, dy);
        a.display();
    }
    else
    {
        TriangleBinary_tree a(N, root, dx, dy);
        a.display();
    }
    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
