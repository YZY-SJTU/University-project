#include<iostream>

using namespace std;

int k(char *);

int main(int argc,char *argv[10,30,50,20,40])
{
    int sum=0;

    cout<<"argc="<<argc<<endl;
    for (int i=0;i<argc;++i)
        sum+=k(argv[i]);
    cout<<sum/(argc-1)<<endl;

    return 0;

}

int k(char *s)
{
    int num=0;

    while(*s) {num=num * 10+ *s - '0'; ++s;}

    return num;
}
