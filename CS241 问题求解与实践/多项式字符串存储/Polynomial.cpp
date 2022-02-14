#include <iostream>
#include <iomanip>

using namespace std;

void print4(double x)
{
    string a;
    a = std::to_string(x);
    int i = 0,cnt = 0;
    bool flag = false;
    while(cnt < 4 && a[i] !='\0')
    {
        if(flag) ++cnt;
        if(a[i] == '.')
        flag = true;
        cout << a[i];
        ++i;
    }
}

class reference  //转化为多项式过程中记录系数
{
private:
    char *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        char *tmp = data;
        maxSize *= 2;
        data = new char[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    reference(int initSize = 10)
    {
        data = new char[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~reference()
    {
        delete[] data;
    }

    void clear()
    {
        currentLength = 0;
    }

    int length()
    {
        return currentLength;
    }

    void input(const char &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    double output()  //将字符串形式的数字转化为double数字
    {
        double x=0, tmp=0;
        bool flag = false;
        int i, length=0;
        for(i=0; i<currentLength; ++i)
            if (data[i] == '.') 
            {++i; length = currentLength - i; flag = true; break;}
            else x = x * 10 + int(data[i]-'0');
        for(i; i<currentLength; ++i)
            tmp = tmp * 10 + int(data[i]-'0');
        if (flag)
        {
            for(i=0; i<length; ++i)
            tmp /= 10;
            x +=tmp;
        }
        return x;
    }
};

class seqList
{
private:
    double *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        double *tmp = data;
        maxSize *= 2;
        data = new double[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new double[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList()
    {
        delete[] data;
    }

    int length()
    {
        return currentLength;
    }

    void calculate(int i, const double &x, const char &flag)
    {
        while(i >= maxSize)
        doubleSpace();
        for(int j=currentLength; j<=i; j++)
        data[j] = 0;
        if(i >= currentLength)
        currentLength = i + 1; 
        if(flag == '+') data[i] += x;
        if(flag == '-') data[i] -= x;
    }

    double search(int i) const
    {
        return data[i];
    }
};


class Polynomial
{
private:
    seqList ratio;
    bool flag = true;
public:
Polynomial(string str)
{
    reference tmp1, tmp2; //储存系数,指数
    char cal2 = '+'; //储存+-,初始为+保证数字开头的情况
    int cnt1=0; //cnt1检查.的个数
    bool isX = false, isRatio = true;
    int i;
    
    for(i=0; str[i]!='\0'; ++i)
    {
        if(str[i] == '+' || str[i] == '-') 
            {
                if(i == 0) cal2 = str[i];
                else if(str[i+1] == '+' || str[i+1] == '-')
                {
                    flag = false; 
                    break;
                }
                    else 
                    {
                        if(!isX)
                        {
                            if(isRatio)  ratio.calculate(0, tmp1.output(), cal2);
                            else    
                            {
                                double mul = 1;
                                for(int i = 0; i < tmp2.output(); ++i)
                                mul *= tmp1.output();
                                ratio.calculate(0, mul, cal2);
                            }
                        } 
                        else if(tmp2.length() == 0) flag = false;
                            else ratio.calculate(int(tmp2.output()), tmp1.output(), cal2);
                        isX = false; 
                        isRatio = true;
                        cal2 = str[i];
                        cnt1 = 0;
                        tmp1.clear();
                        tmp2.clear();
                    }
            }
        else if(str[i]!='^' && str[i]!='+' && str[i]!='-' && str[i]!='x' && str[i]!='.' && !(str[i]>='0' && str[i]<='9'))
        {
            flag = false;
            break;
        }
            else if(isRatio)
            {
                if(str[i]>='0' && str[i]<='9')
                    tmp1.input(str[i]);
                else if(str[i]=='.')
                {
                    ++cnt1;
                    if(tmp1.length() == 0 || !(str[i+1]>='0' && str[i+1]<='9') || cnt1 != 1) 
                    {
                        flag = false; 
                        break;
                    }
                    else tmp1.input(str[i]);
                }
                else if(str[i] == 'x')
                {
                    isX = true;                            
                    if(tmp1.length() == 0)
                    tmp1.input('1');
                    if(str[i+1] == '^')
                    {
                        isRatio = false;
                        ++i;
                        if(str[i+1] == '-' ||str[i+1] == '+')
                        {
                            flag = false;
                            break;
                        }
                    }
                    else if(str[i+1] =='+' || str[i+1] =='-')
                            tmp2.input('1');
                        else if(str[i+1] =='\0')
                            tmp2.input('1');
                            else
                            {
                                flag = false; 
                                break;
                            }
                }
                else if(str[i] =='^')
                {
                    if(str[i+1] == '+' || str[i+1] == '-')
                    {
                        flag = false;
                        break;
                    }
                    isRatio = false;
                }
            }
                else if(str[i]>='0' && str[i]<='9')
                        tmp2.input(str[i]);
                    else
                    {
                        flag = false;
                        break;
                    }
    }
    if(str[i] == '\0')
    {
        if(!isX) 
        {
            if(isRatio)  ratio.calculate(0, tmp1.output(), cal2);
            else    
            {
                double mul = 1;
                for(int i = 0; i < tmp2.output(); ++i)
                mul *= tmp1.output();
                ratio.calculate(0, mul, cal2);
            }
        }
        else {
            if(tmp2.length() == 0) flag = false;
            else ratio.calculate(int(tmp2.output()), tmp1.output(), cal2);}
    }
}
    Polynomial(double a[], int n)
    {
        for(int i=0; i<n; ++i)
        ratio.calculate(i, a[i], '+');
    }
    void simplify()
    {
        if(!flag) cout << "error";
        else 
        {
            bool first = false;
            for(int i=ratio.length()-1; i>=2; --i)
            {
                if(ratio.search(i) < 0)
                {
                    first = true;
                    print4(ratio.search(i));
                    cout << "x^" << i;
                }
                else if(ratio.search(i) > 0)
                {
                    if(!first) 
                    {
                        first = true;
                        print4(ratio.search(i));
                        cout << "x^" << i;
                    }
                    else 
                    {
                        cout << '+';
                        print4(ratio.search(i)); 
                        cout << "x^" << i;
                    }
                }
            }
            if(ratio.length() > 1)
            {
                if(ratio.search(1) < 0)
                {
                    first = true;
                    print4(ratio.search(1));
                    cout << 'x';
                }
                else if(ratio.search(1) > 0)
                    {
                        if(!first) 
                        {
                            first = true;
                            print4(ratio.search(1));
                            cout << 'x';
                        }
                        else 
                        {
                            cout << '+';
                            print4( ratio.search(1));
                            cout << 'x';
                        }
                    }
            }
            if(ratio.length() > 0)
            {
                if(ratio.search(0) < 0)
                {
                    first = true;
                    print4(ratio.search(0));
                }
                else if(ratio.search(0) > 0)
                    {
                        if(!first) 
                        {
                            first = true;
                            print4(ratio.search(0));
                        }
                        else 
                        {
                            cout << '+'; 
                            print4(ratio.search(0));
                        }
                    }
            }
            if(!first) print4(0);
        }
        cout << endl;
    }

    void diff()
    {
        if(!flag) cout << "error";
        else 
        {
            bool first = false;
            for(int i=ratio.length()-1; i>=3; --i)
            {
                if(ratio.search(i) < 0)
                {
                    first = true;
                    print4(i*ratio.search(i));
                    cout << "x^" << i-1;
                }
                else if(ratio.search(i) > 0)
                {
                    if(!first) 
                    {
                        first = true;
                        print4(i*ratio.search(i));
                        cout << "x^" << i-1;
                    }
                    else 
                    {
                        cout << '+'; 
                        print4(i*ratio.search(i));
                        cout << "x^" << i-1;
                    }
                }
            }
            if(ratio.length() > 2)
            {
                if(ratio.search(2) < 0)
                {
                    first = true;
                    print4(2*ratio.search(2));
                    cout << 'x';
                }
                else if(ratio.search(2) > 0)
                    {
                        if(!first) 
                        {
                            first = true;
                            print4(2*ratio.search(2));
                            cout << 'x';
                        }
                        else 
                        {
                            cout << '+';
                            print4(2*ratio.search(2)); 
                            cout << 'x';
                        }
                    }
            }
            if(ratio.length() > 1)
            {
                if(ratio.search(1) < 0)
                {
                    first = true;
                    print4(ratio.search(1));
                }
                else if(ratio.search(1) > 0)
                    {
                        if(!first)
                        {
                            first = true;
                            print4(ratio.search(1));
                        } 
                        else 
                        {
                            cout << '+'; 
                            print4(ratio.search(1));
                        }
                    }
            }
            if(ratio.length() == 1)
            {
                first = true;
                print4(0);
            }
            if(!first) print4(0);
        }
        cout << endl;
    }

    void number(double x)
    {
        if(!flag) cout << "error";
        else
        {
            double result = 0, tmp = 1;
            for(int i=0; i<ratio.length(); ++i)
            {
                result +=ratio.search(i)*tmp;
                tmp *= x;
            }
            print4(result);
        }
        cout << endl;
    }

    double num(int i)
    {return ratio.search(i);}

    int RatioLength()
    {return ratio.length();}
};