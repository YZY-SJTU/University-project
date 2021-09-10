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
    int N, pre, cnt;
    int *A;
    cin >> N;
    A = new int[N];
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    quickSort(A, N);
    pre = A[0];
    cnt = 1;
    for (int i = 1; i < N; ++i)
    {
        if (pre == A[i]) continue;
        else
        {
            cnt++;
            pre = A[i];
        }
    }
    cout << cnt;
}