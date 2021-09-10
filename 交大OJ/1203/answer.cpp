#include <iostream>
#include <cstring>

using namespace std;

template<class elemType>
class seqList 
{
    friend istream &operator>>(istream &is, seqList &x) 
    {
        elemType ch;
        for (int i = 0; i < x.maxSize; ++i)
            is >> x.data[i];
        return is;
    }
    friend ostream &operator<<(ostream &os, const seqList &x) 
    {
        int i = 0;
        for (i = 0; i < x.maxSize - 1; ++i)
            os << x.data[i] << " ";
        os << x.data[i];
        return os;
    }
    friend seqList operator+(const seqList a, const seqList b) 
    {
        seqList c(a.length() + b.length());
        int i = 0;
        for (i = 0; i < a.currentLength; ++i) 
            c.data[i] = a.data[i];
        for (int j = 0; j < b.currentLength; ++j) {
            c.data[i++] = b.data[j];
            c.currentLength = i;
        }
        return c;
    }

private:
    elemType *data;
    int currentLength;
    int maxSize;

public:
    seqList(int initSize = 10) 
    {
        data = new elemType[initSize];
        maxSize = initSize;
        currentLength = initSize;
    }

    seqList(const seqList &other) 
    {
        currentLength = other.currentLength;
        maxSize = other.maxSize;
        data = new elemType[maxSize];
        for (int i = 0; i < currentLength; ++i) {
            data[i] = other.data[i];
        }
    }

    ~seqList() 
    {delete[]data;}

    int length() const 
    {return currentLength;}

    seqList &operator=(const seqList &other) 
    {
        if (this == &other) return *this;
        delete[]data;
        currentLength = other.currentLength;
        maxSize = other.maxSize;
        data = new elemType[maxSize];
        for (int i = 0; i < currentLength; ++i) 
            data[i] = other.data[i];
        return *this;
    }
};


int main() {
    char typeOfInput[6] = {0};
    cin >> typeOfInput;
    int m, n;
    cin >> m >> n;
    if (typeOfInput[0] == 'i') 
    {
        seqList<int> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }

    if (typeOfInput[0] == 'd') 
    {
        seqList<double> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }
    if (typeOfInput[0] == 'c') 
    {
        seqList<char> a(m), b(n), c;
        cin >> a >> b;
        c = a + b;
        cout << c;
    }

    return 0;
}