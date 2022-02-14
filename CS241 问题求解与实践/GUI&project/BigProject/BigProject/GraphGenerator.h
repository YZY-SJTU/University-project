#ifndef GRAPHGENERATOR_GUARD
#define GRAPHGENERATOR_GUARD

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include"adjListGraph.h"

using namespace std;

string ChangeToString(int x);

class reference  //转化为多项式过程中记录系数
{
private:
    char* data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        char* tmp = data;
        maxSize *= 2;
        data = new char[maxSize];
        for (int i = 1; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    reference(int initSize = 10)
    {
        data = new char[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~reference()
    {
        delete[] data;
    }

    void clear()
    {
        currentLength = 0;
    }

    int length()
    {
    return currentLength;
    }

    void input(const char& x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    double output()  //将字符串形式的数字转化为double数字
    {
        double x = 0, tmp = 0;
        bool flag = false;
        int i, length = 0;
        for (i = 0; i < currentLength; ++i)
            if (data[i] == '.')
            {
                ++i; length = currentLength - i; flag = true; break;
            }
            else x = x * 10 + int(data[i] - '0');
        for (i; i < currentLength; ++i)
            tmp = tmp * 10 + int(data[i] - '0');
        if (flag)
        {
            for (i = 0; i < length; ++i)
                tmp /= 10;
            x += tmp;
        }
        return x;
    }
};



class GraphGenerator
{
public:
    GraphGenerator() { srand(time(NULL)); }
    ~GraphGenerator() {}
    void generate(int x, string fileName);
    void add(string fileName, int y);
    double divideGraph(int n, string fileName);
    vector<int> searchAllSubGraph(int NodeName, string fileName);
    double searchAllSubGraph(int NodeName1, int NodeName2, string fileName, vector<int>& result_1, double& weight1, vector<int>& result_2, double& weight2);
    void setNodeRange(int x);
    void setWeightRange(int x);
    void setPInEdge(int x);

public:
    struct fileNode
    {
        string fileName;
        vector<int> currentNode;
    };
private:
    //记录图文件内已有的结点
    vector<fileNode>  storedNode;
    int NodeRange = 1000;
    int WeightRange = 1000;
    int EdgeRange = 10;
    struct searchRoot
    {
        string fileName;
        int StartNodeNum;
    };

    double RandDouble()//生成随机double类型非负数据
    {
        double result = rand() % WeightRange;
        double digit = 1;
        for (int i = 0; i < 6; ++i)
        {
            int tmp = rand() % 10;
            digit /= 10;
            result += tmp * digit;
        }
        return result;
    }

    void searchOneSubGraph(int NodeNum, string subGraphName, string mainFileName, vector<int> &reachNode, vector<searchRoot> &nextSearch, int initialNode);
    double searchFromFirstToSecond(int NodeName1, int NodeName2, string fileName, vector<int>& firstToSecond, vector<int>& result);
};


    
    


#endif // !GRAPHGENERATOR_GUARD