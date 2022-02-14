#include <iostream>
#include <vector>
#include <string>

using namespace std;

class seqList
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
        for (int i = 0; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new char[initSize];
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

    char visit(int i)
    {
        return data[i];
    }

    void insert(const char &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    bool compare(const char &x)
    {
        for(int i=0; i<currentLength; ++i)
        if(data[i] == x) return true;
        return false;
    }

    void traverse()
    {
        for(int i=0; i<currentLength; ++i)
        cout << data[i] <<" ";
        cout <<endl;
    }
};

class stringList
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

public:
    stringList(int initSize = 10)
    {
        data = new string[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~stringList()
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

    void insert(const string &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    void sort()
    {
        string tmp;
        for(int i=0; i<currentLength; ++i)
        {
            bool flag =false;
            for(int j=0; j<currentLength-i-1; ++j)
            {
                if(data[j].length() < data[j+1].length() || (data[j].length() == data[j+1].length() && data[j].compare(data[j+1]) < 0))
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
    
};

class adjListGraph
{
private:
    struct edgeNode
    {
        char end;
        edgeNode *next;

        edgeNode(char e, edgeNode *n = NULL)
        {
            end = e;
            next = n;
        }
    };

    struct verNode
    {
        char ver;
        string AHRcode;
        edgeNode *head;

        verNode(edgeNode *h = NULL){head = h;}
    };
    
    int Vers, Edges;//结点数，边数
    verNode *verList;
    char *parent;//对应结点的父亲
    int find(char v)const
    {
        for(int i=0; i< Vers; ++i)
        if(verList[i].ver == v) 
        return i;
        return -1;
    }

public:
    adjListGraph(int vSize, seqList Node)
    {
        Vers = vSize;
        verList = new verNode[vSize];
        parent = new char[vSize];
        for(int i=0; i<Vers; ++i)
        {
            verList[i].ver = Node.visit(i);
            parent[i] = ' ';
        }    
    }

    void setGraph(string str)
    {
        bool isEdge = false;
        bool isFirst = true;
        char tmp1=' ', tmp2=' ';
        for(int i=0; str[i] != '\0'; ++i)
        {
            if(isEdge)
            {
                if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >='A' && str[i] <= 'Z'))
                {
                    if(isFirst) 
                    {
                        tmp1 = str[i];
                        isFirst = false;
                    }
                    else tmp2 = str[i];
                }
                if(str[i] == ' ')
                continue;
                if(str[i] == '>')
                {
                    if(tmp1 == ' ' && tmp2 == ' ')
                    {
                        isEdge = false;
                        continue;
                    }
                    if(isFirst)
                    {
                        parent[find(tmp1)] = ' ';
                        isEdge = false;
                        continue;
                    }
                    else
                    {
                        insert(tmp2, tmp1);
                        parent[find(tmp1)] = tmp2;
                        tmp1 = ' ';
                        tmp2 = ' ';
                        isEdge = false;
                        isFirst = true;
                    }
                }
            }
            else if(str[i] == '<')
                {
                    isEdge = true;
                    continue;
                }
                else if(str[i] == ' ')
                    continue;
        }
    }

    void insert(char x, char y)
    {
        int u = find(x), v = find(y);
        verList[u].head = new edgeNode(y, verList[u].head);
        ++Edges;
    }

    void remove(char x, char y)
    {
        int u = find(x), v= find(y);
        edgeNode *p = verList[u].head, *q;
        if(p == NULL) return;

        if(p->end == v)
        {
            verList[u].head = p->next;
            delete p;
            --Edges;
            return;
        }
        while(p->next != NULL && p->next->end != v)
        p = p->next;
        if(p->next != NULL)
        {
            q = p->next;
            p->next = q->next;
            delete q;
            --Edges;
        }    
    }

    bool exist(char x, char y) const
    {
        int u = find(x), v = find(y);
        edgeNode *p = verList[u].head;

        while(p!=NULL && p->end != v)
        p = p->next;
        if(p == NULL) return false;
        else return true;
    }

    int height()
    {
        char tmp;
        int height = 0;
        int tmp1 = 0;
        for(int i=0; i < Vers; ++i)
        {
            if(verList[i].head == NULL)
            {
                tmp = verList[i].ver;
                while(tmp != ' ')
                {
                    tmp1++;
                    tmp = parent[find(tmp)];
                }
                if(height < tmp1)
                height = tmp1;
                tmp1 = 0;
            }
            
        }
        return height;
    }

    int height(char x)
    {
        int height = 0;
        char tmp = x;
        while(tmp != ' ')
        {
            height++;
            tmp = parent[find(tmp)];
        }
        return height;
    }

    string AHRcode()
    {
        for(int i=0; i < Vers; ++i)//对叶子结点编码
        {
            if(verList[i].head == NULL)
                verList[i].AHRcode = "10";
        }

        for(int i=1; i < height(); ++i)//一层层处理
        {
            seqList tmp;
            stringList reference;
            for(int j=0; j < Vers; ++j)//输入第height() - i层结点
            {
                if(height(verList[j].ver) == height() - i)
                if(!tmp.compare(verList[j].ver))
                {
                    tmp.insert(verList[j].ver);
                }
            }
            for(int j=0; j<tmp.length(); ++j)
            {
                if(verList[find(tmp.visit(j))].head == NULL)
                {
                    continue;
                }
                string tmp2 = "1";//记录这个节点的AHRcode
                edgeNode *tmp1 = verList[find(tmp.visit(j))].head;//用于循环迭代
                while(tmp1 != NULL)
                {
                    reference.insert(verList[find(tmp1->end)].AHRcode);
                    tmp1 = tmp1->next;
                }
                reference.sort();
                
                for(int k=0; k < reference.length(); ++k)
                {
                    tmp2 += reference.visit(k);
                }
                tmp2 += '0';
                verList[find(tmp.visit(j))].AHRcode = tmp2;
                reference.clear();
            }
            tmp.clear();
        }
        int m;
        for(m=0; m < Vers; ++m)
        {
            if(parent[m] == ' ')
            break;
        }
        return verList[m].AHRcode;
    }

    void traverse()
    {
        cout <<Vers;
        for(int i=0; i<Vers; ++i)
        {
            cout << verList[i].ver;
            edgeNode *tmp = verList[i].head;
            while(tmp != NULL)
            {
                cout << "->" << tmp->end;
                tmp = tmp->next;
            }
            cout <<endl;
        }
        for(int i=0; i<Vers; ++i)
        {
            cout << verList[i].ver <<"<-"<<parent[i]<<endl;
        }
    }

    ~adjListGraph()
    {
        int i;
        edgeNode *p;
        for(i=0; i<Vers; ++i)
        {
            while((p = verList[i].head) != NULL)
            {
                verList[i].head = p->next;
                delete p;
            }
        }
        delete []parent;
        delete []verList;//无法delete
    }
};

void getVerNode(string &str, int &Vers, seqList &Node)//初步识别输入树的结点数与符号
{
    for(int i=0; str[i]!='\0'; ++i)
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >='A' && str[i] <= 'Z'))
        {
            
            if(!Node.compare(str[i]))
            {
                Node.insert(str[i]);
            }
            
        }
    }

    Vers = Node.length();
}

int main()
{
    string str1;
    string str2;
    getline(cin, str1);
    getline(cin, str2);
    int Vers1 = 0, Vers2 = 0;
    seqList Node1, Node2;
    
    getVerNode(str1, Vers1, Node1);
    adjListGraph a(Vers1, Node1);
    a.setGraph(str1);
    a.AHRcode();
    getVerNode(str2, Vers2, Node2);
    adjListGraph b(Vers2, Node2);
    b.setGraph(str2);

    cout << a.height()<<" " << b.height() << endl;
    cout << a.AHRcode() << " " << b.AHRcode() <<endl;
    if(a.AHRcode().compare(b.AHRcode()) == 0)
    cout <<"Yes" << endl;
    else cout << "No" << endl;
    
    
}