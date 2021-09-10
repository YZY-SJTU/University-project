#include<iostream>

using namespace std;

class seqStack
{
private:
    int *data;
    int top_p;
    int maxSize;
    void doubleSpace()
    {
        int *tmp = data;
        data = new int[2 * maxSize];
        for (int i=0; i<maxSize; ++i)
        data[i] = tmp[i];
        maxSize *= 2;
        delete []tmp;
    }
public:
    seqStack(int initSize = 10)
    {
        data = new int[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    ~seqStack()
    {delete []data;}
    bool isEmpty() const
    {
        return top_p == -1;
    }
    void push(const int &x)
    {
        if (top_p == maxSize - 1) doubleSpace();
        data[++top_p] = x;
    }
    int pop()
    {
        return data[top_p--];
    }
    int top() const
    {
        return data[top_p];
    }
};

int main()
{
    seqStack a;
    int n,*op,*num;
    cin >> n;
    op = new int[n];
    num = new int[n];
    for (int i=0; i<n; ++i)
    {
        cin >> op[i] >>num[i];
    }

    for (int i=0; i<n; ++i)
    {
        if (op[i] == 1)
            {
                a.push(num[i]);
                cout << "OK" <<endl;
            }
        else if (op[i] == 2)
            {
                if (a.isEmpty())
                    cout << "ERROR" << endl;
                else
                {
                    if (a.pop() == num[i])
                        cout << "YES" << endl;
                    else cout << "NO" << endl;
                }
            }

    }
}
