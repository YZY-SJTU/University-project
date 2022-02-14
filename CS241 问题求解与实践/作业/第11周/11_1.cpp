#include <iostream>

using namespace std;

void quickSort(int a[], int size);
void quickSort(int a[], int low, int high);
int divide(int a[], int low, int high);
bool isContinue(int edge, int a[], int size);
int boat(int edge, int weight[], int size);

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

bool isContinue(int edge, int a[], int size)
{
    bool flag = true;
    bool out = false, error = false;
    for(int i=0; i<size; ++i)
    {
        if(a[i] <= 0)
        {
            error = true;
            flag = false;
        }
        if(a[i] > edge)
        {
            out = true;
            flag = false;
        }
    }
    if(error) cout << "error" << endl;
    else if(out) cout << "out" << endl;
    return flag;
}

int boat(int edge, int weight[], int size)
{
    int cnt = 0;
    int smallest = 0, largest = size - 1;
    while(smallest <= largest)
    {
        int tmp = edge - weight[smallest];
        if(weight[largest] > tmp)//单独坐一艘船
        {
            ++cnt;
            --largest;
        }
        else//双人坐船
        {
            ++cnt;
            --largest;
            ++smallest;
        }
        //若i=j时，不管怎样，操作完退出了循环
    }
    return cnt;
}

int main()
{
    int w, n;
    cin >> w >> n;
    int *weight;
    weight = new int[n];
    for(int i=0; i<n; ++i)
    cin >> weight[i];
    if(!isContinue(w, weight, n))
    {
        delete []weight;
        return 0;
    }

    quickSort(weight, n);
    cout << boat(w, weight, n) <<endl;
    delete []weight;
    return 0;
}