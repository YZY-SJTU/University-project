#include<iostream>
#include<cstring>

using namespace std;

void printInt (int , int );

int main(){
    int n,base;

    cout<<"Please input n,base(2<=base<=16):";
    cin>>n>>base;
    cout<<n<<"(10)=";
    printInt(n,base);
    cout<<'('<<base<<')';
}

void printInt (int n, int base)
{   int i,j,remain,digitNum,digitmax=0,divisor=1;

    remain=n;
	while (remain!=0)
	{	remain/=base;
		++digitmax;}

    for (i=digitmax;i>=1;--i)
    {   for (j=1;j<i;++j) {divisor*=base;}
        digitNum=n/divisor;

        switch (digitNum) {
            case 10: cout<<'A'; break;
            case 11: cout<<'B'; break;
            case 12: cout<<'C'; break;
            case 13: cout<<'D'; break;
            case 14: cout<<'E'; break;
            case 15: cout<<'F'; break;
            default: cout<<digitNum; break;
        }

        n-=digitNum*divisor;
        divisor=1;
    }

}
