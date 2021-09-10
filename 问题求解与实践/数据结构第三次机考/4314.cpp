#include <iostream>
using namespace std;

void quickSort(int a[], int size);
void quickSort(int a[], int low, int high);
int divide(int a[], int low, int high);

void quickSort(int a[], int size)
{
    quickSort(a, 0, size - 1);
}

int divide(int a[], int low, int high)
{
    int k = a[low];
    do
    {
        while (low < high && a[high] >= k)
            --high;
        if (low < high)
        {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <= k)
            ++low;
        if (low < high)
        {
            a[high] = a[low];
            --high;
        }
    } while (low != high);
    a[low] = k;
    return low;
}

void quickSort(int a[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = divide(a, low, high);
    quickSort(a, low, mid - 1);
    quickSort(a, mid + 1, high);
}

int main()
{
    int n, cnt = 0, *number, *tmp;
    int i, j, k, refer, index;
    cin >> n;
    number = new int[n];
    tmp = new int[n];
    for (i = 0; i < n; ++i)
    {
        cin >> number[i];
        tmp[i] = number[i];
    }
    quickSort(tmp, n);
    for (i = 0; i < n; ++i)
    {
        refer = tmp[i];
        for (j = 0; j < n; ++j)
            if (number[j] == refer)
                index = j;
        for (j = 0; j < index; ++j)
            if (number[j] > refer)
                ++cnt;
    }
    cout << cnt;
    
    delete []number;
    delete []tmp;
    return 0;
}