#include<iostream>

using namespace std;

int max(int arr[], int size);
int SearchMax(int arr[], int LeftHand, int RightHand);

int main()
{   int i,n,*arr;

    cout << "Please input n(length of int array):";
    cin >> n;

    arr=new int [n];
    cout << "Please input "<< n<< " integer:";
    for (i=0; i<n; ++i)
        cin >> arr[i];

    cout << "The max number of array is:"<< max(arr, n);
}

int max(int arr[], int size)           //������ֵ�ĺ���
{
     return SearchMax(arr, 0, size-1);       //�����0��n-1���ֵ�ĺ���
}

int SearchMax(int arr[], int LeftHand, int RightHand)      //�����LeftHand��RightHand���ֵ�ĺ���
{   int mid;

    if (LeftHand==RightHand) return arr[LeftHand];
    if (RightHand==LeftHand + 1) return ((arr[LeftHand]>=arr[RightHand]) ? arr[LeftHand] : arr[RightHand]);
    mid = (LeftHand + RightHand) / 2;
    return((SearchMax(arr, 0, mid) >= SearchMax(arr, mid, RightHand)) ?  SearchMax(arr, 0, mid) :  SearchMax(arr, mid, RightHand));
}
