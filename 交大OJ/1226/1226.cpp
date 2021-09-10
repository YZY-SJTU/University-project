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
    int k, tmp;
    int m1 = a[low];
    int m2 = a[(low+high)/2];
    int m3 = a[high];
    int flag1, flag2;
    if (m1 > m2) flag1 = true;
    else flag1 = false;
    if (m2 > m3) flag2 = true;
    else flag2 = false;
    if ((flag1 && flag2) || (!flag1 && !flag2)) 
    {
        k = m2;
        tmp = a[(low+high)/2];
        a[(low+high)/2] = a[low];
        a[low] = tmp;
    }
    else if (flag1 && !flag2) k = (m1 < m3)? m1 : m3;
    else k = (m1 > m3)? m1 : m3;

    if ( k == m3)
    {
        tmp = a[high];
        a[high] = a[low];
        a[low] = tmp;
    }
    do{
        while(low < high && a[high] >= k) --high;
        if (low < high) {a[low] = a[high]; ++low;}
        while(low < high && a[low] <= k) ++low;
        if (low < high) {a[high] = a[low]; --high;}
    }while(low != high);
    a[low] = k;
    return low;
}

void quickSort(int a[], int low, int high)
{
    int mid;
    if (low >= high) return;
    mid = divide(a, low, high);
    quickSort(a, low, mid - 1);
    quickSort(a, mid + 1, high);
}

int main()
{
    int n;
    int *num;
    cin >> n;
    num = new int[n];
    for (int i =0; i<n; ++i)
    cin >> num[i];
    quickSort(num, n);
    for (int i =0; i<n; ++i)
    cout << num[i] << " ";
}