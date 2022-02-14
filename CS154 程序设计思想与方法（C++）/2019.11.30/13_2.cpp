#include<iostream>

using namespace std;

enum CPU_Rank {P1=1,P2,P3,P4,P5,P6,P7};
class CPU
{
private:
    CPU_Rank rank;
    int frequency;
    float voltage;
public:
    CPU(CPU_Rank r=P1,int f=0,int v=0):rank(r),frequency(f),voltage(v)
    {}
    ~CPU(){rank=P1;}
    void run();
    void stop();
};

void CPU::run()
{
    int p;
    cout << "Input the current frequency:";
    cin >> frequency;
    cout << "Input the current voltage:";
    cin >> voltage;
    p=int( voltage/frequency)/10;
    switch (p)
    {
    case 0: rank=P1; break;
    case 1: rank=P2; break;
    case 2: rank=P3; break;
    case 3: rank=P4; break;
    case 4: rank=P5; break;
    case 5: rank=P6; break;
    default: rank=P7;
    }

}

void CPU::stop()
{
    frequency=0;
    voltage=0;
    cout <<"The current rank is ";
    switch (rank)
    {
    case 1: cout<<"P1"; break;
    case 2: cout<<"P2"; break;
    case 3: cout<<"P3"; break;
    case 4: cout<<"P4"; break;
    case 5: cout<<"P5"; break;
    case 6: cout<<"P6"; break;
    case 7: cout<<"P7"; break;
    }
}
int main()
{
    CPU thing;
    thing.run();
    thing.stop();

    return 0;
}

