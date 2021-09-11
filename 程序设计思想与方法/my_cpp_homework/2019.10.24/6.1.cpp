#include<iostream>

using namespace std;
int main(){
    const int MAXSIZE=80;
    int i,num=0;
    char ch1[MAXSIZE+1];

    cout<<"Please input a string(<=80):";
    cin.getline(ch1,MAXSIZE+1);
    for (i=0;i<MAXSIZE+1;++i)
    ch1[i] = tolower(ch1[i]);
    for (i=0;ch1[i]!='\0';++i)
    {if(ch1[i]=='a'||ch1[i]=='e'||ch1[i]=='i'||ch1[i]=='o'||ch1[i]=='u')
        ++num;}
    cout<<"Count="<<num<<endl;

}
