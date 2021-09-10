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
    void decrease(const int i, const int v)
    {
        array[i] -= v;
        int tmp = array[i], k = i;
        if (i == 1 || array[i] >= array[i / 2])
            return;
        while(k > 1)
        {
            array[k] = array[k / 2];
            if (k <= 3 || tmp >= array[k / 4])
            {
                array[k / 2] = tmp;
                break;
            }
            else k /= 2;
        }
    }
    int find(int x)
    {
        int target, index;
        int i;
        for (i = 1; i <= currentSize; i++)
            if (array[i] > x)
            {
                target = array[i];
                index = i;
                break;
            }
        if (i == currentSize + 1)
        return 0;

        for (i = index; i <= currentSize; i++)
        {
            if (array[i] > x && target > array[i])
            {
                target = array[i];
                index = i;
            }
        }
        return index;
    }
};

int main()
{
    priorityQueue a;
    int num;
    int *value, *addition;
    char **str;
    cin >> num;
    value = new int[num];
    addition = new int[num];
    str = new char*[num];
    for (int i = 0; i < num; i++)
        str[i] = new char[9];
    for(int i = 0; i < num; i++)
    {
        cin >> str[i];
        cin >> value[i];
        if (str[i][0] == 'd')
            cin >> addition[i];
    }

    for (int i = 0; i < num; i++)
    {
        if (str[i][0] == 'i')
            a.enQueue(value[i]);
        if (str[i][0] == 'f')
            cout << a.find(value[i]) << endl;
        if (str[i][0] == 'd')
            a.decrease(value[i], addition[i]);
    }
    delete [] value;
    delete [] addition;
    for (int i = 0; i < num; i++)
        delete [] str[i];
    delete [] str;

    return 0;
}