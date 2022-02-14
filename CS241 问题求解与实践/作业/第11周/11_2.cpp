#include <iostream>

using namespace std;

int *maxSum(int array[], int len);
int *readString(string str, int &len, int n);

int *maxSum(int array[], int len)
{
    int *index;
    index = new int[3];
    int *store;
    store = new int[len];
    store[0] = array[0];
    index[0] = store[0];
    index[1] = 1;
    index[2] = 1;

    for(int i=1; i<len; ++i)
    {
        if(store[i - 1] > 0)
            store[i] = store[i - 1] + array[i];
        else
            store[i] = array[i];
    }
    for(int i=1; i<len; ++i)
    {
        if(index[0] < store[i])
        {
            index[0] = store[i];
            index[2] = i + 1;
        }
    }
    int tmp = index[2] - 1;
    while(tmp >0 && store[tmp - 1] >= 0)
    --tmp;

    index[1] = tmp + 1;
    delete []store;
    return index;
}

int *readString(string str, int &len, int n)
{
    int num = 0;
    int flag = false;
    char token = '+';
    int i = 0;
    int *array;
    array = new int[n];
    len = 0;
    
    for(i=0; str[i]!='\0'; ++i)
    {
        if(str[i] == ' ')
        {
            if(!flag) continue;
            if(len < n)
            {
                if(token == '+')
                    array[len] = num;
                else array[len] = -num;
            }
            ++len;
            num = 0;
            flag = false;
            token = '+';
        }
        if(str[i] <='9' && str[i] >= '0')
        {
            
            num = num * 10 + int(str[i] - '0');
            flag = true;
            
        }
        if(str[i] == '-')
        token = '-';
    }
    if(str[i] == '\0')
    {
        if(flag)
        {
            if(len < n)
            {
                if(token == '+')
                array[len] = num;
                else array[len] = -num;
            }
            ++len;
            num = 0;
            flag = false;
            token = '+';
        }
    }
    return array;
}

int main()
{
    int n;
    cin >> n;
    if(n > 100000)
    {
        cout <<"error";
        return 0;
    }
    cin.get();
    int len;
    int *array;
    string str;
    getline(cin, str);
    array = readString(str, len, n);
    if(len != n)
    {
        cout <<"error";
        delete []array;
        return 0;
    }
    for(int i=0; i<n; ++i)
    {
        if(array[i] > 1000 || array[i] < -1000)
        {
            cout <<"error";
            delete []array;
            return 0;
        }
    }
    
    int *max = maxSum(array, n);
    cout << max[0] << " " << max[1] << " " << max[2];
    delete []array;
    delete []max;
    return 0;
}