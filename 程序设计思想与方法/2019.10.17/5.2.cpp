#include<iostream>
using namespace std;

int main(){
    const int MAXSIZE=100;
    int i,j,k,l;
    int m,n,Array[MAXSIZE][MAXSIZE];
    bool flag1,flag2;

    cout <<"Please input m,n:___\b\b\b";
    cin >>m>>n;
    cout <<"Please input Array:\n";
    flag2=true;
    for (i=0;i<m;++i)
    {   for (j=0;j<n;++j)
        cin >>Array[i][j];}
    for (i=0;i<m;++i)
    {   for (j=0;j<n;++j)
        {   flag1=true;
            for (k=0;k<n;++k)
            {if (Array[i][j]<Array[i][k])
                {flag1=false; break;}
            }
            for (l=0;l<m;++l)
            {   if (Array[i][j]>Array[l][j])
                {flag1=false; break;}
            }
                if (flag1)
                    {cout<<"mat["<<i<<"]["<<j<<"]="<<Array[i][j]<<endl;
                     flag2=false;}
        }
    }
    if (flag2) cout << "Not Found"<<endl;

}
