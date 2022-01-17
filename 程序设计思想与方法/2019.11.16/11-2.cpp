#include<iostream>
using namespace std;

struct clock
{
    int hour;
    int minute;
    int second;
};
void setTime(clock &p);
void increase(clock &p);
void showTime(clock &p);



int main()
{
    int i,n;
    clock now;
    setTime(now);
    cout << "Input the increase seconds:";
    cin >> n;
    for (i=0; i<n; ++i)
        increase(now);
    showTime(now);
}



void setTime(clock &p)
{
    while (true)
    {
        cout << "set the hour:";
        cin >> p.hour;
        if (0<=p.hour&&p.hour<=23) break;
        else cout <<"Error hour! Please set again"<<endl;
    }
    while (true)
    {
        cout << "set the minute:";
        cin >> p.minute;
        if (0<=p.minute&&p.minute<=59) break;
        else cout <<"Error minute! Please set again"<<endl;
    }
    while (true)
    {
        cout << "set the second:";
        cin >> p.second;
        if (0<=p.second&&p.second<=59) break;
        else cout <<"Error second! Please set again"<<endl;
    }
}

void increase(clock &p)
{
    if (p.second!=59) ++p.second;
    else if (p.minute!=59) {p.second=0;  ++p.minute;}
        else if(p.hour!=23) {p.second=0;  p.minute=0;  ++p.hour;}
            else {p.second=0;  p.minute=0;  p.hour = 0;}
}

void showTime(clock &p)
{
    cout << "The present time is:";
    if (p.hour<10) cout << '0' << p.hour;
    else cout << p.hour;
    cout << ':';
    if (p.minute<10) cout << '0' << p.minute;
    else cout << p.minute;
    cout << ':';
    if (p.second<10) cout << '0' << p.second;
    else cout << p.second;
}
