#include<iostream>

using namespace std;

int main(){
    const int n=10;
    int i,j,sum1=1,sum2=0;
    for (i=1;i<=n;++i){
            sum1*=i;
            sum2+=sum1;}
    cout<<"n!(n从1到10）的求和="<<sum2<<endl;
}









