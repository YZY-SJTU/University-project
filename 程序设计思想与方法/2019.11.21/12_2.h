#ifndef WHOLE
#define WHOLE

#include<iostream>
#include<cstring>
using namespace std;

const int MAXSIZE=20;
struct StuInfo
{
    char no[MAXSIZE+1];
    char name[MAXSIZE+1];
    int math;
    int english;
    int physics;
    int sum;
    double average;
    StuInfo *next;
};

//函数:menu
//用法:menu()
//作用:输出菜单
void menu();


//函数:initilize
//用法:initilize()
//作用:初始化链表
void initilize();

//函数:add
//用法:add()
//作用:在链表尾部添加新数据
void add();

//函数:modify
//用法:modify()
//作用:搜素并修改链表中的数据
void modify();

//函数:display
//用法:display()
//作用:显示全部学生信息
void display();

//函数:SearchByNo
//用法:SearchByNo()
//作用:按照学号查询学生信息并输出
void SearchByNo();

//函数:SearchByName
//用法:SearchByName()
//作用:按照学生姓名查询学生信息并输出
void SearchByName();

//函数:SortByNo
//用法:SortByNo()
//作用:将学生信息按学号升序排序
void SortByNo();

//函数:SortByTotalScore
//用法:SortByTotalScore()
//作用:将学生信息按总分升序排序
void SortByTotalScore();

#endif // WHOLE
