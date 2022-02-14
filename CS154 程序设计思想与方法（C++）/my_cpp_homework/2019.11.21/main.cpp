#include"12_2.h"

//head是数据链表的头，rear是数据链表的尾
StuInfo *head,*rear;

int main()
{
    void (*func[8])() = {NULL,add,modify,display,SearchByNo,SearchByName,SortByNo,SortByTotalScore};
    int select;

    initilize();

    while (true)
    {
        menu();

        cin >> select;
        cout << endl;

        if (select == 0) return 0;
        if (select >7) cout << "Input error\n";
        else func[select]();
    }
}
