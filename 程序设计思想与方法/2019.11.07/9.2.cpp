#include<iostream>

using namespace std;


int main(){
    int i,n,num=1,remain,LastCode;
    int *arr;

    cout<<"Please input n:";
    cin>>n;

    remain=n;
    arr=new int [n];
    for (i=0;i<n;++i)
        arr[i]=i;

    while (remain!=1)
    {   for (i=0;i<n;++i)
        {   if (arr[i]==-1) continue;
            else if (num==0) {arr[i]=-1; --remain; num=(num+1)%3;}
                else num=(num+1)%3;
        }
    }

    for (i=0;i<n;++i)
    {   if (arr[i]!=-1) LastCode=i+1;}

    delete [] arr;

    cout<<"Last code:"<<LastCode;
	
	return 0; 
}



