#include<iostream>
#include<cmath>

using namespace std;

double f(double x)
{return 1/(1+x);}
int main()
{
    double a,b;
    int n; //n为精度，即最终输出T[n-1][0]
    double parts = 0;
    double **T;

    cin >> a >> b >> n;
    T = new double*[n];
    for (int i = 0; i < n; ++i)
        T[i] = new double[n-i];
    T[0][0] = (b - a)*(f(a) + f(b)) / 2;
    for(int i = 1; i < n ;++i)
    {
        
        for (int j = 0; j < pow(2, i - 1) ; ++j)
            parts += f(a + (2 * j + 1)*(b - a) / pow(2, i));
        T[0][i] = T[0][i -1] / 2 + (b - a) / pow(2, i) * parts;
        parts = 0;
    }
    for (int i = 1; i < n; ++i)
    {
        for(int j = 0; j< n-i; ++j)
        T[i][j] = 1/ ((pow(4, i)) - 1) * ((pow(4, i)) * T[i-1][j+1] - T[i-1][j]);
    }
    cout << T[n-1][0] << endl;
    
    for (int i = 0; i < n; ++i)
        delete T[i];
    delete T;
    
    return 0;
}