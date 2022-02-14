#include<iostream>

using namespace std;

int main (){
    const int MAXSIZE=400,ORIGINALYEAR=1900;
    const int Runyear[12]={31,29,31,30,31,30,31,31,30,31,30,31},Pingyear[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i,j;
    int n,presentday=0,num[7]={0};
    bool YearArray[MAXSIZE];

    cout <<"Please input n(n is integer and n<=400):_\b";
    cin >>n;

    for (i=0;i<n;++i)
    { if (((ORIGINALYEAR+i)%4==0&&(ORIGINALYEAR+i)%100!=0)||(ORIGINALYEAR+i)%400==0)
        YearArray[i]=true;
        else YearArray[i]=false;}

    for (i=0;i<n;++i)
    {  if (YearArray[i])
        {for (j=0;j<12;++j)
            {  ++num[(presentday+12)%7];                               //(presentday+12)%7时，使周一为0；周二为1……
               presentday=(presentday+Runyear[j])%7;}
        }
        else for (j=0;j<12;++j)
            { ++num[(presentday+12)%7];
              presentday=(presentday+Pingyear[j])%7;}
    }

    for (i=0;i<7;++i)
        cout <<num[i]<<' ';

}


