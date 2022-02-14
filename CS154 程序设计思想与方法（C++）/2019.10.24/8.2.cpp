#include<iostream>

using namespace std;

bool perfectNumber(int);

int main(){
    int i,m,n;
    bool flag=false;

    cout<<"Please input m,n(1<=m<=n<=10000):";
    cin>>m>>n;
    cout<<"Perfect number in ["<<m<<','<<n<<"]:";
    for (i=m;i<=n;++i)
    {   if (perfectNumber(i)) {flag=true; cout<<i<<' ';} }
    if (!flag) cout<<"Not Found"<<endl;
}

bool perfectNumber(int n)
{   bool flag;
    int i,sum=0;

    if (n==1) {flag=false; return (flag);}
    else for (i=1;i<n;++i)
        {if (n%i==0) sum+=i;}

    if (sum==n) flag=true;
    else flag=false;

    return (flag);

}
