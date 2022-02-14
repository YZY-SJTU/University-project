#include<iostream>

using namespace std;

int main()
{
    int n,k;
    int i,j;
    const int MAXSIZE=1000;
    bool LightArray[MAXSIZE]={0};

    cout <<"Please input n(the number of light),k(the number of people):___\b\b\b";
    cin >> n >>k;
    for (i=1;i<=k;++i)
     { for (j=1;j<=n;++j)
        if (j%i==0) {LightArray[j-1]=(LightArray[j-1]+1)%2;}
     }
     for (i=0;i<n;++i){
        if (LightArray[i]) cout<<i+1<<' ';}

}
