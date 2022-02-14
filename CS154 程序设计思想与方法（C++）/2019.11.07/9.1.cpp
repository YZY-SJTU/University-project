#include<iostream>

using namespace std;

int search (int *,int ,int );

int main(){
    int i,n,key;
    int *arr;

    cout<<"Please input n(1<=n<=20):";
    cin>>n;

    arr=new int[n];
    cout<<"Please input "<<n<<" integers:";
    for(i=0;i<n;++i)
       cin>>arr[i];

    cout<<"Please input key:";
    cin>>key;

    if (search(arr,n,key)==-1) cout<<"Not Found";
    else cout<<search(arr,n,key);

    delete [] arr;
    
    return 0; 
}

int search (int *arr,int n,int key)
{   int i;
    for(i=0;i<n;++i)
    { if(arr[i]==key) return i;}
    return -1;
}
