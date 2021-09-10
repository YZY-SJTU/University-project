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
    void print()
    {
        if (isEmpty()) 
        {
            cout << "NULL";
            return ;
        }
        for (int i =0; i <=top_p; i++)
        cout << data[i];
    }
};

int main()
{
    seqStack a;
    char str[1000001];
    cin.getline(str,100000);
    for (int i = 0; str[i]!='\0'; ++i)
    {
        if (a.isEmpty())
        a.push(str[i]-'0');
        else 
        {
            if (a.top() == 1 && str[i]=='1')
            a.pop();
            else if (a.top() == 0 && str[i]=='0')
                {
                    a.pop();
                    if (!a.isEmpty() && a.top() == 1)
                    a.pop();
                    else a.push(1);
                }
            else a.push(str[i]-'0'); 
        }
    }
    a.print();
}