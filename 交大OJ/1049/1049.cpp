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
    int size() const
    {
        return (top_p+1);
    }
};

int main()
{
    
    int t,*n,*m,**order;
    int i,j;
    cin >> t;
    n = new int[t];
    m = new int[t];
    order = new int*[t];
    for (i=0; i<t; ++i)
    {
        cin >> n[i] >> m[i];
        order[i] = new int[n[i]];
        for (j=0; j<n[i]; ++j)
            cin >> order[i][j];
    }
    
    for (i=0; i<t; ++i)
    {
        int index = 0, train = 0;
        seqStack seq; 
        while (index < n[i])
        {
            if(train == order[i][index])
            {
                train++;
                index++;
            }
            else if(!seq.isEmpty() && seq.top() == order[i][index])
            {
                seq.pop();
                index++;
            }
            else 
            {
                seq.push(train++);
                if(seq.size() > m[i])
                {
                    cout<<"NO"<<endl;
                    break;
                }
            }
        }
        if(index == n[i])
        cout<<"YES"<<endl;
    }
    
    for (i=0; i<t; ++i)
    delete []order[i];
    delete []order;
    delete []n;
    delete []m;

    return 0;
}