#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class binaryTree
{
private:
    struct Node{
        Node *leftchild, *rightbrother;
        int number;
        int data;

        Node ():leftchild(NULL), rightbrother(NULL){}
        Node(int x, int item, Node *L = NULL, Node *R = NULL):number(x), data(item), leftchild(L),rightbrother(R){}
        ~Node (){}
    };
    struct StNode
    {
        Node *node;
        int TimesPop;

        StNode(Node *N = NULL):node(N), TimesPop(0) {}
    };
    Node *root;
    
public:
    binaryTree(): root(NULL){}
    binaryTree(int a, int x){ root = new Node(a, x);}
    ~binaryTree()
    { clear(root); }
    void preOrder() const
    {
        stack<Node *> s;
        Node *current;

        s.push(root);
        while (!s.empty())
        {
            current = s.top();
            s.pop();
            cout << current->data <<" ";
            if (current->rightbrother != NULL) s.push(current->rightbrother);
            if (current->leftchild != NULL) s.push(current->leftchild);
        }
        cout << endl;
    }
    void postOrder() const
    {
        stack<StNode> s;
        StNode current(root);

        s.push(current);
        while (!s.empty())
        {
            current = s.top();
            s.pop();
            if (++current.TimesPop == 2)
            {
                cout << current.node->data << " ";
                if (current.node->rightbrother != NULL)
                s.push(StNode(current.node->rightbrother));
            }
            else
            {
                s.push(current);
                if (current.node->leftchild != NULL)
                    s.push(StNode(current.node->leftchild));
            }
        }
        cout << endl;
    }
    void levelOrder() const
    {
        queue<Node *> brother, child;
        Node *tmp;

        child.push(root);
        
        while (!child.empty())
        {
            tmp = child.front();
            child.pop();
            cout << tmp->data <<" ";
            if (tmp->leftchild) child.push(tmp->leftchild);
            if (tmp->rightbrother) brother.push(tmp->rightbrother);
            while (!brother.empty())
            {
                tmp = brother.front();
                brother.pop();
                cout << tmp->data <<" ";
                if (tmp->leftchild) child.push(tmp->leftchild);
                if (tmp->rightbrother) brother.push(tmp->rightbrother);
            }
        }
        cout << endl;
    }
    void createTree(int rootNumber, int ldata[], int rdata[], int value[])
    {
        queue<Node *> que;
        Node *tmp;
        root = new Node(rootNumber, value[rootNumber]);
        que.push(root);
        while(!que.empty())
        {
            tmp = que.front();
            que.pop();
            if (ldata[tmp->number] != 0) que.push(tmp->leftchild = new Node(ldata[tmp->number] - 1, value[ldata[tmp->number] - 1]));
            if (rdata[tmp->number] != 0) que.push(tmp->rightbrother = new Node(rdata[tmp->number] - 1, value[rdata[tmp->number] - 1]));
        }
    }
private:
    void clear(Node *&t)
    {
        if (t == NULL) return;
        clear(t->leftchild);
        clear(t->rightbrother);
        delete t;
        t = NULL;
    }
};

int main()
{
    int n, rootNumber, *ldata, *rdata, *value, *findRoot;
    binaryTree f;
    cin >> n;
    ldata = new int[n];
    rdata = new int[n];
    value = new int[n];
    findRoot = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ldata[i] >> rdata[i] >> value[i];
        findRoot[i] = 0;
    }
    //找出根节点；
    for (int i = 0; i < n; i++)
    {
        if (ldata[i] != 0) findRoot[ldata[i]-1] = -1;
        if (rdata[i] != 0) findRoot[rdata[i]-1] = -1;
    }
    for (int i = 0; i < n; i++)
        if (findRoot[i] == 0) {rootNumber = i; break;}
    
    f.createTree(rootNumber, ldata, rdata, value);
    f.preOrder();
    f.postOrder();
    f.levelOrder();

    delete []ldata;
    delete []rdata;
    delete []findRoot;
    delete []value;
}