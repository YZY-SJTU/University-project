#include <iostream>

using namespace std;

class seqList
{
private:
    int *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        int *tmp = data;
        maxSize *= 2;
        data = new int[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new int[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList()
    {
        delete[] data;
    }

    void clear()
    {
        currentLength = 0;
    }

    int length()
    {
        return currentLength;
    }

    void insert(const int &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++ currentLength;
    }

    bool IsIn(const int &x)
    {
        for (int i = 0; i <currentLength; i++)
        {
            if (data[i] == x)
            return true;
        }
        return false;
    }
};

int main()
{
    int n;
    long int *timeLine;
    int  *number,**From;
    int i, j, k;
    seqList a;
    cin >> n;
    timeLine = new long int[n];
    number = new int[n];
    From = new int*[n];
    for (i = 0; i < n; i++)
    {
        cin >> timeLine[i];
        cin >> number[i];
        From[i] = new int[number[i]];
        for (j = 0; j < number[i]; j++)
        cin >> From[i][j];
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (timeLine[i]-timeLine[j]<86400 && timeLine[i]>=timeLine[j])
            for (k = 0; k < number[j]; k++)
            {
                if (!a.IsIn(From[j][k]))
                a.insert(From[j][k]);
            } 
        }
        cout << a.length() << endl;
        a.clear();
    }
    for (i = 0; i < n; i++)
    delete From[i];
    delete []From;
    delete []timeLine;
    delete []number;
}