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
        cout<<"��������²�����֣�����"<<chance<<"�λ��ᣩ��_____\b\b\b\b\b";
        cin>>guess1>>guess2>>guess3;
        if (guess1==num1) true1+=1;
        else if (guess1==num2||guess1==num3) true2+=1;
        if (guess2==num2) true1+=1;
        else if (guess2==num1||guess2==num3) true2+=1;
        if (guess3==num3) true1+=1;
        else if (guess3==num1||guess3==num2) true2+=1;

        chance-=1;
        cout<<true1<<'A'<<true2<<'B'<<endl;

        if (true1==3) {cout<<"��ϲ����¶��ˡ�"; break;}
        if (chance==0) {cout<<"���ź�����û���ڹ涨�����ڲ¶ԡ�����"<<num1<<num2<<num3<<"��"; break;}
        true1=0,true2=0;
    }
}
