#include <iostream>

using namespace std;

class Rational {
    friend bool operator<(const Rational &r1 , const Rational &r2); 
	friend bool operator==(const Rational &r1 , const Rational &r2); 
	friend bool operator>(const Rational &r1 , const Rational &r2); 
	friend bool operator<=(const Rational &r1 , const Rational &r2); 
	friend bool operator>=(const Rational &r1 , const Rational &r2); 
	friend bool operator!=(const Rational &r1 , const Rational &r2); 
    friend ostream & operator<<(ostream &os, const Rational& obj);
    friend istream& operator>>(istream &in, Rational& obj) ;

private:  
	int num;
	int den;
	void ReductFraction( );
public:
	Rational(int n = 0, int d = 1) { num = n; den = d;}
};

void Rational::ReductFraction()
{
    int tmp = (num > den) ? den : num;

    for (; tmp>1; --tmp)
    if (num % tmp == 0 &&  den % tmp == 0)
    {
        num /= tmp;
        den /= tmp;
        break;
    }
}

bool operator<(const Rational &r1,const Rational &r2) 
{ return r1.num * r2.den < r1.den * r2.num; }

bool operator>(const Rational &r1,const Rational &r2) 
{ return r1.num * r2.den > r1.den * r2.num; }

bool operator<=(const Rational &r1,const Rational &r2) 
{ return r1.num * r2.den <= r1.den * r2.num; }

bool operator>=(const Rational &r1,const Rational &r2) 
{ return r1.num * r2.den >= r1.den * r2.num; }

bool operator==(const Rational &r1,const Rational &r2) 
{ return r1.num == r2.num && r1.den == r2.den;}

bool operator!=(const Rational &r1,const Rational &r2) 
{ return !(r1 == r2);}

ostream & operator<<(ostream &os,   const Rational& obj)
{ 
    os << obj.num << '/' << obj.den;
    return os;
}

istream& operator>>(istream &in, Rational& obj) 
{ in >> obj.num >> obj.den;
    obj.ReductFraction();
    return in;
}

template<class T>
void sort(T arr[], int n)
{
    int j,lh,rh;
    T tmp;
    for (lh=0; lh<n; ++lh)
    {
        rh=lh;
        for (j=lh; j<n; ++j)
        {
            if (arr[j] < arr[rh])
            rh = j;
            
        }
        tmp = arr[lh];
        arr[lh] = arr[rh];
        arr[rh] = tmp;
    }
}

int main()
{
    int i,n;
    cout << "Please input n:";
    cin >> n;
    Rational *arr;
    arr =new Rational [n];
    cout << "Please input " << n << " Rational." <<endl;
    for (i=0; i<n; ++i)
    cin >> arr[i];
    
    sort<Rational>(arr, n);
    
    for (i=0; i<n; ++i)
    cout << arr[i] <<'\t';
    
    delete [] arr;
    return 0;
}