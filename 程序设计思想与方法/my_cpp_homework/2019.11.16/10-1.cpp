#include<iostream>

using namespace std;

int minlen( char *str[], int n);

const int MAXSIZE=100;

int main()
{

    int n,i;
    cout << "Please input the number of strings:_\b";
    cin >> n;  cin.get();
    char **str;
    str = new char *[n];
    for (i=0; i<n; ++i)
    {
        str[i] = new char[MAXSIZE];
        cin.getline(str[i],MAXSIZE);
    }
    cout << minlen(str,  n);
    for (i=0; i<n; ++i)
        delete [] str[i];
    delete [] str;

}

int minlen( char *str[], int n)
{
    int i,maxnum=MAXSIZE,cnt=0;
    char j;
    for (i=0; i<n; ++i)
    {
        for (j=0; str[i][j]!='\0'; ++j)
        {
            ++cnt;
        }
        if (maxnum>cnt) maxnum=cnt;
        cnt=0;
    }
    return maxnum;
}
