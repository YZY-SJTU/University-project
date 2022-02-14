#include<iostream>
#include<cstring>

using namespace std;

int main (){
    const int MAXSIZE=80;
    int place=-1,i;
    char character,ch1[MAXSIZE+1];
    cout<<"Please input a string(<=80):";
    cin.getline(ch1,MAXSIZE+1);
    cout<<"Please input a character:";
    cin>>character;
    for (i=0;ch1[i]!='\0';++i)
    {if (ch1[i]==character) place=i;}
    if (place==-1) cout<<"Not Found"<<endl;
    else cout <<"Index(address of first char is 0)="<< place<<endl;

}
