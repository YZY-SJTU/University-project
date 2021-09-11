#include<iostream>

using namespace std;

struct ComplexNumber
{
    int Re;
    int Im;
};
void InputComplex(ComplexNumber &);
void OutputComplex(ComplexNumber &);
ComplexNumber PlusComplex(ComplexNumber &,ComplexNumber &);
ComplexNumber MultplyComplex(ComplexNumber &,ComplexNumber &);

int main()
{
    ComplexNumber p1,p2,PlusResult,MultplyResult;
    InputComplex(p1);
    InputComplex(p2);
    PlusResult = PlusComplex(p1,p2);
    MultplyResult = MultplyComplex(p1,p2);
    cout << "The result of plus is :";
    OutputComplex(PlusResult);
    cout << "The result of multiply is :";
    OutputComplex(MultplyResult);
}

void InputComplex(ComplexNumber &p)
{
    cout <<"Please input real part:";
    cin >> p.Re;
    cout <<"Please input imaginary part:";
    cin >> p.Im;
    cout << endl;
}

void OutputComplex(ComplexNumber &p)
{
    cout << p.Re << '+' << p.Im << 'i' <<endl;
}

ComplexNumber PlusComplex(ComplexNumber &p1,ComplexNumber &p2)
{
    ComplexNumber result;
    result.Re = p1.Re + p2.Re;
    result.Im = p1.Im + p2.Im;
    return result;
}

ComplexNumber MultplyComplex(ComplexNumber &p1,ComplexNumber &p2)
{
    ComplexNumber result;
    result.Re = p1.Re * p2.Re - p1.Im * p2.Im;
    result.Im = p2.Re * p1.Im + p1.Re * p2.Im;
    return result;
}
