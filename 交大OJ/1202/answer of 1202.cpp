#include <iostream>
using namespace std;

class BigData {
    friend ostream &operator<<(ostream &os, const BigData &x);
    friend istream &operator>>(istream &is, BigData &x);
    friend BigData operator+(BigData a, BigData b);
private:
    struct node {
        int data;
        node *next;

        node(const short &x, node *n = NULL) {
            data = x;
            next = n;
        }
    };

    node *num;
    void clear();

public:
    BigData(node *p = NULL) 
    {
        if (p == NULL) 
            num = new node(0);
        else 
            num = p;
    }

    BigData(const BigData &x)
    {
        num = new node(x.num->data);
        node *p = num, *q = x.num;
        while (q->next != NULL) 
        {
            q = q->next;
            p->next = new node(q->data);
            p = p->next;
        }
    }

    ~BigData() 
    {clear();}

    BigData &operator=(const BigData &);
};

void BigData::clear() 
{
    node *p = num, *q;
    while (p != NULL) 
    {
        q = p;
        p = p->next;
        delete q;
    }
    num = NULL;
}

BigData operator+(BigData a, BigData b) 
{
    BigData tmp;
    BigData::node *p, *q, *end;
    int carry;
    tmp.num = end = new BigData::node(a.num->data + b.num->data);
    carry = tmp.num->data / 10;
    tmp.num->data %= 10;
    p = a.num->next;
    q = b.num->next;
    end = tmp.num;
    while (p != NULL && q != NULL) {
        end->next = new BigData::node(p->data + q->data + carry);
        end = end->next;
        carry = end->data / 10;
        end->data %= 10;
        p = p->next;
        q = q->next;
    }
    if (p == NULL)p = q;
    while (p != NULL) {
        end->next = new BigData::node(p->data + carry);
        end = end->next;
        carry = end->data / 10;
        end->data %= 10;
        p = p->next;
    }
    if (carry != 0) {
        end->next = new BigData::node(carry);
        return tmp;
    }
}

BigData &BigData::operator=(const BigData &x) 
{
    if (&x == this)return *this;
    clear();
    num = new node(x.num->data);
    node *p = num, *q = x.num;
    while (q->next != NULL) {
        q = q->next;
        p->next = new node(q->data);
        p = p->next;
    }
    return *this;
}

ostream &operator<<(ostream &os, const BigData &x) 
{
    string s;
    BigData::node *p = x.num;
    while (p != NULL) 
    {
        s = char(p->data + '0') + s;
        p = p->next;
    }
    os << s;
    return os;
}

istream &operator>>(istream &is, BigData &x) 
{
    char ch;
    x.clear();
    while ((ch = is.get()) != '\n') 
    {
        x.num = new BigData::node(ch - '0', x.num);
    }
    return is;
}

int main() 
{
    BigData a, b, c;
    cin >> a >> b;
    c = a + b;
    cout << c << endl;

    return 0;
}