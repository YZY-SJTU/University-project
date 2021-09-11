#include <iostream>
#include <vector>
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
    int n, m, index1, index2, cnt1 = 0, cnt2 = 0;
    int *num, *store;
    int i, j, tmp, maxIndex1, maxIndex2, number1, number2;
    bool flag = false;
    cin >> n;
    num = new int[n];
    store = new int[n];
    for(i=0; i<n; ++i)
    {
        cin >> num[i];
        store[i] = num[i];
    }
    quickSort(num, n);
    cin >> m;

    tmp = m - num[0];
    for(i=1; i<n; ++i)
        if (num[i] > tmp)
        {
            maxIndex1 = i - 1;
            break;
        }
    if (i == n) maxIndex1 = n - 1;
    maxIndex2 = maxIndex1 + 1;
    for(i=0; i<maxIndex1; ++i)
    {
        tmp = m - num[i];
        for(j=i+1; j<maxIndex2;++j)
        {
            if(tmp == num[j])
            {
                number1 = num[i];
                number2 = num[j];
                flag = true;
                break;
            }
            else if(tmp < num[j])
            {
                maxIndex2 = j;
                break;
            }
        }
        if (flag) 
        break;
    }
    
    if (flag)
    {
        vector<int> a, b;
        for (i=0; i<n; ++i)
        {
            if(store[i] == number1)
            {
                a.push_back(i);
                ++cnt1;
            }
        }
        for (i=0; i<n; ++i)
        {
            if(store[i] == number2)
            {
                ++cnt2;
                b.push_back(i);
            }
        }
        if(b[cnt2-1] - a[0] < a[cnt1-1] - b[0])
        {
            index1 = b[0];
            index2 = a[cnt1-1];
        }
        else if(b[cnt2-1] - a[0] > a[cnt1-1] - b[0])
        {
            index1 = a[0];
            index2 = b[cnt2-1];
        }
        else
        {
            if (a[0] < b[0])
            {
                index1 = a[0];
                index2 = b[cnt2-1];
            }
            else
            {
                index1 = b[0];
                index2 = a[cnt1-1];
            }
        }
        cout << index1 << " " << index2;
    }
    delete []store;
    delete []num;
    return 0;
}