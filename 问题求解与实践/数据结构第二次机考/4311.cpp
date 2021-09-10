#include <iostream>
#include <stack>
#include <queue>

using namespace std;


class binaryTree
{
private:
    struct Node{
        Node *left, *right;
        int data;
        int target;
        Node ():left(NULL), right(NULL){}
        Node(int item, Node *L = NULL, Node *R = NULL, int s = 0):data(item), left(L),right(R), target(s){}
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
    binaryTree(int x){ root = new Node(x);}
    ~binaryTree()
    { clear(root); }
    void clear()
    { clear(root); }
    bool isEmpty() const
    { return root == NULL;}
    
    int lchild(int x, int flag) const
    {
        Node *tmp = find(x, root);
        if (tmp == NULL || tmp->left == NULL) return flag;

        return tmp->left->data;
    }
    int rchild(int x, int flag) const
    {
        Node *tmp = find(x, root);
        if (tmp == NULL || tmp->right == NULL) return flag;

        return tmp->right->data;
    }

    void midOrder(int n) const
    {
        stack<StNode> s;
        StNode current(root);
        int mid[n];
        int cnt=0, index;
        int i;
        s.push(current);
        while (!s.empty())
        {
            current = s.top();
            s.pop();
            if (++current.TimesPop == 2)
            {
                mid[cnt] = current.node->data;
                ++cnt;
                if (current.node->right != NULL)
                s.push(StNode(current.node->right));
            }
            else
            {
                s.push(current);
                if (current.node->left != NULL)
                    s.push(StNode(current.node->left));
            }
        }
    
    }
    void createTree(int level[], int x)
    {
        queue<Node *> que;
        Node *tmp;
        int ldata, rdata;
        int cnt = 1;
        root = new Node(level[0]);
        que.push(root);

        while(!que.empty() && cnt < x-1)
        {
            tmp = que.front();
            que.pop();

            ldata = level[cnt];
            cout << ldata << " ";
            if (ldata != -1) que.push(tmp->left = new Node(ldata));
            ++cnt;
            if (cnt == x)
                break;

            rdata = level[cnt];
            cout << rdata << " ";
            if (rdata != -1) que.push(tmp->right = new Node(rdata));
            if (cnt == x)
                break;
        }
    }
    int parent(int x, int flag) const { return flag;}
private:
    Node *find(int x, Node *t) const
    {
        Node *tmp;
        if (t == NULL) return NULL;
        if (t->data == x) return t;
        if (tmp = find(x,t->left)) return tmp;
        else return find(x,t->right);
    }
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
    int n;
    cin >> n;
    int *number;
    number=new int[n];
    for(int i =0; i< n; ++i)
    cin >> number[i];
    binaryTree a;
    a.createTree(number, n);
}