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
    void find(const int x) const;
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
 
void BinarySearchTree::find(const int x) const
{
    char p[100001] = "*";
    int count = 0;
    BinaryNode *t = root;
    while (t != NULL)
    {
        if (t->data == x) 
        { 
            p[++count]='\0';
            printf("%s\n",p); 
            return;
        }
        else if (t->data > x)
        {
            p[++count] = 'l';
            t = t->left;
        }
        else
        {
            p[++count] = 'r';
            t = t->right;
        }
    }
    printf("Nothing.\n");
}

int main()
{
    BinarySearchTree a;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        char quota;
        int x;
        scanf("\n%c %d", &quota, &x);
        if(quota == '+') a.insert(x);
        else if(quota == '-') a.remove(x);
        else a.find(x);
    }
    return 0;
}