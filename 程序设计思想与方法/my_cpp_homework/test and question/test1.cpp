#include<iostream>

using namespace std;

int main(){
int n;
    int m=1;
    int *const p = &m;
    cout<<*p<<n;
    *p=20;
    cout<<*p<<n;
    delete p;
      cout<<p;
}
