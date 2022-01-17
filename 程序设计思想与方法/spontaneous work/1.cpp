#include<iostream>

using namespace std;

int main()
{
    char str[20]={"987654"};
    cout<<str<<endl;
    cin.getline(str,19);
    cout<<str;
}
