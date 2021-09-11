#include <iostream>

using namespace std;

//the definition and realization of Complex
class Complex{
	friend Complex operator*(Complex x, Complex y);
	friend istream& operator>>(istream &is, Complex &obj);
    friend ostream& operator<<(ostream &os, const Complex &obj);
	double real;   
	double imag;  
public:
	Complex(int r1 = 0, int i1= 0):real(r1), imag(i1) {}
}; 

Complex operator*(Complex x, Complex y) 
{ 
    Complex tmp;
    tmp.real = x.real * y.real - x.imag * y.imag; 
    tmp.imag = x.imag * y.real + x.real * y.imag; 
    return tmp;
} 
istream& operator>>(istream &is, Complex &obj) 
{ 
    cout << "Please input the real:";
    is >> obj.real;         
    cout << "Please input the imag:";
    is >> obj.imag;        
    return is;
}

ostream& operator<<(ostream &os, const Complex &obj)
{ 
    os << obj.real << " + " << obj.imag << "i"; 
    return os;
} 

template<class T>
T power(T x, int n)
{
    T result=T (1);
    for (int i=0; i<n; ++i)
    result = x * result;
    return result;
}

int main()
{
    int n;
    Complex a;
    cin >> a;
    cout <<"Please input the power";
    cin >> n;
    cout << power<Complex>(a,n);

    return 0;
}