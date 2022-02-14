#include<iostream>

using namespace std;

void hanoi(int n,char start,char finish,char temp);

int main (){
    int n;
    cin>>n;
    hanoi(n,'A','B','C');
    return 0;

}

void hanoi(int n,char start,char finish,char temp)
{if (n==1) cout<<start<<"->"<<finish<<'\t';
    else {
        hanoi(n-1,start,temp,finish);
        cout<<start<<"->"<<finish<<'\t';
        hanoi(n-1,temp,finish,start);
    }

}
