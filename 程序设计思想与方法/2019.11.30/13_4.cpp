#include<iostream>
#include<cstring>

using namespace std;

class LongLongInt
{
private:
    int len;
    int *longlongint;
public:
    LongLongInt(char IntStr[]);
    LongLongInt(const LongLongInt&n);
    ~LongLongInt(){delete []longlongint;}
    void add(const LongLongInt &a,const LongLongInt &b);
    void display();
};

LongLongInt::LongLongInt(char IntStr[])
{
    len=strlen(IntStr)+1;
    longlongint=new int[len];
    longlongint[0]=0;
    for (int i=1; i<len; ++i)
    longlongint[i]=int(IntStr[i-1]-'0');
}

LongLongInt::LongLongInt(const LongLongInt&n)
{
    len=n.len;
    longlongint = new int[len];
    for (int i=0; i<len; ++i)
    longlongint[i]=n.longlongint[i];
}

void LongLongInt::add(const LongLongInt &a,const LongLongInt &b)
{
    int i,sum,*tmp1,*tmp2,*tmp3,AddDigit=0;
    tmp3=longlongint;
    if (a.len>b.len)
    {
        sum = a.len;
        tmp1 = new int[sum];
        tmp2 = new int[sum];
        for (i=0; i<a.len-b.len; ++i)
            tmp1[i]=0;
        for (i=a.len-b.len; i<sum; ++i)
            tmp1[i]=b.longlongint[i-a.len+b.len];
        for (i=sum-1; i>=0; --i)
        {
            if (a.longlongint[i]+tmp1[i]+AddDigit>=10)
            {
                tmp2[i]=a.longlongint[i]+tmp1[i]+AddDigit-10;
                AddDigit=1;
            }
            else
            {
                tmp2[i]=a.longlongint[i]+tmp1[i]+AddDigit;
                AddDigit=0;
            }
        }

    }
    else
    {
        sum = b.len;
        tmp1 = new int[sum];
        tmp2 = new int[sum];
        for (i=0; i<b.len-a.len; ++i)
            tmp1[i]=0;
        for (i=b.len-a.len; i<sum; ++i)
            tmp1[i]=a.longlongint[i-b.len+a.len];
        for (i=sum-1; i>=0; --i)
        {
            if (b.longlongint[i]+tmp1[i]+AddDigit>=10)
            {
                tmp2[i]=b.longlongint[i]+tmp1[i]+AddDigit-10;
                AddDigit=1;
            }
            else
            {
                tmp2[i]=b.longlongint[i]+tmp1[i]+AddDigit;
                AddDigit=0;
            }
        }
    }
    len = sum;
    longlongint = tmp2;
    delete []tmp1;
    delete []tmp3;

}
void LongLongInt::display()
{
    if (longlongint[0]!=0) cout << longlongint[0];
    for (int i=1; i<len; ++i)
    {
        cout << longlongint[i];
    }
    cout << endl;
}

int main()
{
    const int MAXSIZE=1000;
    char arr1[MAXSIZE+1],arr2[MAXSIZE+1];
    cout << "Input the longlongint: ";
    cin.getline(arr1,MAXSIZE);
    cout << "Input the longlongint: ";
    cin.getline(arr2,MAXSIZE);

    LongLongInt num1(arr1),num2(arr2),num3=num1,num4("");
    num4.add(num1,num2);
    cout << "num1 is ";
    num1.display();
    cout << "num2 is ";
    num2.display();
    cout << "num3 is ";
    num3.display();
    cout << "num4 is ";
    num4.display();

    return 0;
}
