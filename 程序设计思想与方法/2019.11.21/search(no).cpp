#include"12_2.h"

extern StuInfo *head;

void SearchByNo()
{
    StuInfo *p=head;
    char no[MAXSIZE+1];
    cout <<"Please input the student number";
    cin.get();
    cin.getline(no,MAXSIZE);
    while (true)
        {
            if (strcmp(no,p->no)!=0)
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
