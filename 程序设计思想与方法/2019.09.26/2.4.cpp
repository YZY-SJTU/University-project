#include <iostream>

using namespace std;

int main(){
    int num,a,b,c,d;
    char a1,b1,c1,d1;
    cout << "������һ����λ����:___\b\b\b";
    cin >> num;
    a1=num/1000+13+64;
    b1=num/100%10+13+64;
    c1=num/10%10+13+64;
    d1=num%10+13+64;
    cout <<"�������:"<<a1 << b1 << c1 <<d1 << endl;
}
