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

        Node ():left(NULL), right(NULL){}
        Node(int item, Node *L = NULL, Node *R = NULL):data(item), left(L),right(R){}
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
    void postOrder() const
    {
        stack<StNode> s;
        StNode current(root);

        s.push(current);
        while (!s.empty())
        {
            current = s.top();
            s.pop();
            if (++current.TimesPop == 3)
            {
                cout << current.node->data << " ";
                continue;
            }
            s.push(current);
            if (current.TimesPop == 1)
            {
                if (current.node->left != NULL)
                s.push(StNode(current.node->left));
            }
            else
            {
                if (current.node->right != NULL)
                    s.push(StNode(current.node->right));
            }
        }
    }
    void createTree(int n, int *num, int flag)
    {
        queue<Node *> que;
        Node *tmp;
        int x, ldata, rdata, parent;
        int i, cnt = 1;
        for(i=0; i<n; ++i)
        {
            if(root == NULL)
            {
                root = new Node(num[3*i]);
                que.push(root);
            }
            tmp = que.front();
            que.pop();
            
            if (num[3*i+1] != flag) 
            {
                tmp->right = new Node(num[3*i+1]);
                if (cnt < n && num[3*cnt] == num[3*i+1])
                {
                    que.push(tmp->right);
                    ++cnt;
                }
            }
            if (num[3*i+2] != flag) 
            {
                tmp->left = new Node(num[3*i+2]);
                if (cnt < n && num[3*cnt] == num[3*i+2])
                {
                    que.push(tmp->left);
                    ++cnt;
                }
            }
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
    
    int n, *num;
    int i;
    cin >> n;
    num = new int[3*n];
    for(i=0; i<n; ++i)
        cin >> num[3*i] >> num[3*i+1] >>num[3*i+2];
    binaryTree a;
    a.createTree(n, num, -1);
    a.postOrder();
    delete []num;
    return 0;
}