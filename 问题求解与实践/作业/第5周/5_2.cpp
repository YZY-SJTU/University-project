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

bool isKeyword(string str)
{
    if(str == "alignas" || str == "alignof" || str == "and" || str == "and_eq" || str == "asm" || 
    str == "atomic_cancel" || str == "atomic_commit" || str == "atomic_noexcept" || str == "auto" ||
    str == "bitand	" || str == "bitor" || str == "bool" || str == "break" || str == "case" || 
    str == "catch" || str == "char" || str == "char8_t" || str == "char16_t" || str == "char32_t" || 
    str == "class" || str == "compl" || str == "concept" || str == "const" || str == "consteval" || 
    str == "constexpr" || str == "constinit" || str == "const_cast" || str == "continue" || str == "co_await" || 
    str == "co_return	" || str == "co_yield" || str == "decltype" || str == "default" || str == "define" || 
    str == "defined" || str == "delete" || str == "do" || str == "double" || str == "dynamic_cast" || 
    str == "elif" || str == "else" || str == "error" || str == "endif" || str == "enum" || 
    str == "explicit" || str == "export" || str == "extern" || str == "false" || str == "final" || 
    str == "float" || str == "for" || str == "friend" || str == "goto" || str == "if" || 
    str == "ifdef" || str == "ifndef" || str == "import" || str == "include" || str == "inline" || 
    str == "int" || str == "line" || str == "long" || str == "module" || str == "mutable" || 
    str == "namespace" || str == "new" || str == "noexcept" || str == "not" || str == "not_eq" || 
    str == "nullptr" || str == "operator" || str == "or" || str == "or_eq" || str == "override" || 
    str == "pragma" || str == "private" || str == "protected" || str == "public" || str == "reflexpr" || 
    str == "register" || str == "reinterpret_cast" || str == "requires" || str == "return" || str == "short" || 
    str == "signed" || str == "sizeof" || str == "static" || str == "static_assert" || str == "static_cast" || 
    str == "struct" || str == "switch" || str == "synchronized" || str == "template" || str == "this" || 
    str == "thread_local" || str == "throw" || str == "xor_eq" || str == "true" || str == "try" || 
    str == "typedef" || str == "typeid" || str == "typename	" || str == "undef	" || str == "union" || 
    str == "unsigned" || str == "using" || str == "virtual" || str == "void" || str == "volatile" || 
    str == "wchar_t" || str == "while" || str == "xor")
    return true;
    else 
    return false;
}

class word //输入以空格为划分的一个单词，判断是否为关键字
{
private:
    string str;
    int currentLength = 0;
public:
    word(){}
    ~word(){}
    
    void clear()
    {
        str = "";
        currentLength = 0;
    }

    int length()
    {return currentLength;}

    void input(char s)
    {
        str += s;
        ++currentLength;
    }

    string output()
    {
        return str;
    }

    bool isIdentifier()
    {
        if(isKeyword(str))
        return false;
        if(!(str[0] <= 'z' && str[0] >= 'a') && !(str[0] <= 'Z' && str[0] >= 'A') && str[0]!='_')
        return false;
        for(int i=1; i<currentLength; ++i)
        {
            if(!(str[i] <= 'z' && str[i] >= 'a') && !(str[i] <= 'Z' && str[i] >= 'A') && !(str[i] <= '9' && str[i] >= '0') && str[i]!='_')
            {
                break;
                return false;
            }
        }
        return true;
    }
};

class identifierGroup
{
private:
    string *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        string *tmp = data;
        maxSize *= 2;
        data = new string[maxSize];
        for (int i = 0; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

    bool isShortNote = false;
    bool isLongNote = false;

public:
    identifierGroup(int initSize = 10)
    {
        data = new string[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~identifierGroup()
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

    string visit(int i)
    {
        return data[i];
    }

    void setPoint(const string &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    void readString(string str)
    {
        word tmp;
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if(isLongNote) //注释部分
            {
                if(str[i] == '*' && str[i+1] == '/')
                {
                    isLongNote = false;
                    ++i;
                }
                    continue;
            }
            if(str[i] == '/')
            {
                if(str[i+1] == '/')
                {
                    isShortNote = true;
                    break;
                }
                else if(str[i+1] == '*')
                {
                    isLongNote = true;
                    
                }
            }
            if(str[i] == '\\' && str[i+1] == 'n')//考虑\n情况
            {
                ++i;
                continue;
            }
            if((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A') || (str[i] <= '9' && str[i] >= '0') || str[i]=='_')
            {
                tmp.input(str[i]);
                continue;
            }
            else
            {
                if(tmp.length() == 0)
                continue;
                else
                {
                    if(!tmp.isIdentifier())
                        tmp.clear();
                    else
                    {
                        int j;
                        for(j=0; j<currentLength; ++j)
                        {
                            if(compare(data[j], tmp.output()))
                            {
                                tmp.clear();
                                break;
                            }
                        }
                        if(j == currentLength)
                        {
                            setPoint(tmp.output());
                            tmp.clear();
                        }
                    }
                }
            }
        }
        if(str[i] == '\0')
        {
            if(tmp.length() != 0)
            {
                if(!tmp.isIdentifier())
                    tmp.clear();
                else
                {
                    int j;
                    for(j=0; j<currentLength; ++j)
                    {
                        if(compare(data[j], tmp.output()))
                        {
                            tmp.clear();
                            break;
                        }
                    }
                    if(j == currentLength)
                    {
                        setPoint(tmp.output());
                        tmp.clear();
                    }
                }
            }
        }
    }

    void sortString() //按字母序排序
    {
        string tmp;
        for(int i=0; i<currentLength - 1; ++i)
        {
            bool flag = false;
            for(int j=0; j<currentLength-i-1; ++j)
            {
                if(data[j].compare(data[j+1]) > 0)
                {
                    tmp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = tmp;
                    flag = true;
                }
            }
            if(!flag)
            break;
        }
    }

    void printIdentifier()
    {
        for(int i=0; i<currentLength; ++i)
        {
            cout << data[i] <<' ';
        }
    }
    
    void traverse() const
    {
        cout << endl;
        for (int i =0; i < currentLength; ++i)
            cout << data[i] <<' ';
    }
};


int main()
{
    string str;
    identifierGroup a;
    while(getline(cin, str))
    a.readString(str);
    
    a.sortString();
    a.printIdentifier();
    return 0;
}