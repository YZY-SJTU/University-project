# include <iostream>
using namespace std;

template<class T>
class seqList
{
    friend istream &operator>>(istream &is, seqList &x)
    {
    int i;
    for (i=0; i<x.length; ++i)
        is >> x.data[i];
        return is;
    }

    friend ostream &operator<<(ostream &os,const seqList &x)
    {
    int i;
    for (i=0; i<x.length-1; ++i)
        os << x.data[i] << ' ';
    os << x.data[i];
    return os;
    }

    friend seqList operator+(seqList a, seqList b)
    {
    int i;
    seqList tmp(a.length+b.length);
    for (i=0; i<a.length; ++i)
    tmp.data[i] = a.data[i];
    for (i=a.length; i<a.length+b.length; ++i)
    tmp.data[i]=b.data[i-a.length];
    return tmp;
    }

private:
    T *data;
    int length;
public:
    seqList(int x = 0)
    {
        length = x;
        data = new T[length];
    }
    ~seqList()
    {delete data;}
    seqList &operator=(const seqList &x)
    {
    if (this == &x) return *this;
    delete []data;
    length = x.length;
    data = new T[length];
    for (int i = 0; i < length; ++i)
    data[i] = x.data[i];
    return *this;
    }
};

int main() {
    char typeOfInput[6] = {0};
    cin >> typeOfInput;
    int m, n;
    cin >> m >> n;
    if (typeOfInput[0] == 'i') {
        seqList<int> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }

    if (typeOfInput[0] == 'd') {
        seqList<double> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }
    if (typeOfInput[0] == 'c') {
        seqList<char> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }

    return 0;
}