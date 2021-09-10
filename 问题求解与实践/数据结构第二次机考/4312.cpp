#include <iostream>

using namespace std;

struct BNode
{
    struct BNode* left;
    struct BNode* right;
    int data;
};


BNode* postorder(int* preorder, int* midorder, int length)
{
    if(length == 0) return NULL;
    BNode* node = new BNode;
    int index = 0;
    node->data = *preorder;
    for(;index < length; index++)
        if(midorder[index] == *preorder)
            break;
    node->left = postorder(preorder +1, midorder, index);
    node->right = postorder(preorder + index + 1, midorder + index + 1, length - index - 1);
    cout << node->data << ' ';
    delete node;
    return NULL;
}

int main()
{
    int n;
    cin >> n;
    int *pre = new int[n], *mid = new int[n];
    for(int i = 0;i<n;++i)
        cin >> pre[i];
    for(int i = 0;i<n;++i)
        cin >> mid[i];
    postorder(pre, mid, n); 
    return 0;
}