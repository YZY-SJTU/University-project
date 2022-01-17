#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream no1,no2;
    const int MAXSIZE = 80;
    int cnt1=1,cnt2=1;
    char x,y;
    char arr1[MAXSIZE+1],arr2[MAXSIZE+1];
    cout << "Please input the name of the file1:";
    cin.getline(arr1,MAXSIZE);
    cout << "Please input the name of the file2:";
    cin.getline(arr2,MAXSIZE);
    no1.open(arr1,ifstream::in);
    no2.open(arr2,ifstream::in);
    if (!no1)
    {
    cout << "cannot open input file1\n"; 
    return 1;
    }
    if (!no2)
    {
    cout << "cannot open input file2\n"; 
    return 1;
    }
    while (true)
    {
        no1.get(x);
        no2.get(y);
        if (no1.eof() && no2.eof())
        {
            cout << "Two files are equal" << endl;
            break;
        }
        if (x==y) 
        {
            if (x=='\n')
            {
                ++cnt1;
                cnt2=1;
            }
            else 
            ++cnt2;
        }
        else 
        {
            cout << "The first difference is in row " << cnt1 << ",column " << cnt2 << endl;
            break;
        }

    }
    no1.close();
    no2.close();

    return 0;
}