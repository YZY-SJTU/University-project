#include <iostream>
using namespace std;

class stack
{
private:
    struct node
    {
        char data;
        node *next;
        node(const char &x, node *n = NULL)
        { data = x; next = n;}
        node():next(NULL){}
        ~node(){}
    };

    node *top_p;   
public:
    stack();
    ~stack();
    bool isEmpty() const;
    void push(const char &x);
    char pop();
    char top() const;
    bool isMatch();
};

stack::stack()
{
    top_p = NULL;
}

stack::~stack()
{
    node *tmp;
        while (top_p != NULL)
        {
            tmp = top_p;
            top_p = top_p->next;
            delete tmp;
        }
}

bool stack::isEmpty() const
{
    return top_p == NULL;
}
void stack::push(const char &x)
{
    top_p = new node(x,top_p);
}

char stack::pop()
{
    if (isEmpty())
        return 'n';    
    node *tmp = top_p;
    char x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}

char stack::top() const
{
    if (isEmpty())
        return 'n'; 
    return top_p->data;
}

bool stack::isMatch()
{
    if (top_p == NULL)
    return true;
    node *tmp = top_p;
    stack order;
    while (tmp != NULL)
    {
        if (tmp->data == ')' ||tmp->data == ']' ||tmp->data == '}')
        {
            order.push(tmp->data);
            tmp = tmp->next;
            continue;
        }
        if (tmp->data == '(')
            if (order.top() == ')')
            {
                order.pop();
                tmp = tmp->next;
                continue;
            }
        if (tmp->data == '[')
            if (order.top() == ']')
            {
                order.pop();
                tmp = tmp->next;
                continue;
            }
        if (tmp->data == '{')
            if (order.top() == '}')
            {
                order.pop();
                tmp = tmp->next;
                continue;
            }
        return false;
    }
    return order.isEmpty();
}

int main()
{
    stack a;
    string data;
    char quote;
    int i,n,*number;
    cin >> n;
    number = new int[n];
    for (i=0; i<n; ++i)
        {
            cin >> number[i];
            if (number[i] == 1)
            cin >> quote;
            data += quote;
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
    return 0;
}