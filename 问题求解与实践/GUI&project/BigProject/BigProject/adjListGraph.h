#ifndef ADJLISTGRAPH_GUARD
#define ADJLISTGRAPH_GUARD

#include <iostream>
#include <vector>

using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode* next;

        edgeNode(int e, TypeOfEdge w, edgeNode* n = NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
    };

    struct verNode
    {
        TypeOfVer ver;
        edgeNode* head;

        verNode(edgeNode* h = NULL) { head = h; }
    };

private:
    int Vers, Edges;//最大结点的编号，边数
    verNode* verList;
    int find(TypeOfVer v)const
    {
        for (int i = 0; i < Vers; ++i)
            if (verList[i].ver == v) return i;
    }

public:
    adjListGraph(int vSize, const TypeOfVer d[])
    {
        Vers = vSize;
        verList = new verNode[vSize];
        for (int i = 0; i < Vers; ++i)
            verList[i].ver = d[i];
    }

    adjListGraph(int vSize, const vector<TypeOfVer> d)
    {
        Vers = vSize;
        verList = new verNode[vSize];
        for (int i = 0; i < Vers; ++i)
            verList[i].ver = d[i];
    }

    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
    {
        int u = find(x), v = find(y);
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++Edges;
    }

    void remove(TypeOfVer x, TypeOfVer y)
    {
        int u = find(x), v = find(y);
        edgeNode* p = verList[u].head, * q;
        if (p == NULL) return;

        if (p->end == v)
        {
            verList[u].head = p->next;
            delete p;
            --Edges;
            return;
        }
        while (p->next != NULL && p->next->end != v)
            p = p->next;
        if (p->next != NULL)
        {
            q = p->next;
            p->next = q->next;
            delete q;
            --Edges;
        }
    }

    bool exist(TypeOfVer x, TypeOfVer y) const
    {
        int u = find(x), v = find(y);
        edgeNode* p = verList[u].head;

        while (p != NULL && p->end != v)
            p = p->next;
        if (p == NULL) return false;
        else return true;
    }

    void traverse() const
    {
        for (int i = 0; i < Vers; ++i)
        {
            cout << verList[i].ver << ':' << endl;
            edgeNode *tmp = verList[i].head;
            while (tmp != NULL)
            {
                cout << verList[tmp->end].ver << "," << tmp->weight<<" ";
                tmp = tmp->next;
            }
            cout << endl;
        }
    }

    int verLength()
    {
        return Vers;
    }

    verNode ListNode(int i)
    {
        return verList[i];
    }

    ~adjListGraph()
    {
        int i;
        edgeNode* p;
        for (i = 0; i < Vers; ++i)
            while ((p = verList[i].head) != NULL)
            {
                verList[i].head = p->next;
                delete p;
            }
        delete[]verList;
    }

    vector<TypeOfVer> dfs(int start) const
    {
        bool* visited = new bool[Vers];
        for (int i = 0; i < Vers; ++i)
            visited[i] = false;
        vector<TypeOfVer> result = dfs(start, visited);       
        return result;
    }

    //返回值为最短路径的权重和
    //result为记录的最短路径
    TypeOfEdge dijkstra(TypeOfVer start,TypeOfVer finish,TypeOfEdge noEdge, vector<TypeOfVer>& result) const
    {
        TypeOfEdge* distance = new TypeOfEdge[Vers];
        int* prev = new int[Vers];
        bool* known = new bool[Vers];
        for (int i = 0; i < Vers; ++i)
        {
            known[i] = false;
            distance[i] = noEdge;
        }

        int u, sNo, i, j;
        edgeNode* tmp;
        TypeOfEdge min;
        
        sNo = find(start);
        distance[sNo] = 0;
        prev[sNo] = sNo;

        for (i = 1; i < Vers; ++i)
        {
            min = noEdge;
            for (j = 0; j < Vers; ++j)
            {
                if (!known[j] && distance[j] < min)
                {
                        min = distance[j];
                        u = j;
                }
            }
            known[u] = true;
            for (tmp = verList[u].head; tmp != NULL; tmp = tmp->next)
            {
                if (!known[tmp->end] && distance[tmp->end] > min + tmp->weight)
                {
                    distance[tmp->end] = min + tmp->weight;
                    prev[tmp->end] = u;
                }
            }
        }
        
        //输出路径信息
        int endNum = find(finish);
        double minDistance = distance[endNum];
        
        result = printPath(sNo, endNum, prev);
        
        delete[]distance;
        delete[]prev;
        delete[]known;
        return minDistance;
    }
private:
    vector<TypeOfVer> dfs(int start, bool visited[]) const
    {
        vector<TypeOfVer> result;
        edgeNode* p = verList[start].head;
        result.push_back(verList[start].ver);
        visited[start] = true;
        while (p != NULL)
        {
            if (visited[p->end] == false)
            {
                vector<TypeOfVer> tmp = dfs(p->end, visited);
                for (int i = 0; i < tmp.size(); ++i)
                    result.push_back(tmp[i]);
            }
            p = p->next;
        }
        return result;
    }

    vector<TypeOfVer> printPath(int start, int end, int prev[]) const
    {
        vector<TypeOfVer> result;
        if (start == end)
        {
            result.push_back(verList[start].ver);
            return result;
        }
        vector<TypeOfVer> tmp = printPath(start, prev[end], prev);
        for (int i = 0; i < tmp.size(); ++i)
            result.push_back(tmp[i]);
        result.push_back(verList[end].ver);
        return result;
    }
};



#endif // !ADJLISTGRAPH_GUARD