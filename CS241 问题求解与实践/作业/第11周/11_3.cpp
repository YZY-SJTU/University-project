#include <iostream>
#include <vector>

using namespace std;

string longestPalindromeSubseq(string str);

string longestPalindromeSubseq(string str)
{
    int n = str.length();
    vector<vector<string>> tmp(n, vector<string>(n));
    for(int j=0; j<n; ++j)
    {
        for(int i=j-1; i>=0; --i)
        {
            if(str[i] == str[j])
            {
                string temp;
                temp += str[i];
                temp += tmp[i+1][j-1];
                temp += str[i];
                tmp[i][j] = temp;
            }
            else
            {
                if(tmp[i+1][j].length() < tmp[i][j-1].length())
                tmp[i][j] = tmp[i][j-1];
                else
                tmp[i][j] = tmp[i+1][j];
            }
        }
    }
    return tmp[0][n-1];
}

int main()
{
    string str;
    getline(cin, str);
    cout << longestPalindromeSubseq(str) <<endl;
    return 0;
}