#include<iostream>

using namespace std;

class Time
{
private:
    int hour;
    int minute;
    int second;
public:
        Time(int a=0,int b=0,int c=0):hour(a),minute(b),second(c){}
    void setTime();
    void showTime();

};

void Time::setTime()
{
    while (true)
    {
        cout << "set the hour:";
        cin >> hour;
        if (0<=hour&&hour<=23)
            break;
        else
            cout <<"Error hour! Please set again"<<endl;
    }
    while (true)
    {
        cout << "set the minute:";
        cin >> minute;
        if (0<=minute&&minute<=59)
            break;
        else
            cout <<"Error minute! Please set again"<<endl;
    }
    while (true)
    {
        cout << "set the second:";
        cin >> second;
        if (0<=second&&second<=59)
            break;
        else
            cout <<"Error second! Please set again"<<endl;
    }
}

void Time::showTime()
{
    cout << "The present time is:";
    if (hour<10)
        cout << '0' << hour;
    else
        cout << hour;
    cout << ':';
    if (minute<10)
        cout << '0' << minute;
    else
        cout << minute;
    cout << ':';
    if (second<10)
        cout << '0' << second;
    else
        cout << second;
}

int main()
{
    Time clock;
    clock.setTime();
    clock.showTime();

    return 0;
}


