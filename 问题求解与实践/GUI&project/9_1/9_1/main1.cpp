
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "hyperelliptic.h"



//*****************************************************************************//
//�����ĳ���Ӧ����ˣ��������ڱ���ʱ������ٴ�����ͼ���Ϊ���ˣ����Խ�ͼΪ�����ڳ����ж�ֵ��Ľ��
//ϣ�������ܽ�һ�������ļ�����canvas�ϣ�ָ���ҵĴ���������
//��ͼΪa = 200, b = 150, m =2, n = 1.8, N =10��������
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