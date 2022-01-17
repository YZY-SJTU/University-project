#include"12_2.h"

extern StuInfo *head;

void display()
{
    StuInfo *p=head;

    if (p->next==NULL)
        cout << "No statistics" << endl;
    else
    {
        p=p->next;
        while (true)
        {
            cout << "No:"<< p->no <<endl;
            cout << "Name:"<< p->name <<endl;
            cout << "Math:"<< p->math << '\t'<< "English:"<< p->english<< '\t'<<"physics:"<< p->physics<< endl;
            cout << "Total score:"<< p->sum<< "   "<<"Average score:"<< p->average<<endl<<endl;
            if (p->next==NULL) break;
            else p = p->next;
        }
    }
}
