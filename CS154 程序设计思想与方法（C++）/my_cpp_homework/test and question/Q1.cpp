#include<iostream>
#include<cstring>

using namespace std;

void printInt (int num, int base);

int main(){
    int n,base;

    cout<<"Please input n,base(2<=base<=16):";
    cin>>n>>base;
    cout<<n<<"(10)=";
    printInt(n,base);
    cout<<'('<<base<<')';
}

void printInt (int num, int base)
{   int i,j,remain,digitnum,digitmax=0;
    long long int divisor=1;
    digitmax=16;
    for (i=digitmax;i>=1;--i)
    {   for (j=1;j<i;++j) {divisor*=base;}
        digitnum=num/divisor;
        switch (digitnum) {
            case 10: cout<<'A'; break;
            case 11: cout<<'B'; break;
            case 12: cout<<'C'; break;
            case 13: cout<<'D'; break;
            case 14: cout<<'E'; break;
            case 15: cout<<'F'; break;
            default: cout<<digitnum; break;
        }

        num-=digitnum*divisor;
        divisor=1;
    }

}
