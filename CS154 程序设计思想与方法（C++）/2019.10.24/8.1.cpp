#include<iostream>

using namespace std;

bool isPrime(int );

int main() {
    int m,n,i,count1=0;
    cout<<"Please input m,n(1<=m<=n<=100):";
    cin>>m>>n;
    for (i=m;i<=n;++i)
    {
        if (isPrime(i))
        ++count1;
    }
    cout<<"Count="<<count1<<endl;
}

bool isPrime(int n)
{
    int i;
    bool flag=false;
    if (n==1) flag=false;
    else if (n==2) flag=true;
        else for (i=2;i<n;++i)
            {   if (n%i==0)  {flag=false; break;}
                else flag=true;
            }
    return (flag);
}
