#include <iostream>
#include <vector>

using namespace std;

class number
{
private:
    int num;
    bool flag;

public:
    number()
    {
        num = 0;
        flag = true;
    }

    ~number()
    {}

    void clear()
    {
        num = 0;
        flag = true;
    }

    void input(char a)
    {
        num = num * 10 + (a - '0');
        flag = false;
    }

    int output()
    {return num;}

    bool isEmpty()
    {return flag;}
};

class seqList
{
private:
    int *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        int *tmp = data;
        maxSize *= 2;
        data = new int[maxSize];
        for (int i = 0; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new int[initSize];
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

    int visit(int i)
    {
        return data[i];
    }

    void insert(const int &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    void remove(int i)
    {
        for (int j = i; j < currentLength - 1; j++)
            data[j] = data[j + 1];
        --currentLength;
    }

    void change(int i, int num)
    {data[i] = num;}

    void traverse()
    {
        for(int i=0; i<currentLength; ++i)
        cout << data[i] <<" ";
        cout <<endl;
    }
};

class GraphSort
{
private:
    struct DataNode
    {
        int size;
        int weight;
        DataNode(int n = 0, int w = 0)
        {
            size = n;
            weight = w;
        }
    };
    DataNode *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        DataNode *tmp = data;
        maxSize *= 2;
        data = new DataNode[maxSize];
        for (int i = 0; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    GraphSort(int initSize = 10)
    {
        data = new DataNode[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~GraphSort()
    {
        delete[] data;
    }

    int length()
    {
        return currentLength;
    }

    int weight(int i)
    {return data[i].weight;}

    int size(int i)
    {return data[i].size;}

    void insert(const int &x, const int &y)//x为weight,y为size
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength].weight = x;
        data[currentLength].size = y;
        ++currentLength;
    }

    void sort()
    {
        DataNode tmp;
        for(int i=0; i<currentLength; ++i)
        {
            bool flag =false;
            for(int j=0; j<currentLength-i-1; ++j)
            {
                if(data[j].weight > data[j+1].weight ||(data[j].weight == data[j+1].weight && data[j].size > data[j+1].size))
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

    void traverse()
    {
        for(int i=0; i<currentLength; ++i)
        {
            cout << data[i].weight<<" "<<data[i].size<<endl;
        }
    }
};


class adjListGraph//无向图邻接表
{
private:
    struct edgeNode//权值weight此处均为1
    {
        int end;
        edgeNode *next;

        edgeNode(int e, edgeNode *n = NULL)
        {
            end = e;
            next = n;
        }
    };

    struct verNode//若该结点在输入中未出现过，ver为-1,index即对应结点编号
    {
        int ver;
        edgeNode *head;

        verNode(edgeNode *h = NULL){head = h;}
    };
    
    int Vers, Edges;//最大结点的编号，边数
    verNode *verList;
    
    
    seqList rootNode;

public:
    adjListGraph(){}

    void setGraph(string str)
    {
        int i;
        number tmp;
        int maxNumber = 0;
        for(int i=0; str[i]!='\0'; ++i)//计算最大下标
        {
            if(str[i] <= '9' && str[i] >='0')
            tmp.input(str[i]);
            else
            {
                if(!tmp.isEmpty())
                {
                    if(tmp.output() > maxNumber)
                    maxNumber = tmp.output();
                    tmp.clear();
                }
                continue;
            }
        }
        Vers = maxNumber + 1;
        verList = new verNode[Vers];
        for(int i=0; i<Vers; ++i)
        verList[i].ver = -1;

//正式输入
        int node1 = -1, node2 = -1;
        bool isFirst = true, isEdge = false;
        for(int i=0; str[i]!='\0'; ++i)
        {
            if(isEdge)
            {
                if(str[i] >= '0' && str[i] <= '9')
                tmp.input(str[i]);
                if(str[i] == ' ')
                {
                    node1 = tmp.output();
                    tmp.clear();
                    isFirst = false;
                }
                if(str[i] == '>')
                {
                    if(tmp.isEmpty())
                    {
                        isEdge = false;
                        continue;
                    }
                    if(isFirst)
                    {
                        node1 = tmp.output();
                        tmp.clear();
                        verList[node1].ver = node1;
                        rootNode.insert(node1);
                        isEdge = false;
                        node1 = -1;
                    }
                    else
                    {
                        node2 = tmp.output();
                        tmp.clear();
                        verList[node1].ver = node1;
                        verList[node2].ver = node2;
                        insert(node1, node2);
                        node1 = -1;
                        node2 = -1;
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

    void insert(int x, int y)//加边（无向边）
    {
        int u = x, v = y;
        verList[u].head = new edgeNode(v, verList[u].head);
        verList[v].head = new edgeNode(u, verList[v].head);
        ++Edges;
    }

    void remove(int x, int y)
    {
        int u = x, v= y;
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

    bool exist(int x, int y) const
    {
        int u = x, v = y;
        edgeNode *p = verList[u].head;

        while(p!=NULL && p->end != v)
        p = p->next;
        if(p == NULL) return false;
        else return true;
    }

    ~adjListGraph()
    {
        int i;
        edgeNode *p;
        for(i=0; i<Vers; ++i)
        while((p = verList[i].head) != NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
        delete []verList;
    }

//v为根节点下标，countOfVer为结点计数，countOfEdge为边计数（度，一条边计入两次），visited判断是否访问过了
//isTree的内部递归函数
    void dfs(int v, int &countOfVer, int &countOfEdge, vector<int> &visited) const
    {
        visited[v] = true;
        countOfVer++;
        for(edgeNode *tmp = verList[v].head; tmp != NULL ; tmp = tmp->next)
        {
            countOfEdge++;
            if(!visited[tmp->end])
                dfs(tmp->end, countOfVer, countOfEdge, visited);
        }
    }

    bool isTree(int v)//v为根结点编号
    {
        vector<int> visited(Vers, false);
        int countOfVer = 0;
        int countOfEdge = 0;
        dfs(v, countOfVer, countOfEdge, visited);
        if((countOfVer - 1) * 2 == countOfEdge) return true;
        else return false;
    }

    bool isBinaryTree(int v)//在判断为树的基础上
    {
        vector<int> visited(Vers, false);
        edgeNode *tmp = verList[v].head;
        int cnt = 0;
        while(tmp != NULL)
        {
            ++cnt;
            tmp = tmp->next;
        }
        if(cnt > 2) return false;
        else tmp = verList[v].head;
        return isBinaryNode(v, visited);
    }

    bool isBinaryNode(int v, vector<int> &visited)//isBinaryTree的内部递归函数
    {
        if(visited[v] != false) return true;
        visited[v] = true;
        edgeNode *tmp = verList[v].head;
        int cnt = 0;
        while(tmp != NULL)
        {
            ++cnt;
            tmp = tmp->next;
        }
        if(cnt > 3) return false;

        edgeNode *tmp2 = verList[v].head;
        while(tmp2 != NULL)
        {
            if(!isBinaryNode(tmp2->end, visited)) return false;
            tmp2 = tmp2->next;
        }
        return true;
    }

    void labelNode(int v, int &size, int &weight, seqList &printed, vector<int> &visited)
    {
        visited[v] = true;
        size++;
        weight += v;
        printed.change(v, 1);
        for(edgeNode *tmp = verList[v].head; tmp != NULL ; tmp = tmp->next)
        {
            if(!visited[tmp->end])
            {
                labelNode(tmp->end, size, weight, printed, visited);
            }
                
        }
    }

    void getSizeAndWeight(int v, int &size, int &weight, seqList &printed)
    {
        vector<int> visited(Vers, false);
        labelNode(v, size, weight, printed, visited);
    }

    void judgeAndPrintGraph()
    {
        seqList printed;
        for(int i=0; i<Vers; ++i)
        {
            if(verList[i].ver != -1)
            printed.insert(0);
            else printed.insert(-1);
        }

        GraphSort Graph;
        GraphSort Tree;
        GraphSort BinaryTree;
        GraphSort Node;
        int size = 0, weight = 0;
        for(int i=0; i<rootNode.length(); ++i)//根结点处理
        {
            if(printed.visit(rootNode.visit(i)) == 1)
            continue;
            if(verList[rootNode.visit(i)].head == NULL)
            {
                printed.change(rootNode.visit(i), 1);
                Node.insert(rootNode.visit(i), 1);
            }
            else if(!isTree(rootNode.visit(i)))
            {
                getSizeAndWeight(rootNode.visit(i), size, weight, printed);
                Graph.insert(weight, size);
                weight = 0;
                size = 0;
            }
            else if(!isBinaryTree(rootNode.visit(i)))
                {
                    getSizeAndWeight(rootNode.visit(i), size, weight, printed);
                    Tree.insert(weight, size);
                    weight = 0;
                    size = 0;
                }
                else
                {
                    getSizeAndWeight(rootNode.visit(i), size, weight, printed);
                    BinaryTree.insert(weight, size);
                    weight = 0;
                    size = 0;
                }
            
        }
        for(int i=0; i<Vers; ++i)//若还有子图
            {
                if(printed.visit(i) == 0)
                {
                    if(verList[i].head == NULL)
                    {
                        printed.change(i, 1);
                        Node.insert(i, 1);
                    }
                    else if(!isTree(i))
                    {
                    getSizeAndWeight(i, size, weight, printed);
                    Graph.insert(weight, size);
                    weight = 0;
                    size = 0;
                    }
                    else if(!isBinaryTree(i))
                    {
                        getSizeAndWeight(i, size, weight, printed);
                        Tree.insert(weight, size);
                        weight = 0;
                        size = 0;
                    }
                    else
                    {
                        getSizeAndWeight(i, size, weight, printed);
                        BinaryTree.insert(weight, size);
                        weight = 0;
                        size = 0;
                    }
                }
            }
            Graph.sort();
            Tree.sort();
            BinaryTree.sort();
            Node.sort();
            
            int sum = Graph.length() + Tree.length() + BinaryTree.length() + Node.length();
            cout << "We have recognized " << sum;
            if(sum == 1) cout << " graph."<< endl;
            else if(sum != 0)cout << " graphs." << endl;
                else
                {
                    cout << " graph." << endl;
                    return;
                }
            for(int i=0; i<Node.length(); ++i)
            {
                cout << "--Node. Weight: " << Node.weight(i) << ". Size: " << Node.size(i) << "." << endl;
            }
            for(int i=0; i<BinaryTree.length(); ++i)
            {
                cout << "--Binary tree. Weight: " << BinaryTree.weight(i) << ". Size: " << BinaryTree.size(i) << "." << endl;
            }
            for(int i=0; i<Tree.length(); ++i)
            {
                cout << "--Tree. Weight: " << Tree.weight(i) << ". Size: " << Tree.size(i) << "." << endl;
            }
            for(int i=0; i<Graph.length(); ++i)
            {
                cout << "--Graph. Weight: " << Graph.weight(i) << ". Size: " << Graph.size(i) << "." << endl;
            }
    }

    void traverse()
    {
        rootNode.traverse();
        for(int i=0; i<Vers; ++i)
        {
            if(verList[i].ver == -1)
            {
                cout << i <<"=-1"<<endl;
                continue;
            }
            cout << i;
            edgeNode *tmp = verList[i].head;
            while(tmp != NULL)
            {
                cout << "->" << tmp->end;
                tmp = tmp->next;
            }
            cout <<endl;
        }
    }
};

int main()
{
    string str;
    getline(cin, str);
    adjListGraph a;
    a.setGraph(str);
    a.judgeAndPrintGraph();
    return 0;
}
