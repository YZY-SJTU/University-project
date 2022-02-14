#include<iostream>

using namespace std;

int main(){
    double n,m;
    int sum,foot,chicken,rabbit;
    cout <<"请输入n（鸡与兔的总数量）,m（腿的总数量）:_____\b\b\b\b\b";
    cin >> n >>m;
    sum=int (n);
    foot=int (m);
    rabbit=foot/2-sum;
    chicken=sum-rabbit;
    if (foot%2!=0||rabbit<0||chicken<0||n!=sum||m!=foot)
        cout <<"无解"<<endl;
    else cout <<"鸡:"<<chicken<<",兔:"<<rabbit<<endl;

}
