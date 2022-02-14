#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    char x;
    int cnt=1;
    ifstream infile("hello.cpp",ifstream::in);
    if (!infile)
    cout << "cannot open input file\n"; 
    cout << cnt << " //Print\"Hello Everyone!\""<< endl;
    ++cnt;
    cout << cnt << ' ';
    while (infile.get(x))
    {
        cout << x;
        if (x=='\n')
        {
            ++cnt;
            cout << cnt << ' ';
        }
    }
    infile.close();

    return 0;
}