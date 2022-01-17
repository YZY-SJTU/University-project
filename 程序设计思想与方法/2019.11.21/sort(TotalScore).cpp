#include"12_2.h"

extern StuInfo *head;

void SortByTotalScore()
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
            if ((p->next->sum)<(p->next->next->sum))
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
