#include<iostream>

using namespace std;

int main(){
    int num,a,b,c;
    cout << "请输入一个三位整数:___\b\b\b";
    cin  >> num ;
    a=num/100;
    b=num/10%10;
    c=num%10;
    cout <<num<<"的百位数字是"<<a << ",十位数字是" <<b<<",个位数是"<<c<< endl;


}


