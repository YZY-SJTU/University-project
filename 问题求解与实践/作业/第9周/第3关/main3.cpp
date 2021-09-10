
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Binary_tree.h"
#include "TriangleBinary_tree.h"
//------------------------------------------------------------------------------

//������ȷ��VS2019������fltk��󣬲�����������ĳ���һ������
//�������ڱ�������ʱ����������ٴ���window��ͼ��ͱ�Ϊ���ˣ����Խ�ͼ��Ϊ�����ڳ����ж�ֵ��Ľ��
//ϣ����������ʱ�佲һ����ָ���ҵĴ���������
//����㣨300��10������ʼdx = 100, dy = 70 
//ͼһΪ����Բ�ν����������
//ͼ��Ϊ���������ν����������

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
