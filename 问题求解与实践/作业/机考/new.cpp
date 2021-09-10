#include <iostream>
#include <vector>

using namespace std;

class mission
{
private:
    int num;
    int priority;
    int start_time;
    vector<int> TimeNeed;
    int missionNum;
    int solved;
public:
    void setUp(string str)
    {
        int i=2;
        num = 0;
        priority = 0;
        start_time = 0;
        while(str[i]!=' ')
        {
            num = num *10 + int(str[i]-'0');
            ++i;
        }
        ++i;
        while(str[i]!=' ')
        {
            priority = priority *10+ int(str[i]-'0');
            ++i;
        }
        ++i;
        while(str[i]!=' ')
        {
            start_time = start_time *10+ int(str[i]-'0');
            ++i;
        }
        ++i;
        while(str[i] != ']')
        {
            int tmp = 0;
            while(str[i]!=' ' && str[i] != ']')
            {
                tmp = tmp *10+ int(str[i]-'0');
                ++i;
            }
            TimeNeed.push_back(tmp);
            if(str[i] == ' ')
            ++i;
        }
        solved = 0;
        missionNum = TimeNeed.size();
    }

    int getStartTime()
    {return start_time;}
    
    int getPriority()
    {return priority;}

    int getTimeNeed()
    {
        return TimeNeed[solved];
    }

    int getID()
    {
        return num;
    }

    void solveOne()
    {
        ++solved;
        if(priority != 1)
        --priority;
    }

    void UpPriority()
    {
        if(priority != 10)
        ++priority;
    }

    bool isSolved()
    {
        return (missionNum == solved);
    }

    void renewTime(int x)
    {TimeNeed[solved] -= x;}

    void traverse()
    {
        cout << "p"<<num<<endl;
        cout << priority<<endl;
        cout <<start_time<<endl;
        for(int i=0; i<TimeNeed.size(); ++i)
        cout << TimeNeed[i]<< " ";

    }
};

class seqList
{
private:
    mission *data;
    int currentLength;
    int maxSize;
    void doubleSpace()
    {
        mission *tmp = data;
        maxSize *= 2;
        data = new mission[maxSize];
        for (int i = 0; i < currentLength; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seqList(int initSize = 10)
    {
        data = new mission[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList()
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

    void setUp(string str)
    {
        if(maxSize == currentLength)
        doubleSpace();
        data[currentLength].setUp(str);
        ++currentLength;
    }

    void solveOne(int i)
    {data[i].solveOne();}

    void renewTime(int i, int x)
    {
        data[i].renewTime(x);
    }

    void UpPriority(int i)
    {
        data[i].UpPriority();
    }
    
    mission visit(int i)
    {
        return data[i];
    }

    void insert(const mission &x)
    {
        if (currentLength == maxSize)
            doubleSpace();
        data[currentLength] = x;
        ++currentLength;
    }

    void remove(int i)
    {
        for (int j = i; j < currentLength - 1; j++)
            data[j] = data[j + 1];
        --currentLength;
    }


};

class SolveMission
{
private:
    seqList data;
public:
    void setUp()
    {
        string str;
        while(getline(cin, str))
        data.setUp(str);
    }

    void solveProblem()
    {
        
        int sum = data.length();
        int currentTime = 0;
        int currentNum;
        int finishedNum = 0;
        int *order;
        
        order = new int[sum];
        for(int i=0; i<sum; ++i)
        order[i] = 0;
        //找到最先启动，优先级最高的片
        currentTime = data.visit(0).getStartTime();
        currentNum = 0;
        
        for(int i=1; i<sum; ++i)
        {
            if(data.visit(i).getStartTime() < currentTime)
            {
                currentTime = data.visit(i).getStartTime();
                currentNum = i;
            }
            if(data.visit(i).getStartTime() == currentTime)
            {
                if(data.visit(i).getPriority() > data.visit(currentNum).getPriority())
                {
                    currentTime = data.visit(i).getStartTime();
                    currentNum = i;
                }
            }
        }
            while(finishedNum != sum)
            {
                //判断是否有抢占
                bool flag = false;
                int first = currentNum;
                int firstPriority = data.visit(currentNum).getPriority();
                currentTime += data.visit(currentNum).getTimeNeed();
                data.solveOne(currentNum);
                for(int i=0; i<sum; ++i)
                {
                    if(i != currentNum && data.visit(i).getStartTime() <= currentTime)
                    data.UpPriority(i);
                }
                for(int i=0; i<sum; ++i)
                {
                    if(data.visit(i).isSolved())
                    continue;
                    if(data.visit(i).getPriority() >= 2 + data.visit(currentNum).getPriority()
                    && (currentTime > data.visit(i).getStartTime()))
                    {
                        if(firstPriority < data.visit(i).getPriority())
                        {
                            first = i;
                            firstPriority = data.visit(i).getPriority();
                            flag = true;
                        }    
                    }
                }

                if(!flag)
                {
                    if(data.visit(currentNum).isSolved())
                    {
                        order[finishedNum] = data.visit(currentNum).getID();
                        ++finishedNum;
                        if(finishedNum != sum)
                        {
                            int i;
                            for(i=0; i<sum; ++i)
                            {
                                if(data.visit(i).isSolved())
                                continue;
                                if(currentTime >= data.visit(i).getStartTime())
                                break;
                            }
                            if(i == sum)
                            {
                                for(i=0; i<sum; ++i)
                                {
                                    if(data.visit(i).isSolved())
                                    continue;
                                    else 
                                    {
                                        currentTime = data.visit(i).getStartTime();
                                        currentNum = i;
                                    }
                                    break;
                                }
                                for(i=0; i<sum; ++i)
                                {
                                    if(data.visit(i).isSolved())
                                    continue;
                                    else if(currentTime > data.visit(i).getStartTime())
                                    {
                                        currentTime = data.visit(i).getStartTime();
                                        currentNum = i;
                                    }
                                }
                            }
                            else
                            {
                                for(int i=0; i<sum; ++i)
                                {
                                    if(data.visit(i).isSolved())
                                    continue;
                                    else if(data.visit(i).getStartTime() <= currentTime)
                                    { 
                                        currentNum = i;
                                        break;
                                    }
                                }
                                for(int i=0; i<sum; ++i)
                                {
                                    if(data.visit(i).isSolved())
                                    continue;
                                    else if(data.visit(i).getPriority() > data.visit(currentNum).getPriority()
                                    &&data.visit(i).getStartTime() <= currentTime)
                                    currentNum = i;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(data.visit(currentNum).isSolved())
                    {
                        order[finishedNum] = data.visit(currentNum).getID();
                        ++finishedNum;
                    }
                    currentNum = first;
                }
            }
            for(int i=0; i<sum; ++i)
            {
                cout << "P" << order[i]<<" ";
            }
            cout <<endl;
    }
};

int main()
{
    SolveMission a;
    a.setUp(); 
    a.solveProblem();   
}