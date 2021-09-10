#include <iostream>
#include <iomanip>

using namespace std;

class seqStack //从大到小排序的栈
{
private:
    int *data;
    int top_p;
    int maxSize;
    int currentLength;
    void doubleSpace()
    {
        int *tmp = data;
        data = new int[2 * maxSize];
        for (int i=0; i<maxSize; ++i)
        data[i] = tmp[i];
        maxSize *= 2;
        delete []tmp;
    }
    void maxHeap(int n);
    void buildMaxHeap(int n);
public:
    seqStack(int initSize = 10)
    {
        data = new int[initSize];
        maxSize = initSize;
        currentLength = 0;
        top_p = -1;
    }
    ~seqStack()
    {delete []data;}
    bool isEmpty() const
    {
        return top_p == -1;
    }
    void push(const int &x)
    {
        if (top_p == maxSize - 1) doubleSpace();
        data[++top_p] = x;
        currentLength++;
    }
    int pop()
    {
        currentLength--;
        return data[top_p--];
    }
    int top() const
    {
        return data[top_p];
    }
    void heapSort();
};
void seqStack::heapSort()
{
    int i;
    buildMaxHeap(currentLength);
    for (i = currentLength; i > 1; i--)
    {
        swap(data[0], data[i - 1]);
        currentLength = currentLength - 1;
        maxHeap(1);
    }
}
void seqStack::buildMaxHeap(int n)
{
    int i = n / 2;
    for (i; i > 0; i--)
        maxHeap(i);
}
void seqStack::maxHeap(int n)
{
    int leftChild, rightChild, smallest;
    leftChild = 2 * n;
    rightChild = 2 * n + 1;
    if (leftChild <= currentLength && data[leftChild - 1] < data[n - 1])
        smallest = leftChild;
    else
        smallest = n;
    if (rightChild <= currentLength && data[rightChild - 1] < data[smallest - 1])
        smallest = rightChild;
    if (smallest != n)
    {
        swap(data[n - 1], data[smallest - 1]);
        maxHeap(smallest);
    }
}

int main()
{
    seqStack boys, girls;
    int musicNumber, people, sex, time, *music;
    long int currentTime = 0, boysWait = 0,girlsWait = 0;
    int boysNum = 0, girlsNum = 0;
    double boysAve, girlsAve;
    int i;
    cin >> musicNumber;
    music = new int[musicNumber];
    for (i = 0; i < musicNumber; i++)
        cin >> music[i];
    cin >> people;
    for (i = 0; i < people; i++)
    {
        cin >> sex >> time;
        if (sex == 1)   
        {
            boys.push(time);
            ++boysNum;
        }
        else 
        {
            girls.push(time);
            ++girlsNum;
        }
    }
    boys.heapSort();
    girls.heapSort();

    for (i = 0; i < musicNumber - 1; ++i)
    {
        while (!girls.isEmpty() && !boys.isEmpty() && girls.top() <= currentTime && boys.top() <= currentTime)
        {
            girlsWait += (currentTime - girls.pop());
            boysWait += (currentTime - boys.pop());
        }
        currentTime += music[i];
    }
    while(!boys.isEmpty())
    {
        boysWait += (currentTime - boys.pop());

    }
    while(!girls.isEmpty())
    {
        girlsWait += (currentTime - girls.pop());
    }

    if (boysNum == 0) boysAve = 0;
    else boysAve = boysWait / double(boysNum);
    if (girlsNum == 0) girlsAve = 0;
    else girlsAve = girlsWait / double(girlsNum);
    
    cout << fixed << setprecision(2) << boysAve;
    cout << " ";
    cout << fixed << setprecision(2) << girlsAve;
    
    return 0;
}
