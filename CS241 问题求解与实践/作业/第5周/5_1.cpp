#include <iostream>
#include <string>

using namespace std;

bool compare(const string &a, const string &b)
{
    if(a.length()!= b.length())
    return false;
    else
    {
        for(int i=0; a[i]!='\0'; ++i)
        if(a[i] != b[i]) return false;

        return true;
    }
    
}

class word //英文字母不关注大小写，只输入小写字母
{
private:
    string str;
    bool isPureEnglish = true;
    bool isPureNumber = true;
    bool only_ = true;
    int currentLength = 0;
public:
    word(){}
    ~word(){}
    
    void clear()
    {
        str = "";
        isPureEnglish = true;
        isPureNumber = true;
        only_ = true;
        currentLength = 0;
    }

    int length()
    {return currentLength;}

    char lastChar()
    {return str[currentLength-1];}

    void input(char s)
    {
        if(s <= 'z' && s >= 'a')
        {
            str += s;
            ++currentLength;
            isPureNumber = false;
            only_ = false;
        }
        if(s <= 'Z' && s >= 'A')
        {
            str += char(s + 32);
            ++currentLength;
            isPureNumber = false;
            only_ = false;
        }
        if(s >= '0' && s <= '9')
        {
            str += s;
            ++currentLength;
            isPureEnglish = false;
            only_ = false;
        }
        if(s == '-' || s == '_')
        {
            str += s;
            ++currentLength;
            isPureNumber = false;
            isPureEnglish = false;
        }
    }

    void SecondInput(char s)
    {
        if((s <= 'z' && s >= 'a') || (s <= 'Z' && s >= 'A'))
        {
            str += s;
            ++currentLength;
            isPureNumber = false;
            only_ = false;
        }
        if(s >= '0' && s <= '9')
        {
            str += s;
            ++currentLength;
            isPureEnglish = false;
            only_ = false;
        }
        if(s == '-' || s == '_')
        {
            str += s;
            ++currentLength;
            isPureNumber = false;
            isPureEnglish = false;
        }
    }

    string outputLine2()
    {
        return str;
    }

    string output() //仅输出合法的不为空的字符串
    {
        if(only_)
        {
            return str;
        }
        if(str[currentLength - 1] == '-' || str[currentLength - 1] == '_')
        {
            int cnt = 1;
            while(str[currentLength - cnt - 1] == '-' || str[currentLength - cnt - 1] == '_')
            {
                ++cnt;
            }
            string tmp = str.substr(0,currentLength-cnt);
            return tmp;
        }
        if(str[0] == '-' || str[0] == '_')
        {
            int cnt = 1;
            while(str[cnt] == '-' || str[cnt] == '_')
            {
                ++cnt;
            }
            string tmp = str.substr(cnt,currentLength-cnt);
            return tmp;
        }
        return str;
    }
};

struct TokenPoint
{
    string str;
    int number = 0;

};

class TokenGroup
{
    private:
    TokenPoint *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        TokenPoint *tmp = data;
        maxSize *= 2;
        data = new TokenPoint[maxSize];
        for (int i = 0; i < currentLength; ++i)
            {
                data[i] = tmp[i];
            }
        delete[] tmp;
    }

public:
    TokenGroup(int initSize = 10)
    {
        data = new TokenPoint[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~TokenGroup()
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

    TokenPoint visit(int i)
    {
        return data[i];
    }

    void setPoint(string s)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength].str = s;
        data[currentLength].number = 1;
        ++currentLength;
    }

    void readString(string str)
    {
        word tmp;
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if((str[i] >= '0' && str[i] <= '9') || (str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A') || str[i] == '-' || str[i] == '_')
            {
                tmp.input(str[i]);
            }
            else
            {
                if(tmp.length() == 0)
                {
                    continue;
                }
                int j;
                for(j=0; j<currentLength; ++j)
                {
                    if(compare(tmp.output(), data[j].str))
                    {
                        ++data[j].number;
                        break;
                    }
                }
                if(j == currentLength)
                {
                    setPoint(tmp.output());
                }
                tmp.clear();
            }
        }
        if(str[i] == '\0')
        {
            if(tmp.length() != 0)
            {
                int j;
                for(j=0; j<currentLength; ++j)
                {
                    if(compare(tmp.output(), data[j].str))
                    {
                        ++data[j].number;
                        break;
                    }
                }
                if(j == currentLength)
                {
                    setPoint(tmp.output());
                }
                tmp.clear();
            }
        }
    }

    void readLine2(string str)
    {
        word tmp;
        int cnt = 0;
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if((str[i] >= '0' && str[i] <= '9') || (str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A') || str[i] == '-' || str[i] == '_')
            {
                tmp.SecondInput(str[i]);
            }
            else
            {
                if(tmp.length() == 0)
                {
                    continue;
                }
                setPoint(tmp.outputLine2());
                ++cnt;
                tmp.clear();
            }
        }
        if(str[i] == '\0')
        {
            if(tmp.length() != 0)
            {
                setPoint(tmp.outputLine2());
                ++cnt;
                tmp.clear();
            }
        }
    }

    void traverse() const
    {
        for(int i=0; i<currentLength; ++i)
        {
            cout << data[i].str <<"," <<data[i].number<<endl;
        }
    }
};

void outputTokenNumber(TokenGroup arr, string str)
    {
        TokenGroup tmp1, tmp2;
        tmp1.readString(str);
        tmp2.readLine2(str);
        for(int i=0; i<tmp1.length(); ++i)
        {
            int j;
            for(j=0; j<arr.length(); ++j)
            {
                if(compare(arr.visit(j).str, tmp1.visit(i).str))
                {
                    if(i == tmp1.length() - 1)
                    cout << '(' << tmp2.visit(i).str << ',' << arr.visit(j).number << ')' << endl;
                    else 
                    cout << '(' << tmp2.visit(i).str << ',' << arr.visit(j).number << ')' << ' ';
                    break;
                }
            }
            if(j == arr.length())
            {
                if(i == tmp1.length() - 1)
                cout << '(' << tmp2.visit(i).str << ',' << 0 << ')' <<endl;
                else 
                cout << '(' << tmp2.visit(i).str << ',' << 0 << ')' << ' ';
            }
        }
    }

int main()
{
    string str1, str2;  
    getline(cin, str1);
    getline(cin, str2);
    TokenGroup a;
    a.readString(str1);
    outputTokenNumber(a, str2);

}