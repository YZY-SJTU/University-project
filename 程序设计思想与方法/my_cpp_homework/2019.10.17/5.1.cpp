#include<iostream>

using namespace std;

int main(){
    bool flag;
    const int MAXSIZE=100;
    int i,j,tmp;
    int n,Sort[MAXSIZE];
    cout <<"Please input n:_\b";
    cin >>n;
    cout <<"Please input "<<n<<" integers:_____________\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

    for (i=0;i<n;++i)
        cin >>Sort[i];

for (i=1;i<n;++i)
    {   flag=false;
        for(j=0;j<n-i;++j)
            if (Sort[j]<Sort[j+1])
            {tmp=Sort[j]; Sort[j]=Sort[j+1]; Sort[j+1]=tmp; flag=true;}
        if (!flag) break;
    }

    cout <<endl;
    for (i=0;i<n;++i)
        cout<<Sort[i]<<' ';

    return 0;
}
