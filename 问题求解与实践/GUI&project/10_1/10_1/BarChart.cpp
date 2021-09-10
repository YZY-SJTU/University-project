//
#include "BarChart.h"



void BarChart::setMonthlyTemp(int No)
{
    ifstream in;
    if (No == 1)
    {
        in.open("Austin.csv");
        if (!in)
        {
            bool flag = false;
            cerr << "error" << endl;
            return;
        }
    }
    else
    {
        in.open("NewYork.csv");
        if (!in)
        {
            bool flag = false;
            cerr << "error" << endl;
            return;
        }
    }

    char ch;
    reference tmp1; //记录数据的月份
    reference tmp2;//记录温度
    int Month = 0;//对应月份为i-1
    int DaySum = 0;//该月日期数
    int cnt = 0;//找出这一列对应的月份
    bool isDate = true;//日期部分
    char Token = '+';//温度的正负

    while ((ch = in.get()) != '\n');
    while ((ch = in.get()) != EOF)
    {
        if (!(ch >= '0' && ch <= '9') && ch != '/' && ch != '\n' && ch != ',' && ch != '.' && ch != '-')
            continue;
        if (ch == '\n')
        {
            isDate = true;
            cnt = 0;
            Token = '+';
            tmp1.clear();
            tmp2.clear();
            continue;
        }
        if (isDate)
        {
            if (ch == ',')
            {
                if (int(tmp1.output()) != Month + 1)
                {
                    if (No == 1)
                        AustinMonthlyAveTemp[Month] /= DaySum;
                    else
                        NewYorkMonthlyAveTemp[Month] /= DaySum;
                    ++Month;

                    DaySum = 0;

                }
                isDate = false;
                ++DaySum;
                continue;
            }
            if (ch == '/')
            {
                ++cnt;
                continue;
            }
            if (ch >= '0' && ch <= '9')
            {
                if (cnt != 1)
                    continue;
                else
                    tmp1.input(ch);
            }
        }
        else
        {
            if (ch == '-')
                Token = '-';
            if ((ch >= '0' && ch <= '9') || ch == '.')
                tmp2.input(ch);
            if (ch == ',')
            {
                if (No == 1)
                {
                    if (Token == '+')
                        AustinMonthlyAveTemp[Month] += tmp2.output();
                    else
                        AustinMonthlyAveTemp[Month] -= tmp2.output();
                }
                else
                {
                    if (Token == '+')
                        NewYorkMonthlyAveTemp[Month] += tmp2.output();
                    else
                        NewYorkMonthlyAveTemp[Month] -= tmp2.output();
                }
            }
        }
    }

    if (ch == EOF)
    {
        if (No == 1)
            AustinMonthlyAveTemp[11] /= DaySum;
        else
            NewYorkMonthlyAveTemp[11] /= DaySum;
    }

    in.close();
}

BarChart::BarChart(string& str1, string& str2)
{
    for (int i = 0; i < 12; ++i)
    {
        AustinMonthlyAveTemp[i] = 0;
        NewYorkMonthlyAveTemp[i] = 0;

    }
    setMonthlyTemp(1);
    setMonthlyTemp(2);
    cout << "Austin:" << endl;
    for (int i = 0; i < 12; ++i)
        cout << " Month" << i + 1 << "'s Temp = " << AustinMonthlyAveTemp[i] << " degree" << endl;
    cout << "NewYork:" << endl;
    for (int i = 0; i < 12; ++i)
        cout << " Month" << i + 1 << "'s Temp = " << NewYorkMonthlyAveTemp[i] << " degree" << endl;
}

void BarChart::display()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    Point tl(100, 100);           // to become top left  corner of window
    Simple_window win(tl, 600, 400, "BarChart");    // make a simple window

    Axis xa(Axis::x, Point(60, 350), 420, 14, "");
    xa.set_color(Color::black);
    xa.draw();
    Axis ya(Axis::y, Point(60, 350), 280, 7, "Temperature(centigrade)");
    ya.set_color(Color::black); // choose a color for the axis
    ya.label.set_color(Color::black); // choose a color for the text
    ya.draw();

    Point xLabel(75, 370);
    for (int i = 1; i < 10; ++i)
    {
        xLabel.x += 30;
        string tmp1;
        tmp1 += i + '0';
        Text tmp2(xLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    xLabel.x -= 10;
    for (int i = 0; i <= 2; ++i)
    {
        xLabel.x += 30;
        string tmp1;
        tmp1 += '1';
        tmp1 += i + '0';
        Text tmp2(xLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    {
        xLabel.x += 70;
        xLabel.y -= 20;
        string tmp1 = "Month";
        Text tmp2(xLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }

    Point yLabel(40, 350);
    {
        string tmp1 = "0";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }

    {
        yLabel.y -= 40;
        string tmp1 = "5";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    {
        yLabel.y -= 40;
        string tmp1 = "10";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    {
        yLabel.y -= 40;
        string tmp1 = "15";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    {
        yLabel.y -= 40;
        string tmp1 = "20";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }
    {
        yLabel.y -= 40;
        string tmp1 = "25";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    } {
        yLabel.y -= 40;
        string tmp1 = "30";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    } {
        yLabel.y -= 40;
        string tmp1 = "35";
        Text tmp2(yLabel, tmp1);
        tmp2.set_color(Color::black);
        tmp2.draw();
    }

    Graph_lib::Polygon a;
    a.add(Point(480, 70));
    a.add(Point(500, 70));
    a.add(Point(500, 80));
    a.add(Point(480, 80));
    a.set_fill_color(Color::blue);
    a.draw();

    Text a1(Point(510, 85), "Austin");
    a1.set_color(Color::black);
    a1.draw();

    Graph_lib::Polygon b;
    b.add(Point(480, 55));
    b.add(Point(500, 55));
    b.add(Point(500, 65));
    b.add(Point(480, 65));
    b.set_fill_color(Color::yellow);
    b.draw();

    Text b1(Point(510, 65), "NewYork");
    b1.set_color(Color::black);
    b1.draw();

    Point leftDown(90, 350);
    Point rightDown(120, 350);
    Point leftUp(90, 350);
    Point rightUp(120, 350);
    for (int i = 0; i < 12; ++i)
    {
        double length = AustinMonthlyAveTemp[i] * 280 / 35;
        leftUp.y -= length;
        rightUp.y -= length;
        Graph_lib::Polygon Poly1;
        Poly1.add(leftDown);
        Poly1.add(rightDown);
        Poly1.add(rightUp);
        Poly1.add(leftUp);
        Poly1.set_color(Color::black);
        Poly1.set_fill_color(Color::blue);
        Poly1.draw();

        leftUp.y = 350;
        rightUp.y = 350;

        length = NewYorkMonthlyAveTemp[i] * 280 / 35;
        leftUp.y -= length;
        rightUp.y -= length;
        Graph_lib::Polygon Poly2;
        Poly2.add(leftDown);
        Poly2.add(rightDown);
        Poly2.add(rightUp);
        Poly2.add(leftUp);
        Poly2.set_color(Color::black);
        Poly2.set_fill_color(Color::yellow);
        Poly2.draw();

        leftUp.y = 350;
        rightUp.y = 350;
        leftUp.x += 30;
        rightUp.x += 30;
        leftDown.x += 30;
        rightDown.x += 30;
    }

    win.wait_for_button();
}