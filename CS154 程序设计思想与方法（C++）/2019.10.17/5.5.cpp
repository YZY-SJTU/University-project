#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main (){
    int i;
    int num1,num2,sum,totalnum,Array[11]={0};
    bool flag=false;
    cout <<"Please input number:_\b";
    cin>>totalnum;
    srand(time(NULL));
    for (i=0;i<totalnum;++i)
    {num1=(rand()%6)+1;
     num2=(rand()%6)+1;
     sum=num1+num2;
     Array[sum-2]+=1;}

    for (i=0;i<11;++i)
    {   if (Array[5]<Array[i])
            flag=true;}

    //����б�
    cout<<"��:     ";
    for(i=0;i<11;++i)
        cout <<i+2<<'\t';
    cout<<endl<<"����:   ";
    for (i=0;i<11;++i)
        cout<<Array[i]<<'\t';

    if (flag) cout<<endl<<"����֮�Ͳ�����";
    else cout<<endl<<"����֮�ͺ���";




}
