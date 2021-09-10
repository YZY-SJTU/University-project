#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool compare(string &a, string &b)
{
    return (a+b) > (b+a);
}

void shellSort(vector<string> &a, int size)
{
    int step, i, j;
    string tmp;
    for (step= size/2; step>0;step/=2)
        for(i = step; i < size; ++i)
        {
            tmp = a[i];
            for(j = i - step; j>=0 && compare(tmp, a[j]); j-=step)
                a[j+step] = a[j];
            a[j+step] = tmp;
        }
}

int main()
{
    int n;
    int i;
    string tmp;
    cin >> n;
    vector<string> number(n,"");
    for (i = 0; i < n; ++i)
    cin >> number[i];
    shellSort(number, n);
    for (i = 0; i < n; ++i)
    cout << number[i];
    return 0;
}
