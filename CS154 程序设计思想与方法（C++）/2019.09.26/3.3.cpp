#include<iostream>

using namespace std;

int main(){
    double n,m;
    int sum,foot,chicken,rabbit;
    cout <<"������n�������õ���������,m���ȵ���������:_____\b\b\b\b\b";
    cin >> n >>m;
    sum=int (n);
    foot=int (m);
    rabbit=foot/2-sum;
    chicken=sum-rabbit;
    if (foot%2!=0||rabbit<0||chicken<0||n!=sum||m!=foot)
        cout <<"�޽�"<<endl;
    else cout <<"��:"<<chicken<<",��:"<<rabbit<<endl;

}
