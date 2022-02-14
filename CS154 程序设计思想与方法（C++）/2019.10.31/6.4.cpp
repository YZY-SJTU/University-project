#include<iostream>

using namespace std;

int main(){
    const int MAXSIZE1=10,MAXSIZE2=80;
    int i,j,LineNum,EnglishLetter=0,Number=0,Others=0;
    char diag[MAXSIZE1-1][MAXSIZE2+1],copy1[MAXSIZE1-1][MAXSIZE2+1];

    cout<<"请输入行数:_\b";
    cin >>LineNum; cin.get();     //读掉留下的'\0'
    cout<<"请输入英文文章:"<<endl;
    for (i=0;i<LineNum;++i)
    {   cin.getline(diag[i],MAXSIZE2+1); }

    for (i=0;i<LineNum;++i)
    {   for (j=0;diag[i][j]!='\0';++j)
        {   if (diag[i][j]<='9'&&diag[i][j]>='0') ++Number;
            else if ((diag[i][j]<='z'&&diag[i][j]>='a')||(diag[i][j]<='Z'&&diag[i][j]>='A')) ++EnglishLetter;
                else if (diag[i][j]!=' ') ++Others;
        }
    }
    cout<<"英文字母:"<<EnglishLetter<<endl;
    cout<<"数字:"<<Number<<endl;
    cout<<"其它字符:"<<Others<<endl;
}
