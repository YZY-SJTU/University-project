#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool compare(string &a, string &b)
{
    return (a+b) > (b+a);
}

void bubbleSort(vector<string> &a, int size)
{
    int i, j;
    string tmp;
    bool flag = true;

    for (i = 1; i < size - i; ++j)
    {
        flag = false;
        for (j = 0; j < size - i; ++j)
        if (compare(a[j+1], a[j]))
        {
            tmp = a[j];
            a[j] = a[j+1];
            a[j+1] = tmp;
            flag = true;
        }
        if (!flag) break;
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
    bubbleSort(number, n);
    for (i = 0; i < n; ++i)
    cout << number[i];
    return 0;
}
