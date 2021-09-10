#include <iostream>
using namespace std;

int main()
{
    int n, cnt = 0, *number;
    int i, j;
    cin >> n;
    number = new int[n];
    for (i = 0;i < n; ++i)
        cin >>number[i];
    for (i = 0 ; i < n; ++i)
    {
        for (j = 0; j < i; ++j)
            if (number[i] < number[j])
                ++cnt;
    }
    cout << cnt;
    return 0;
}