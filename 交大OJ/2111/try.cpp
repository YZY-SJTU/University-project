#include <iostream>

using namespace std;

class AvlTree
{
private:
    struct AvlNode
    {
        int data;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const int & thedata, AvlNode *lt=NULL, AvlNode *rt=NULL, int h = 1):data(thedata), left(lt), right(rt), height(h){}
    };
    AvlNode *root;
    
public:
    AvlTree(){root = NULL;}
    ~AvlTree(){makeEmpty(root);}
    int find(const int & x) const
    {
        AvlNode *parent, *tmp = root;
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
    void insert(const int & x)
    {
        insert(x, root);
    }
    void remove(const int & x)
    {
        remove(x, root);
    }

private:
    void insert(const int & x, AvlNode * & t)
    {
        if (t ==NULL)
        t = new AvlNode(x, NULL, NULL);
        else if(x < t->data)
        {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
                if(x < t->left->data) LL(t); else LR(t);
        }
        else if (x > t->data)
        {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
                if(x > t->right->data) RR(t); else RL(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    bool remove(const int & x, AvlNode * & t)
    {
        if (t == NULL) return true;
        if (x == t->data)
        {
            if (t->left == NULL ||t->right == NULL)
            {
                AvlNode *oldNode = t;
                t = (t->left != NULL) ? t->left : t->right;
                delete oldNode;
                return false;
            }
            else
            {
                AvlNode *tmp = t->right;
                while(tmp->left != NULL) tmp = tmp->left;
                t->data = tmp->data;
                if (remove(tmp->data, t->right)) return true;
                return adjust(t, 1);
            }
        }
        if (x < t->data)
        {
            if (remove(x, t->left)) return true;
                return adjust(t, 0);
        }
        else
        {
            if (remove(x, t->right)) return true;
                return adjust(t, 1);
        }
    }
    void makeEmpty(AvlNode * & t)
    {
        if (t == NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    int height(AvlNode *t) const {return t == NULL ? 0 : t->height;}
    void LL(AvlNode * & t)
    {
        AvlNode *t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        t1->height = max(height(t1->left), height(t)) + 1;
        t = t1;
    }
    void LR(AvlNode * & t)
    {
        RR(t->left);
        LL(t);
    }
    void RL(AvlNode * & t)
    {
        LL(t->right);
        RR(t);
    }
    void RR(AvlNode * & t)
    {
        AvlNode *t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        t1->height = max(height(t1->right), height(t)) + 1;
        t = t1;
    }
    int max(int a, int b){return (a>b)? a: b;}
    bool adjust(AvlNode * & t, int subTree)
    {
        if(subTree)
        {
            if (height(t->left) - height(t->right) == 1) return true;
            if (height(t->right) == height(t->left)) {--t->height; return false;}
            if (height(t->left->right) > height(t->left->left))
            {
                LR(t);
                return false;
            }
            LL(t);
            if (height(t->right) == height(t->left)) return false;
            else return true;
        }
        else
        {
            if (height(t->right) - height(t->left) == 1) return true;
            if (height(t->right) == height(t->left)) {--t->height; return false;}
            if (height(t->right->left) > height(t->right->right))
            {
                RL(t);
                return false;
            }
            RR(t);
            if (height(t->right) == height(t->left)) return false;
            else return true;
        }
    }
};


int main()
{
    AvlTree a;
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