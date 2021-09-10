#include <iostream>

using namespace std;

double m, n, p;

double func(double x)
{
    return (m*x*x + n*x + p);
}

int main()
{
    double a, b;
    double present;
    double division = 0.00001,standard = 0.000001; 
    cout << "Please input m,n,p of ax^2+bx+c"<< endl;
    cin >> m >> n >> p;
    cout << "Please input[a,b]"<< endl;
    cin >> a >> b;

    present = a;
    while(present <= b)
    {
        if(func(present) < standard && func(present) > -standard)
        {
            cout << present << endl;
            break;
        }
        else present += division;
    }
    if (present > b)
    cout << "No solution" << endl;

}