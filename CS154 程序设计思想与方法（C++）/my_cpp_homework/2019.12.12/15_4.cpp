#include <iostream>

using namespace std;

class Shape
{
protected:
    double x,y; //coordinate of the shape
public:
    Shape(double xx, double yy){x=xx; y=yy;}
    virtual double getArea() const {return 0.0;}
};

class Rectangle:public Shape 
{
protected:
    double width,length;
public:
    Rectangle(double ww, double ll, double xx=0, double yy=0): width(ww), length(ll), Shape(xx, yy){}
    double getArea() const {return width * length;} 
};

class Square:public Rectangle
{
public:
    Square(double ll, double xx=0, double yy=0): Rectangle(ll,ll,xx,yy){}
    double getArea() const {return width * length;} 
};

int main()
{
    double ll,ww,ss;
    cout << "Please input the length of the rectangle:";
    cin >> ll;
    cout << "Please input the width of the rectangle:";
    cin >> ww;
    Rectangle a(ww,ll);
    cout << "The area of the rectangle is " << a.getArea() << endl;
    cout << "Please input the side of the square:";
    cin >> ss;
    Square b(ss);
    cout << "The area of the square is " << b.getArea() << endl;

    return 0;
}