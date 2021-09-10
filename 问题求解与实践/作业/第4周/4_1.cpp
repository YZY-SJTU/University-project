#include <iostream>

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

class twoTuple
{
private:
    double x;
    double y;
public:
    void setX(double num)
    {
        x = num;
    }
    void setY(double num)
    {
        y = num;
    }
    double getX()
    {return x;}
    double getY()
    {return y;}
};

class reference  //转化为多项式过程中记录系数
{
private:
    char *data;
    int currentLength;
    int maxSize;
    char token ='+';
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

    bool inputData(string str)//如果输入不符合，则输出false
    {
        int cnt1 = 0;//检查.的数目 检查一行的数字数量
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if(str[i] != '.' && str[i] != '-' && !(str[i]<= '9' && str[i]>='0'))
            return false;
            if(str[i] == '-')
            {
                if(currentLength != 0)
                return false;
                else token = '-';
            }
            if(str[i] == '.')
            {
                ++cnt1;
                if(cnt1 != 1 || i == 0 || !(str[i+1]<= '9' && str[i+1]>='0'))
                return false;
                else input(str[i]);
            }
            if(str[i]<= '9' && str[i]>='0')
            input(str[i]);
        }
        return true;
    }

    double output()  //将字符串形式的数字转化为double数字
    {
        double x=0, tmp=0;
        bool flag = false;
        int i, length=0, cnt = 1;
        for(i=0; i<currentLength; ++i)
            if (data[i] == '.') 
            {
                ++i;
                if(currentLength - i > 4)
                length = 4;
                else length = currentLength - i;
                
                flag = true; 
                break;
            }
            else x = x * 10 + int(data[i]-'0');
        for(i; i<currentLength && cnt <=4; ++i)
            {
                tmp = tmp * 10 + int(data[i]-'0');
                ++cnt;
            }
        if (flag)
        {
            for(i=0; i<length; ++i)
            tmp /= 10;
            x += tmp;
        }
        if(token == '+') return x;
        else return -x;
    }
};

class seqList
{
private:
    twoTuple *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        twoTuple *tmp = data;
        maxSize *= 2;
        data = new twoTuple[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new twoTuple[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList()
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

    twoTuple visit(int i)
    {
        return data[i];
    }

    void insert(double x, double y)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength].setX(x);
        data[currentLength].setY(y); 
        ++currentLength;
    }

    bool sort()
    {
        bool isChange = false, depth = true;
        double tmp1, tmp2, tmp3;
        for(int i=0; i<currentLength-1; ++i)
        {
            for(int j=0; j<currentLength-i-1; ++j)
            {
                if(data[j].getX() > data[j+1].getX())
                {
                    tmp1 = data[j].getX();
                    tmp2 = data[j].getY();
                    data[j].setX(data[j+1].getX());
                    data[j].setY(data[j+1].getY());
                    data[j+1].setX(tmp1);
                    data[j+1].setY(tmp2);
                    isChange = true;
                }
            }
            if(!isChange)
                break;
        }
        double standard = 0.000001;
        if(currentLength > 1)
        {
            tmp3 = data[1].getX() - data[0].getX();
            for(int i=1; i<currentLength - 1; ++i)
            {
                if(data[i+1].getX()- data[i].getX() - tmp3 > standard || data[i+1].getX()- data[i].getX() - tmp3 < -standard)
                return false;
            }
            return true;
        }
        else return true;
    }

    void print()
    {
        for(int i =0; i< currentLength; ++i)
        {
            cout << "x=" << data[i].getX() <<", y=" << data[i].getY()<<endl;
        }
    }
};

class dataList
{
private:
    seqList data;
    int length;
    bool flag; //为false表示输入出错
public:
    dataList()
    {   
        length = 0;
        flag = true; 
    }

    void inputData(string str) 
    {
        reference tmp1, tmp2;
        char token1 = '+', token2 = '+';
        int cnt1 = 0, cnt2 = 0;//检查.的数目 检查一行的数字数量
        bool isX = true;
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if(isX)
            {
                if(str[i] != '.' && str[i]!=' ' && str[i]!='-' && !(str[i]<= '9' && str[i]>='0'))
                {
                    flag = false;
                    break;
                }
                if(str[i] == '-')
                {
                    if(tmp1.length() == 0)
                    {
                        token1 = '-';
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                if(str[i] == '.')
                {
                    ++cnt1;
                    if(cnt1 != 1 || i == 0 || !(str[i+1]<= '9' && str[i+1]>='0'))
                    {
                        flag = false;
                        break;
                    }
                    else tmp1.input(str[i]);
                }
                if(str[i]<= '9' && str[i]>='0')
                tmp1.input(str[i]);
                if(str[i]==' ')
                {
                    while(str[i+1] ==' ')
                        ++i;
                    ++cnt2;
                    isX = false;
                    cnt1 = 0;
                }
            }
            else
            {
                if(str[i] != '.' && str[i]!=' ' && str[i]!='-' && !(str[i]<= '9' && str[i]>='0'))
                {
                    flag = false;
                    break;
                }
                if(str[i] == '-')
                {
                    if(tmp2.length() == 0)
                    {
                        token2 = '-';
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                if(str[i] == '.')
                {
                    ++cnt1;
                    if(cnt1 != 1 || i == 0 || !(str[i+1]<= '9' && str[i+1]>='0'))
                    {
                        flag = false;
                        break;
                    }
                    else tmp2.input(str[i]);
                }
                if(str[i]<= '9' && str[i]>='0')
                tmp2.input(str[i]);
                if(str[i]==' ')
                {
                    while(str[i+1] ==' ')
                        ++i;
                    ++cnt2;
                }
            }
        }
        if(str[i] == '\0')
        {
            ++cnt2;
            if(cnt2 != 2 || !flag)
            {
                flag = false;
            }
            else
            {
                if(token1 =='+' && token2 =='+')
                data.insert(tmp1.output(), tmp2.output());
                else if(token1 =='-' && token2 =='+')
                    data.insert(-tmp1.output(), tmp2.output());
                    else if(token1 =='+' && token2 =='-')
                        data.insert(tmp1.output(), -tmp2.output());
                        else data.insert(-tmp1.output(), -tmp2.output());
                ++length;
            }
        }
    }

    double calculate(double target) //在排序的前提下计算系数
    {
        double ratio[length];
        for(int i=0; i<length; ++i)
        ratio[i] = data.visit(i).getY();
        for(int i=0; i < length - 1; ++i)//计算Δy
        {
            for(int j = length - 1; j > i; --j)
            ratio[j] = ratio[j] - ratio[j-1];
        }
        if(length >= 2)//计算系数
        {
            double step = data.visit(1).getX() - data.visit(0).getX();
            int factorial = 1;
            double div = 1;
            for(int i=1; i<length; ++i)
            {
                factorial *= i;
                div *= step;
                ratio[i] = ratio[i]/factorial/div;
            }
        }
        double result = ratio[0];
        double mul = 1;
        for(int i=1; i<length; ++i)
        {
            mul *= (target - data.visit(i-1).getX());
            result += mul * ratio[i];
        }
        return result;
    }

    bool sort_smallest()
    {
        return data.sort();
    }

    void print()
    {
        data.print();
    }
    
    bool isRight()
    {
        return flag;
    }
};



int main()
{
    string str;
    getline(cin, str);
    reference tmp;
    double point;
    if(!tmp.inputData(str))
    {
        cout << "error" << endl;
        return 0;
    }
    else 
    {
        point = tmp.output();
        dataList data;
        while(getline(cin, str))
        {
            data.inputData(str);
            if(!data.isRight())
            {
                cout << "error" << endl;
                return 0;
            }
        }
        
        if(!data.sort_smallest())
        {
                cout << "error" << endl;
                return 0;
        }
        print4(data.calculate(point));
        cout << endl;
        return 0;
    }


}
