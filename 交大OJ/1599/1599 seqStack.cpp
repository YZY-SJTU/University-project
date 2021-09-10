#include<iostream>

using namespace std;

class seqStack
{
private:
    char *data;
    int top_p;
    int maxSize;
    void doubleSpace()
    {
        char *tmp = data;
        data = new char[2 * maxSize];
        for (int i=0; i<maxSize; ++i)
        data[i] = tmp[i];
        maxSize *= 2;
        delete []tmp;
    }
public:
    seqStack(int initSize = 10)
    {
        data = new char[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    ~seqStack()
    {delete []data;}
    bool isEmpty() const
    {
        return top_p == -1;
    }
    void push(const char &x)
    {
        if (top_p == maxSize - 1) doubleSpace();
        data[++top_p] = x;
    }
    char pop()
    {
        if (isEmpty())
        return 'n';
        return data[top_p--];
    }
    char top() const
    {
        
        if (isEmpty())
        return 'n';
        return data[top_p];
    }
    bool isMatch()
    {
        if (top_p == -1)
        return true;
        seqStack order;
        for (int i=top_p; i>=0; --i)
        {
            if (data[i] == ')' ||data[i] == ']' ||data[i] == '}')
            {
                order.push(data[i]);
                continue;
            }
            if (data[i] == '(')
                if (order.top() == ')')
                {
                    order.pop();
                    continue;
                }
            if (data[i] == '[')
                if (order.top() == ']')
                {
                    order.pop();
                    continue;
                }
            if (data[i] == '{')
                if (order.top() == '}')
                {
                    order.pop();
                    continue;
                }
            return false;
        }
        return order.isEmpty();
    }
};

int main()
{
    seqStack a;
    char *data;
    int i,n,*number;
    cin >> n;
    number = new int[n];
    data = new char[n];
    for (i=0; i<n; ++i)
        {
            cin >> number[i];
            if (number[i] == 1)
            cin >> data[i];
        }
    for (i=0; i<n; ++i)
    {
        switch (number[i]){
            case 1:a.push(data[i]); break;
            case 2:a.pop(); break;
            case 3:
                if (a.top() == 'n') break;
                cout << a.top() <<endl; break;
            case 4:
                if (a.isMatch()) cout << "YES" <<endl;
                else cout << "NO" <<endl;
                break; 
        }
    }
    delete [] number;
    delete [] data;
    return 0;
}