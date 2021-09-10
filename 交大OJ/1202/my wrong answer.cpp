# include <iostream>

using namespace std;
class IntData
{
    friend ostream &operator<<(ostream &os, const IntData &x);
    friend istream &operator>>(istream &is, IntData &x);
    friend IntData operator+(IntData &a, IntData &b);

private:
    struct node
    {
        int digit;
        node *next;

        node(const int &x,node *n=NULL)
            {digit = x; next = n;}
        node():next(NULL){}
        ~node(){}
    };

    node *head;

public:
    IntData(){head = new node;}
    ~IntData(){clear(); delete head;}
    void clear();
    IntData &operator=(const IntData &x);
};

void IntData::clear()
{
    node *p=IntData::head->next,*q;
    head->next = NULL;
    while(p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
}

ostream &operator<<(ostream &os, const IntData &x)
{
    string s;
    IntData::node *p = x.head;
    while (p != NULL) 
    {
        s = char(p->digit + '0') + s;
        p = p->next;
    }
    os << s;
    return os;
}

istream &operator>>(istream &is, IntData &x)
{
    char num;
    x.clear();
    while((num=is.get()) != '\n')
    {
        (x.head)->next = new IntData::node(num-'0',(x.head)->next);
    }
    return is;
}

IntData operator+(IntData &a, IntData &b)
{
    IntData tmp;
    IntData::node *p = (a.head)->next, *q = (b.head)->next,*s = tmp.head;
    int carrier = 0,left,i;
    while(p != NULL && q != NULL)
    {
        left = (carrier + p->digit +q->digit)%10;
        carrier = (carrier + p->digit +q->digit)/10;
        s->next = new IntData::node(left, s->next);
        p = p->next;
        q = q->next;
        s = s->next;
    }
    while (p != NULL || q != NULL)
    {
        if (q == NULL)
        {
            carrier = (carrier + p->digit)/10;
            left = (carrier + p->digit)%10;
            s->next = new IntData::node(left, s->next);
            p = p->next;
            s = s->next;
        }
        else
        {
            carrier = (carrier +q->digit)/10;
            left = (carrier +q->digit)%10;
            s->next = new IntData::node(left, s->next);
            q = q->next;
            s = s->next;
        }
    }
    if (carrier != 0)
    {
        s->next = new IntData::node(1, s->next);
    }
    return tmp;
}

IntData &IntData::operator=(const IntData &x)
{
    if (&x == this) return *this;
    clear();
    node *p = head, *q = x.head;
    while( q->next != NULL)
    {
        p = p->next = new node(q->next->digit,NULL);
        q = q->next;
    }
    return *this;
}

int main()
{
    IntData a,b,c;
    cin >> a >> b;
    c = a + b;
    cout << c << endl;

    return 0;
}
