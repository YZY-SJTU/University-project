#include <iostream>
using namespace std;

class priorityQueue
{
private:
    int currentSize;
    int *array;
    int maxSize;

    void doublespace()
    {
        int *tmp = array;
        maxSize *= 2;
        array = new int[maxSize];
        for (int i = 0; i <= currentSize; ++i)
            array[i] = tmp[i];
        delete []tmp;
    }
    void buildHeap()
    {
        for (int i = currentSize / 2; i > 0; i--)
            percolateDown(i);
    }
    void percolateDown(int hole)
    {
        int child;
        int tmp = array[hole];

        for (; hole * 2 <= currentSize; hole = child)
        {
            child = hole * 2;
            if (child !=currentSize && array[child + 1] < array[child])
                child++;
            if (array[child] < tmp) array[hole] = array[child];
            else break;
        }
        array[hole] = tmp;
    }
public:
    priorityQueue(int capacity = 100)
    {
        array = new int[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const int *items, int size):maxSize(size+10), currentSize(size)
    {
        array = new int[maxSize];
        for (int i = 0; i < size; i++)
            array[i + 1] = items[i];
        buildHeap();
    }
    ~priorityQueue()
    {delete []array;}
    bool isEmpty() const
    {return currentSize == 0;}
    void enQueue(const int &x)
    {
        if (currentSize == maxSize - 1) doublespace();

        int hole = ++currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
            array[hole] = array[hole / 2];
        array[hole] = x;
    }
    int deQueue()
    {
        int minItem;
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }
    int getHead() const
    {return array[1];}
};

int main()
{
    int k, l;
    int i, j;
    int *cnt, sum=0;
    int **number, *first;
    cin >> k >> l;
    number = new int*[k];
    for (i=0; i<k; ++i)
        number[i] = new int[l];

    first = new int[k];

    cnt = new int[k];
    for (i=0; i<k; ++i)
        cnt[i] = 0;

    for (i = 0; i < k; ++i)
    {
        for (j = 0; j<l; ++j)
        cin >> number[i][j];
    }
    
    for (i = 0; i < k; ++i)
    first[i] = number[i][0];

    priorityQueue print(first,k);

    int tmp;
    while(sum < k*l)
    {
        tmp = print.deQueue();
        cout << tmp << " ";
        for(i = 0; i < k; ++i)
        {
            if (tmp == first[i] && cnt[i] != l-1)
            {
                ++cnt[i];
                first[i] = number[i][cnt[i]];
                print.enQueue(first[i]);
                break;
            }
        }
        ++sum;
    }

}