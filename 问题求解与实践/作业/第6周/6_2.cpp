#include <iostream>

using namespace std;

class hfTree
{
private:
    struct Node
    {
        char data;
        int weight;
        int parent, left, right; 
    };

    Node *tree;
    int length;
public:
    struct hfCode
    {
        char data;
        string code;
    };
    hfTree(const char *v,const int *w, int size) //v为代编码的符号，w为每个符号对应的权值，size为长度
    {
        const int MAX_INT = 32767;
        int min1, min2;
        int x, y;

        //置初值
        length = 2 * size;
        tree = new Node[length];

        for (int i = size; i < length; ++i)
        {
            tree[i].weight = w[i - size];
            tree[i].data = v[i - size];
            tree[i].parent = tree[i].left = tree[i].right = 0;
        }

        //归并森林中的树
        for (int i = size - 1; i > 0; --i)
        {
            min1 = min2 = MAX_INT;
            x = y = 0;
            for(int j = i + 1; j < length; ++j)
            if (tree[j].parent == 0)
                if (tree[j].weight < min1)
            {
                min2 = min1;
                min1 = tree[j].weight;
                x = y;
                y = j;    
            }
            else if (tree[j].weight < min2)
            {
                min2 = tree[j].weight;
                x = j;
            }
            tree[i].weight = min1 + min2;
            tree[i].left = x;
            tree[i].right = y;
            tree[i].parent = 0;
            tree[x].parent = i;
            tree[y].parent = i;
        }
    }

    void getCode(hfCode result[])//获得一个result的编码数组与长度l
    {
        int size = length / 2;
        int p, s;

        for (int i = size; i < length; ++i)
        {
            result[i - size].data = tree[i].data;
            result[i - size].code = "";
            p = tree[i].parent;
            s = i;
            while (p)
            {
                if (tree[p].left == s)
                    result[i - size].code = '0' + result[i - size].code;
                else result[i - size].code = '1' + result[i - size].code;
                s = p;
                p = tree[p].parent;
            }
        }
    }

    ~hfTree(){delete []tree;}
};

struct WordPoint
{
    string str;
    int number = 0;
};

class WordGroup
{
private:
    WordPoint *data;
    int currentLength;
    int maxSize;

    int IgnoreEnter;//未计算的回车数量+1
    int otherChar;//非字母的字符数量
    void doubleSpace()
    {
        WordPoint *tmp = data;
        maxSize *= 2;
        data = new WordPoint[maxSize];
        for (int i = 0; i < currentLength; ++i)
            {
                data[i] = tmp[i];
            }
        delete[] tmp;
    }

public:
    WordGroup(int initSize = 10)
    {
        data = new WordPoint[initSize];
        maxSize = initSize;
        currentLength = 0;
        otherChar = 0;
        IgnoreEnter = 0;
    }

    ~WordGroup()
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

    int otherCharNum()
    {
        otherChar += IgnoreEnter - 1;
        IgnoreEnter = 1;
        return otherChar;
    }

    WordPoint getWord(int i)
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
        string tmp;
        int i;
        for(i=0; str[i]!='\0'; ++i)
        {
            if((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A'))
            {
                tmp+=str[i];
            }
            else
            {
                otherChar++;
                if(tmp.length() == 0)
                {
                    continue;
                }
                int j;
                for(j=0; j<currentLength; ++j)
                {
                    if(tmp.compare(data[j].str) == 0)
                    {
                        ++data[j].number;
                        break;
                    }
                }
                if(j == currentLength)
                {
                    setPoint(tmp);
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
                    if(tmp.compare(data[j].str) == 0)
                    {
                        ++data[j].number;
                        break;
                    }
                }
                if(j == currentLength)
                {
                    setPoint(tmp);
                }
                tmp.clear();
            }
        }
        ++IgnoreEnter;
    }
};

int main()
{
    string str;
    getline(cin, str);
    WordGroup refer;
    refer.readString(str);
    getline(cin, str);
    refer.readString(str);
    getline(cin, str);
    refer.readString(str);


    char sample[refer.length()]={};//构造哈夫曼树
    int weight[refer.length()];
    for(int i=0; i<refer.length(); ++i)
    weight[i] = refer.getWord(i).number;
    hfTree::hfCode code[refer.length()];
    hfTree tmp(sample, weight, refer.length());
    tmp.getCode(code);

    int sum = 0;//计算
    for(int i=0; i<refer.length(); ++i)
    {
        sum += code[i].code.length() * weight[i];
    }
    sum += 8 * refer.otherCharNum();
    cout << sum << endl;
    for(int i=0; i<refer.length(); ++i)
    cout<< refer.getWord(i).str << " "<< refer.getWord(i).number<<endl;

}