1#include<iostream>
#include<cmath>

using namespace std;

int main(){
    double x1,x2,y1,y2;
    cout <<"������x1,y1:___\b\b\b";
    cin >>x1>>y1;
    cout <<"������x2,y2:___\b\b\b";
    cin >>x2>>y2;
    cout <<"("<<x1<<","<<y1<<")��"<<"("<<x2<<","<<y2<<")֮��ľ���:" <<sqrt(pow((x1-x2),2)+pow((y1-y2),2))<< endl;

}
