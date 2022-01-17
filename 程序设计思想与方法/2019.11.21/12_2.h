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

//����:menu
//�÷�:menu()
//����:����˵�
void menu();


//����:initilize
//�÷�:initilize()
//����:��ʼ������
void initilize();

//����:add
//�÷�:add()
//����:������β�����������
void add();

//����:modify
//�÷�:modify()
//����:���ز��޸������е�����
void modify();

//����:display
//�÷�:display()
//����:��ʾȫ��ѧ����Ϣ
void display();

//����:SearchByNo
//�÷�:SearchByNo()
//����:����ѧ�Ų�ѯѧ����Ϣ�����
void SearchByNo();

//����:SearchByName
//�÷�:SearchByName()
//����:����ѧ��������ѯѧ����Ϣ�����
void SearchByName();

//����:SortByNo
//�÷�:SortByNo()
//����:��ѧ����Ϣ��ѧ����������
void SortByNo();

//����:SortByTotalScore
//�÷�:SortByTotalScore()
//����:��ѧ����Ϣ���ܷ���������
void SortByTotalScore();

#endif // WHOLE
