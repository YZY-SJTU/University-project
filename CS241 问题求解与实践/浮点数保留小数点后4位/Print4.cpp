#include <iostream>
#include <iomanip>

using namespace std;

void print4(double x)
{
    string a;
    a = std::to_string(x);
    int i = 0,cnt = 0;
    bool flag = false;
    while(cnt < 4 && a[i] !='\0')
    {
        if(flag) ++cnt;
        if(a[i] == '.')
        flag = true;
        cout << a[i];
        ++i;
    }
}