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
    priorityQueue(const int *items, int size): maxSize(size + 10), currentSize(size)
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
    int n, total = 0, *num;
    int i, x, y;
    cin >> n;
    num = new int[n];
    for(i = 0; i < n; ++i)
    cin >> num[i];
    priorityQueue a(num, n);
    for (i = 0; i < n - 1; ++i)
    {
        x = a.deQueue();
        y = a.deQueue();
        total += x + y;
        a.enQueue(x + y);
    }
    cout << total << endl;
    return 0;
}
