#include<iostream>

using namespace std;

int main(){
    double rate1=1.5,rate2=2,total,num;
    cout <<"����������ˮ�������֣�:___\b\b\b";
    cin >> num;
    if (num<=10)
        total=rate1*num;
    else
        total=rate1*10+rate2*(num-10);
    cout <<"ˮ�ѣ�Ԫ��:"<<total<<endl;
}
