#include"12_2.h"

extern StuInfo *head;

void SearchByName()
{
    StuInfo *p=head;
    char name[MAXSIZE+1];
    cout <<"Please input the student number";
    cin.get();
    cin.getline(name,MAXSIZE);
    while (true)
        {
            if (strcmp(name,p->name)!=0)
                p=p->next;
            else
            {
                cout << "No:"<< p->no <<endl;
                cout << "Name:"<< p->name <<endl;
                cout << "Math:"<< p->math << '\t'<< "English:"<< p->english<< '\t'<<"physics:"<< p->physics<< endl;
                cout << "Total score:"<< p->sum<< '\t'<<"Average score:"<< p->average<<endl<<endl;
                break;
            }
            if (p == NULL)
            {
                cout << "Not Found"<<endl;
                break;
            }
        }
}
