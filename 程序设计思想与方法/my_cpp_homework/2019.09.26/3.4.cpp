#include<iostream>

using namespace std;

int main(){
    double x1,x2,x3,y1,y2,y3;
    cout<<"x1,y1:___\b\b\b";
    cin >>x1>>y1;
    cout<<"x2,y2:___\b\b\b";
    cin >>x2>>y2;
    cout<<"x3,y3:___\b\b\b";
    cin >>x3>>y3;
    if (x1==x2&&x2==x3)    //以横坐标的差为分母，只需讨论横坐标的差有0出现的情况 
        cout <<"Yes"<<endl;
    else if (x1==x2||x2==x3)
        cout <<"No"<<endl;
        else if ((y1-y2)/(x1-x2)==(y3-y2)/(x3-x2))
        cout <<"Yes"<<endl;
            else cout <<"No"<<endl;
}
