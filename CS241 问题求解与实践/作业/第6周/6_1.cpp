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

void readString(string str, int ASCII[])
{
    for(int i=0; i<128; ++i)//初始化
        {
            ASCII[i] = 0;
        }
        
    int cnt = 0;
    while(getline(cin, str))
    {
        for(int i=0; str[i]!='\0'; ++i)
        {
            ++ASCII[int(str[i])];
        }
        ++cnt;
    }    
    ASCII[13] = cnt - 1;//检测回车数量
}

int main()
{
    int ASCII[128];
    for(int i=0; i<128; ++i)
        ASCII[i] = 0;
    char token[128]={};
    string str;
    readString(str,ASCII);

    //去掉频率为0的字符
    int currentLength = 128; 
    for(int i=0; i<128; ++i)
    {
        if(ASCII[i] == 0)
        --currentLength;
    }
    int frequency[currentLength], cnt = 0;
    for(int i=0; i<128; ++i)
    {
        if(ASCII[i] == 0)
        continue;
        else 
        {
            frequency[cnt] = ASCII[i];
            ++cnt;
        }
    }

    hfTree::hfCode code[currentLength];//计数并输出
    char refer[currentLength]={};
    hfTree tmp(refer, frequency, currentLength);
    tmp.getCode(code);
    int sum = 0;
    for(int i=0; i<currentLength; ++i)
    {
        sum += code[i].code.length() * frequency[i];
    }
    cout << sum << endl;

}