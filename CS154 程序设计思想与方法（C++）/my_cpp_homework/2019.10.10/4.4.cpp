#include<iostream>

using namespace std;

int main(){
    int line_number,i,j;
    cout<<"���������ε�������1��11��һ��������:__\b\b";
    cin>>line_number;
    for (i=1;i<=line_number;++i){
        if (i<=line_number/2+1)
            {for (j=1;j<=line_number;++j){
                if (j>=line_number/2+2-i&&j<=line_number/2+i) cout<<'*' ;
                else cout<<' ';}}
        else {for (j=1;j<=line_number;++j){
                if (j>=i-line_number/2&&j<=(line_number*3)/2-i+1) cout<<'*' ;
                else cout<<' ';}}
        cout<<endl;
    }
}
