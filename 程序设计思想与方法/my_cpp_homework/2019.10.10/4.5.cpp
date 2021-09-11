#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    int num1,num2,num3,guess1,guess2,guess3,chance=7,true1=0,true2=0;
    srand(time(NULL));
    num1 = rand() % 10;
    num2 = rand() % 10;
    num3 = rand() % 10;

    do {
        num2 = rand() % 10;
        }while (num2==num1);

    do {
        num3 = rand() % 10;
        }while (num3==num2||num3==num1);

    cout << num1 <<num2<<num3<< endl;
    while (true){
        cout<<"请输入你猜测的数字（还有"<<chance<<"次机会）：_____\b\b\b\b\b";
        cin>>guess1>>guess2>>guess3;
        if (guess1==num1) true1+=1;
        else if (guess1==num2||guess1==num3) true2+=1;
        if (guess2==num2) true1+=1;
        else if (guess2==num1||guess2==num3) true2+=1;
        if (guess3==num3) true1+=1;
        else if (guess3==num1||guess3==num2) true2+=1;

        chance-=1;
        cout<<true1<<'A'<<true2<<'B'<<endl;

        if (true1==3) {cout<<"恭喜，你猜对了。"; break;}
        if (chance==0) {cout<<"很遗憾，你没有在规定次数内猜对。答案是"<<num1<<num2<<num3<<"。"; break;}
        true1=0,true2=0;
    }
}
