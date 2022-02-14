#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    const int MAXSIZE = 80;
    int num1=0,num2=0,num3=0;
    ifstream infile;
    char x;
    char arr[MAXSIZE+1];
    cout << "Please input the name of the file:";
    cin.getline(arr,MAXSIZE);
    infile.open(arr,ifstream::in);
    if (!infile)
    {
    cout << "cannot open input file\n"; 
    return 1;
    }
    while (infile.get(x))
    {
        if (x<='9'&& x>='0')
        ++num1;
        else if ((x<='z'&& x>='a')||(x<='Z'&& x>='A'))
        ++num2;
        else ++num3;
    } 
    infile.close();
    cout << "The file has " << num1 <<" number, " << num2 << " letter and " << num3 << " others(including blank)" << endl;

    return 0;


}