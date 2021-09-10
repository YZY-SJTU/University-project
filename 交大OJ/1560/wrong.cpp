#include <iostream>
#include <cstring>

using namespace std;

class BinarySearchTable
{
private:
    struct BinaryNode
    {
        long int data;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const int & thedata, BinaryNode *lt= NULL, BinaryNode *rt= NULL):data(thedata), left(lt), right(rt){}
    };
    
    BinaryNode *root;

public:
    BinarySearchTable(){root = NULL;}
    ~BinarySearchTable(){makeEmpty(root);}
    void find(const long int &x) const 
    {
        string str="*";
        if(find(x, root, str)) cout<< str << endl;
        else cout << "Nothing" << endl;
    }
    void insert(const long int &x){insert(x, root);}
    void remove(const long int &x){remove(x, root);}
private:
    void insert(const long int &x, BinaryNode *&t)
    {
        if (t == NULL) t = new BinaryNode(x, NULL, NULL);
        else if (x < t->data) insert(x, t->left);
            else if(x > t->data) insert(x, t->right);
    }
    void remove(const long int &x, BinaryNode *&t)
    {
        if (t == NULL) return;
        if (x < t->data) remove(x, t->left);
        else if (t->data < x) remove(x, t->right);
            else if (t->right == NULL) 
                {
                    BinaryNode *oldNode = t;
                    t = t->left;
                    delete oldNode;
                }
                else
                {
                    BinaryNode *tmp = t->right;
                    while(tmp->left != NULL) tmp = tmp->left;
                    t->data = tmp->data;
                    subRemove(t->data, t->right);
                }
    }
    void subRemove(const long int &x, BinaryNode *&t)
    {
        if (x < t->data) subRemove(x, t->left);
        else if (t->data < x) subRemove(x, t->right);
            else
            {
                BinaryNode *oldNode = t;
                t = t->right;
                delete oldNode;
            }
    }
    bool find(const long int &x, BinaryNode *t, string &str) const
    {
        if(t == NULL) return false;
        if(x == t->data) return true;

        if(x < t->data) 
        {
            str += "l";
            return find(x, t->left, str);
        }
        else
        {
            str += "r";
            return find(x, t->right, str);
        }
    }
    void makeEmpty(BinaryNode *t)
    {
        if (t == NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
};

int main()
{
    BinarySearchTable a;
    int n;
    int i;
    long int *number;
    char *quote;
    cin >> n;
    number = new long int[n];
    quote = new char[n];
    for (i=0; i<n; ++i)
    cin >> quote[i] >> number[i];
    for (i=0; i<n; ++i)
    {
        if (quote[i] == '+')
        a.insert(number[i]);
        if (quote[i] == '-')
        a.remove(number[i]);
        if (quote[i] == '*')
        a.find(number[i]);
    }
    delete []number;
    delete []quote;
    return 0;
}

