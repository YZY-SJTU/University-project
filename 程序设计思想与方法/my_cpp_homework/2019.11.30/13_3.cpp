#include<iostream>

using namespace std;

class Circle
{
private:
    double x_of_centre;
    double y_of_centre;
    double radius;
public:
    Circle(double x=0,double y=0 , double r=0):x_of_centre(x),y_of_centre(y),radius(r) {}
    void getO(double &x,double &y){x=x_of_centre; y=y_of_centre;}
    void getR(double &r){r=radius;}
    void setR(double r){if (r>=0) radius=r; else cout << "Wrong number!Set unsuccessfully"<<endl;}
    void moveTo(double x,double y){x_of_centre=x; y_of_centre=y;}
    void display() const {cout <<"The centre is ("<< x_of_centre<<','<< y_of_centre<<')'<<endl <<"The radius is "<<radius<<endl;}
};


int main()
{
    double x,y,r,add1,add2,add3;
    Circle round;
    round.getO(x,y);
    round.getR(r);
    round.display();
    cout <<"Input the increment of x: ";
    cin >> add1;
    cout <<"Input the increment of y: ";
    cin >> add2;
    cout <<"Input the increment of r: ";
    cin >> add3;
    x+=add1;
    y+=add2;
    r+=add3;
    round.moveTo(x,y);
    round.setR(r);
    round.display();

    return 0;
}
