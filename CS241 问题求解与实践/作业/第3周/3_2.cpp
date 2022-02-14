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
        for (int i = 0; i < currentLength; ++i)
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

    int length() const
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

class listOf2D
{
private:
    double **data;
    int currentLength,currentDepth;
    int maxLength,maxDepth;
    void doubleSize()
    {
        double **tmp = data;
        maxLength *= 2;
        maxDepth *= 2;
        data = new double*[maxDepth];
        for(int i=0; i<maxDepth; ++i)
        data[i] = new double[maxLength];
        for (int i = 0; i < currentDepth; ++i)
            {
                for(int j = 0; j< currentLength; ++j)
                data[i] = tmp[i];
            }
        for(int i=0; i<maxDepth/2; ++i)
        delete tmp[i];
        delete tmp;
    }

public:
    listOf2D(int initLength = 10, int initDepth = 10)
    {
        data = new double*[initDepth];
        for(int i=0; i<initDepth; ++i)
        data[i] = new double[initLength];
        maxLength = initLength;
        maxDepth = initDepth;
        currentLength = 0;
        currentDepth = 0;
    }

    ~listOf2D()
    {
        for(int i=0; i<currentDepth; ++i)
        delete data[i];
        delete data;
    }

    int length() const
    {
        return currentLength;
    }

    int depth() const
    {
        return currentDepth;
    }

    void calculate(int i, int j, const double &x)
    {
        while(i >= maxDepth || j >= maxLength)
        doubleSize();
        if(i < currentDepth && j < currentLength)
            data[i][j] += x;
        else if(i >= currentDepth && j < currentLength)
        {
            for(int k=currentDepth; k<=i; ++k)
                for(int l=0; l<currentLength; ++l)
                data[k][l] = 0;
            data[i][j] += x;
            currentDepth = i + 1;
        }
            else if(i < currentDepth && j >= currentLength)
            {
                for(int k=0; k<currentDepth; ++k)
                    for(int l=currentLength; l<=j; ++l)
                    data[k][l] = 0;
                data[i][j] += x;
                currentLength= j + 1;
            }
                else
            {
                for(int k=0; k<currentDepth; ++k)
                    for(int l=currentLength; l<=j; ++l)
                    data[k][l] = 0;
                for(int k=currentDepth; k<=i; ++k)
                    for(int l=0; l<=j; ++l)
                    data[k][l] = 0;
                data[i][j] += x;
                currentDepth = i + 1;
                currentLength= j + 1;
            }    
    }

    double search(int i, int j) const
    {
        return data[i][j];
    }
};

class LinearEquations
{
private:
    listOf2D ratio;
    seqList list;
    bool flag;
public:
    LinearEquations()
    {
        flag = true;
    }

    void inputEquation(string str, int line)//第line个方程对应到第line-1行
    {
        reference tmp1, tmp2; //储存系数,指数
        char cal2 = '+'; //储存+-,初始为+保证数字开头的情况
        int cnt1=0; //cnt1检查.的个数
        bool isX = false, isRatio = true, isEqual = false;
        int i;
    
        for(i=0; str[i]!='\0'; ++i)
        {
            if(str[i] == '=')
            {
                if(str[i+1] == '_' || str[i+1] == '\0' ||str[i+1] == '=' || str[i+1] == '.' || i==0 || isEqual )
                {
                    flag = false;
                    break;
                }
                else 
                {
                    isEqual = true;
                    if(!isX)
                        list.calculate(line-1, -tmp1.output(),cal2);
                    else if(tmp2.length() == 0) 
                    {
                        flag = false;
                        break;
                    }
                        else 
                        {
                            if(cal2 =='+')
                            ratio.calculate(line-1,int(tmp2.output())-1, tmp1.output());
                            else if(cal2 =='-')
                            ratio.calculate(line-1,int(tmp2.output())-1, -tmp1.output());
                        }
                    isX = false; 
                    isRatio = true;
                    cal2 = '+';
                    cnt1 = 0;
                    tmp1.clear();
                    tmp2.clear();
                }
            }
            else if(str[i] == '+' || str[i] == '-') 
                {
                    if(i == 0) cal2 = str[i];
                    else if(str[i+1] == '+' || str[i+1] == '-' ||str[i+1] == '=')
                    {
                        flag = false; 
                        break;
                    }
                        else 
                        {
                            if(!isX)
                            {
                                if(!isEqual)
                                list.calculate(line-1, -tmp1.output(),cal2);
                                else
                                list.calculate(line-1, tmp1.output(),cal2);
                            } 
                            else if(tmp2.length() == 0) 
                                {
                                    flag = false;
                                    break;
                                }
                                else 
                                {
                                    if(!isEqual)
                                    {
                                        if(cal2 =='+')
                                        ratio.calculate(line-1,int(tmp2.output())-1, tmp1.output());
                                        else if(cal2 =='-')
                                        ratio.calculate(line-1,int(tmp2.output())-1, -tmp1.output());
                                    }
                                    else
                                    {
                                    if(cal2 =='+')
                                    ratio.calculate(line-1,int(tmp2.output())-1, -tmp1.output());
                                    else if(cal2 =='-')
                                    ratio.calculate(line-1,int(tmp2.output())-1, tmp1.output());
                                    }
                                }
                            isX = false; 
                            isRatio = true;
                            cal2 = str[i];
                            cnt1 = 0;
                            tmp1.clear();
                            tmp2.clear();
                        }
                }
            else if(str[i]!='_' && str[i]!='+' && str[i]!='-' && str[i]!='x' && str[i]!='.' && !(str[i]>='0' && str[i]<='9'))
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
                                    isRatio = false;
                                    ++i;
                                    if(str[i] !='_')
                                    {
                                        flag = false;
                                        break;
                                    }                            
                                    if(tmp1.length() == 0)
                                    {
                                        if(!isEqual)
                                        tmp1.input('1');
                                        else
                                        {
                                            tmp1.input('-');
                                            tmp1.input('1');
                                        }
                                    }
                                    if(!(str[i+1] <= '9' && str[i+1] >= '0'))
                                    {
                                        flag = false;
                                        break;
                                    }
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
            if(!isEqual)
            {
                if(i!=0)
                flag = false;
            }
            else if(!isX) 
            {
                if(isRatio)  
                list.calculate(line-1, tmp1.output(), cal2);
            }
                else 
                {
                    if(tmp2.length() == 0) flag = false;
                    else 
                    {
                        if(cal2 =='+')
                        ratio.calculate(line-1,int(tmp2.output())-1, -tmp1.output());
                        else if(cal2 =='-')
                        ratio.calculate(line-1,int(tmp2.output())-1, tmp1.output());
                    }
                }
        }
    }

    void result()
    {
        if(!flag || ratio.length()!=ratio.depth() || ratio.depth() == 0 || ratio.length() == 0)
        {
            cout <<"error" <<endl;
            return;
        }
        else
        {
            for(int i=0; i<ratio.length(); ++i)//消元部分
            {
                if(ratio.search(i,i)==0) //第i次消元左上元素为0
                {
                    int tmp1=i+1;
                    while(ratio.search(tmp1,i) == 0 && tmp1<ratio.depth())
                        ++tmp1;
                    if (tmp1 == ratio.depth())
                    {
                        cout << "error" <<endl;
                        return;
                    }
                    else
                    {
                        for(int j=0; j<ratio.length(); ++j)
                            ratio.calculate(i, j, ratio.search(tmp1, j));
                        list.calculate(i, list.search(tmp1), '+');
                    }
                }
                for(int k=1; k<ratio.depth()-i; ++k)
                {
                    double tmp2 = ratio.search(i+k, i)/ratio.search(i,i);
                    for(int l=i; l<ratio.length(); ++l)
                    {
                        ratio.calculate(i+k, l, -tmp2 * ratio.search(i,l));
                    }
                    list.calculate(i+k,tmp2*list.search(i),'-');
                }
            }
            //回代部分
            double tmp2; 
            for(int m = ratio.depth()-1; m>=0; --m)
            {
                tmp2 = list.search(m)/ratio.search(m, m);
                list.calculate(m,tmp2-list.search(m),'+');
                ratio.calculate(m, m,1-ratio.search(m, m));
                for(int n=0; n<m; ++n)
                {
                    list.calculate(n, tmp2*ratio.search(n, m), '-');
                    ratio.calculate(n, m, -ratio.search(n, m));
                }
            }
            for(int t=0; t<list.length(); ++t)
            {
                print4(list.search(t));
                cout <<" ";
            }
            cout <<endl;
        }
    }
};

int main()
{
    string str;
    LinearEquations a;
    int cnt = 1;
    while(getline(cin, str))
    {
        a.inputEquation(str,cnt);
        ++cnt;
    }
    a.result();
    return 0;
}