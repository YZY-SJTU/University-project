#include<iostream>

using namespace std;

int main(){
    int num,unit,decade,kilobit,myriabit;
    cout <<"������һ��5λ����:_____\b\b\b\b\b";
    cin >> num;
    unit=num%10;
    decade=num/10%10;
    kilobit=num/1000%10;
    myriabit=num/10000;
    if (unit==myriabit&&decade==kilobit)
        cout <<"Yes"<<endl;
    else
        cout <<"No"<<endl;


}
