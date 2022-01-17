#include <iostream>

using namespace std;

class Vector
{
friend istream & operator>>(istream & is, Vector & obj);
friend ostream & operator<<(ostream & os, Vector & obj);
friend Vector  operator+(const Vector & n1, const Vector & n2);
friend Vector  operator-(const Vector & n1, const Vector & n2);
friend int operator*(const Vector & n1, const Vector & n2);
private:
    int dem;
    int *vector;
public:
    Vector(int n=0,int *p=NULL);
    ~Vector(){delete []vector;}
    Vector & operator=(const Vector &n);
};

Vector::Vector(int n,int *p):dem(n)
{
    if (n>0)
    {
        vector = new int (dem);
        for (int i=0;i<n; ++i)
        {
            vector[i]=p[i];
        }
    }
}

istream & operator>>(istream & is, Vector & obj)
{
    cout << "Input the dimension of the vector:";
    is >> obj.dem;
    delete [] obj.vector;
    obj.vector=new int [obj.dem];
    cout <<"Input the integer vector:";
    for (int i=0; i<obj.dem ; ++i)
    is >> obj.vector[i];
    return is;
}

ostream & operator<<(ostream & os, Vector & obj)
{
    if (obj.dem==0)
    os << "ERROR" << endl;
    else
    {
        os << '(' << obj.vector[0];
        for (int i=1; i< obj.dem ; ++i)
        os << ',' << obj.vector[i];
        os << ')' << endl;
    }
    return os;
}

Vector  operator+(const Vector & n1, const Vector & n2)
{
    Vector tmp;
    if (n1.dem != n2.dem)
    cout <<"Different dimension! Unable to plus." << endl;

    else
    {
        tmp.dem = n1.dem;
        tmp.vector=new int [tmp.dem];
        for (int i=0; i<tmp.dem; ++i)
        {tmp.vector[i] = n1.vector[i] + n2.vector[i];}
    }

    return tmp;
}

Vector  operator-(const Vector & n1, const Vector & n2)
{
    Vector tmp;
    if (n1.dem != n2.dem)
    cout <<"Different dimension! Unable to minus." << endl;
    else
    {
        tmp.dem = n1.dem;
        tmp.vector=new int [tmp.dem];
        for (int i=0; i<tmp.dem; ++i)
        tmp.vector[i] = n1.vector[i] - n2.vector[i];
    }
    return tmp;
}

int operator*(const Vector & n1, const Vector & n2)
{
    int result=0;
    if (n1.dem != n2.dem)
    {
        cout <<"Different dimension! Unable to multiply." << endl;
    }
    else
    {
        for (int i=0; i<n1.dem; ++i)
        result += n1.vector[i] * n2.vector[i];

    }
    return result;
}

Vector & Vector::operator=(const Vector & n)
{
    if (this == &n) return *this;

    delete [] vector;
    dem = n.dem;
    vector = new int [dem];
    for (int i=0; i<dem; ++i)
    vector[i] = n.vector[i];

    return *this;
}

int main()
{
    Vector n1,n2,n3,n4;

    cin >> n1 >> n2;
    n3 = n1 + n2;
    n4 = n1 - n2;
    cout << "n1 + n2 = "<< n3;
    cout << "n1 - n2 = " << n4;
    cout << "n1 * n2 = " << n1*n2;
    return 0;
}
