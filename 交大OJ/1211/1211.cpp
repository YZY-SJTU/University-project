#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class binaryTree
{
private:
    struct Node{
        Node *left, *right;
        int number;
        Node(int num, Node *L = NULL, Node *R = NULL):number(num), left(L),right(R){}
        ~Node (){}
    };
    Node *root;
public:
    binaryTree(): root(NULL){}
    binaryTree(int x){ root = new Node(x);}
    ~binaryTree()
    { clear(root); }
    void clear()
    { clear(root); }
    bool levelOrder(int sum) const
    {
        queue<Node *> que;
        Node *tmp;
        int cnt = 1;
        que.push(root);
        
        while (!que.empty())
        {
            tmp = que.front();
            que.pop();
            if (tmp->left) 
            {
                que.push(tmp->left);
                ++cnt;
            }
            else if (cnt == sum) return true;
                else return false;
            if (tmp->right) 
            {
                que.push(tmp->right);
                ++cnt;
            }
            else if(cnt == sum) return true;
                else return false;
        }
        return true;
    }
    void createTree(int rootNumber, int ldata[], int rdata[])
    {
        queue<Node *> que;
        Node *tmp;
        root = new Node(rootNumber);
        que.push(root);

        while(!que.empty())
        {
            tmp = que.front();
            que.pop();
            if (ldata[tmp->number] != 0) que.push(tmp->left = new Node(ldata[tmp->number] - 1));
            if (rdata[tmp->number] != 0) que.push(tmp->right = new Node(rdata[tmp->number] - 1));
        }
    }
private:
    void clear(Node *&t)
    {
        if (t == NULL) return;
        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }
};



int main()
{
    int n, rootNumber, *ldata, *rdata, *findRoot;
    binaryTree f;
    cin >> n;
    ldata = new int[n];
    rdata = new int[n];
    findRoot = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ldata[i] >> rdata[i];
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
    f.createTree(rootNumber, ldata, rdata);
    if (f.levelOrder(n)) cout <<"Y";
    else cout <<"N";

    delete []ldata;
    delete []rdata;
    delete []findRoot;
}