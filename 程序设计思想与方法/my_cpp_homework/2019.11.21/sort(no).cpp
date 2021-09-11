#include"12_2.h"

extern StuInfo *head;

void SortByNo()
{
    int cnt=0,i,j;
    bool flag;
    StuInfo *p = head,*tmp;
    while (p->next!=NULL)
    {
        ++cnt;
        p = p->next;
    }

    for (i=1; i<cnt; ++i)
    {
        p = head;
        flag=false;
        for(j=0; j<cnt-i; ++j)
        {
            if (strcmp(p->next->no,p->next->next->no)>0)
            {
                tmp=p->next->next->next;
                p->next->next->next=p->next;
                p->next=p->next->next;
                p->next->next->next=tmp;
                p=p->next;
                flag=true;
            }

        }
        if (!flag) break;
    }
}
