#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int n, **mountain, cnt, row, column, i, j;
    
    cin >> n;
    mountain = new int *[n];
    for (i = 0; i < n; ++i)
    {
        mountain[i] = new int[n];
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            mountain[i][j] = 0;
        }
    }

    row = column =  0;
    cnt = 1;

    while (cnt <= n * n)
    {
        while (cnt <= n * n) //从左向右
        {
            mountain[row][column] = cnt++;
            if (column == n - 1|| mountain[row][column + 1] != 0)
                {
                    ++row;
                    break;
                }
            ++column;
        }
        while (cnt <= n * n) //从上往下
        {
            mountain[row][column] = cnt++;
            if (row == n - 1|| mountain[row + 1][column] != 0)
                {
                    --column;
                    break;
                }
            ++row;
        }
        while (cnt <= n * n) //从右往左
        {
            mountain[row][column] = cnt++;
            if (column == 0 || mountain[row][column - 1] != 0)
                {
                    --row;
                    break;
                }
            --column;
        }
        while (cnt <= n * n) //从下往上
        {
            mountain[row][column] = cnt++;
            if (row == 0 || mountain[row - 1][column] != 0)
                {
                    ++column;
                    break;
                }
            --row;
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        cout << setw(6) << mountain[i][j];
        cout << endl;
    }
    
    for (i = 0; i < n; ++i)
        delete [] mountain[i];
    delete [] mountain;

    return 0;
}