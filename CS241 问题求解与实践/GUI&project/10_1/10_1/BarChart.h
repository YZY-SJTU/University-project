//
#ifndef BARCHART_GUARD
#define BARCHART_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

class reference  //转化为多项式过程中记录系数
{
private:
    char* data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        char* tmp = data;
        maxSize *= 2;
        data = new char[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    reference(int initSize = 10)
    {
        data = new char[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~reference()
    {
        delete[] data;
    }

    void clear()
    {
        currentLength = 0;
    }

    int length()
    {
        return currentLength;
    }

    void input(const char& x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    double output()  //将字符串形式的数字转化为double数字
    {
        double x = 0, tmp = 0;
        bool flag = false;
        int i, length = 0;
        for (i = 0; i < currentLength; ++i)
            if (data[i] == '.')
            {
                ++i; length = currentLength - i; flag = true; break;
            }
            else x = x * 10 + int(data[i] - '0');
        for (i; i < currentLength; ++i)
            tmp = tmp * 10 + int(data[i] - '0');
        if (flag)
        {
            for (i = 0; i < length; ++i)
                tmp /= 10;
            x += tmp;
        }
        return x;
    }
};

class BarChart
{
public:
	BarChart(string &str1, string& str2);
	~BarChart(){}
	
	void display();

private:
	double AustinMonthlyAveTemp[12];
	double NewYorkMonthlyAveTemp[12];
    bool flag;

    void setMonthlyTemp(int No);
};

#endif // !BARCHART_GUARD