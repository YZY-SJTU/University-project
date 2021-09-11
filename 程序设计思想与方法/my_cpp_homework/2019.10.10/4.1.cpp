#include<iostream>
#include<cmath>

using namespace std;

int main(){
    int i,j,a,n;
    long num,Sum=0;
    cout<<"Input a,n:___\b\b\b";
    cin>>a>>n;
    for (i=0;i<n;++i)
    {num=0;
        for (j=0;j<=i;++j)
        num+=a*pow(10,j);
    Sum+=num;
    }
    cout<<"Sum="<<Sum<<endl;
}

