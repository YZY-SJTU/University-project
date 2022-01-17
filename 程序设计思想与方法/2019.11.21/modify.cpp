#include"12_2.h"

extern StuInfo *head;

void modify()
{
    StuInfo *p=head;
    char no[MAXSIZE+1];
    char flag;
    int score,choose;

    while (true)
    {
        cout <<"Please input the student number:";
        cin.get();
        cin.getline(no,MAXSIZE);
        while (true)
            {
                if (strcmp(no,p->no)!=0)
                    p = p->next;
                else
                {
                    cout << "Please choose which score you want to modify(Math is 1,English is 2,physics is 3):";
                    cin >>choose;
                    cout << "input the new score:";
                    cin >>score;
                    switch (choose)
                    {
                    case 1:
                        p->math = score;
                        break;
                    case 2:
                        p->english = score;
                        break;
                    case 3:
                        p->physics = score;
                        break;
                    }
                    break;
                }
                if (p == NULL)
                {
                    cout << "Not Found"<<endl;
                    break;
                }

            }
        cout << "Do you want to modify again?(y/n):";
        cin >> flag;
        cout << endl;
        if (flag == 'n') break;
        else p = head;
    }
}
