#include"12_2.h"

extern StuInfo *rear;

void add()
{
    char no[MAXSIZE+1];
    char name[MAXSIZE+1];
    char choose;
    int math,english,physics;
    StuInfo *p;
    while (true)
    {
        cout << "Please input the student number:";
        cin.get();
        cin.getline(no,MAXSIZE);
        cout << "Please input the student name:";
        cin.getline(name,MAXSIZE);
        cout << "Please input the Math score:";
        cin >> math;
        cout << "Please input the English score:";
        cin >> english;
        cout << "Please input the physics score:";
        cin >> physics;

        p=new StuInfo;
        strcpy(p->no, no);
        strcpy(p->name, name);
        p->math = math;
        p->english =english;
        p->physics = physics;
        p->sum = math +english +physics;
        p->average = (p->sum)/3.0;
        rear->next = p;

        rear = p;

        cout << "Do you want to add again?(y/n):";
        cin >> choose;
        cout << endl;
        if (choose == 'n') break;
    }
    rear->next = NULL;
}
