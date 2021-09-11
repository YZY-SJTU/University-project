#include <iostream>

using namespace std;

class Point
{
friend Point operator-(const Point &p);
friend ostream & operator<<(ostream & os,  Point &obj);
friend istream & operator>>(istream & is,  Point &obj);

private:
    double x;
    double y;
    double z;

public:
};

Point operator-(const Point &p)
{
    Point tmp;
    tmp.x = -p.x;
    tmp.y = -p.y;
    tmp.z = -p.z;
    return tmp;
}

ostream  & operator<<(ostream & os, Point &obj)
{
    os << '(' << obj.x << ',' << obj.y << ',' << obj.z << ')';
    return os;
}

istream & operator>>(istream & is,  Point &obj)
{
    is >> obj.x >> obj.y >> obj.z;
    return is;
}

int main()
{
    Point p1,p2;
    cin >> p1;
    p2=-p1;
    cout <<p2;

    return 0;
}
