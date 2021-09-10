#include<iostream>
using namespace std;

class BinarySearchTree
{
private:
    struct BinaryNode
    {
        int data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const int thedata,BinaryNode *lt=NULL,
                   BinaryNode *rt=NULL)
                :data(thedata),left(lt),right(rt){}
    };
    BinaryNode *root;

public:
    BinarySearchTree(){root = NULL;}
    ~BinarySearchTree(){makeEmpty(root);}
    int find(const int x) const;
    void insert(const int x);
    void remove(const int x);

private:
    void makeEmpty(BinaryNode *t)
    {
        if(t==NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
};

void BinarySearchTree::remove(const int x)
{
    BinaryNode *parent = NULL,*t = root;
    int flag = 0;
    while(t && t->data != x)
    {
        if(t->data > x) 
        {
            parent = t;
            t = t->left;
            flag = 0;
        }
        else 
        {
            parent = t;
            t = t->right;
            flag = 1;
        }
    }
    if(!t) return;
    if(t->right)
    {
        BinaryNode *tmp = t->right;
        if(!tmp->left)
        {
            t->data = tmp->data;
            t->right = tmp->right;
            delete tmp;
        }
        else
        {
            while(tmp->left) 
            {
                parent = tmp;
                tmp = tmp->left;
            }
            t->data = tmp->data;
            parent->left = tmp->right;
            delete tmp;
        }
    }
    else
    {
        if(!parent) 
        {
            BinaryNode *tmp = root;
            root = root->left;
            delete tmp;
        }
        else if(flag) 
            {
                parent->right = t->left;
                delete t;
            }
        else 
        {
            parent->left = t->left;
            delete t;
        }
    }
}

void BinarySearchTree::insert(const int x)
{
    int flag;
    BinaryNode *t = root;
    BinaryNode *parent = NULL;
    if(!t) {root = new BinaryNode(x,NULL,NULL); return;}
    while(t)
    {
        if(x < t->data) 
        {
            parent = t;
            t = t->left;
            flag = 0;
        }
        else if(x > t->data) 
        {
            parent = t;
            t = t->right;
            flag = 1;
        }
        else return;
    }
    ((flag)? parent->right:parent->left) = new BinaryNode(x,NULL,NULL);
}

int BinarySearchTree::find(const int x) const
    {
        BinaryNode *parent, *tmp = root;
        int lh, rh;
        int l, h;
        bool lflag = false, rflag = false;
        while(tmp != NULL)
        {
            if (x > tmp->data)
            {
                while (tmp && x > tmp->data)
                {
                    parent = tmp;
                    tmp = tmp->right;
                }
                lh = parent->data;
                lflag = true;
            }
            else if(x < tmp->data)
            {
                while (tmp && x < tmp->data)
                {
                    parent = tmp;
                    tmp = tmp->left;
                }    
                rh = parent->data;
                rflag = true;
            }
            else return 0;
        }
        if (lflag && rflag) return ((x - lh) < (rh - x) ? x - lh : rh - x);
        if (lflag) return (x - lh);
        if (rflag) return (rh - x);
        return -1;
    }

int main()
{
    BinarySearchTree a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int quota;
        int x;
        cin >> quota >> x;
        if(quota == 1) a.insert(x);
        else if(quota == 2) a.remove(x);
        else printf("%d\n", a.find(x))  ;
    }
    return 0;
}