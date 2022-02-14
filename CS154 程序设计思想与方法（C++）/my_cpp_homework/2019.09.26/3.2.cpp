#include<iostream>

using namespace std;

int main(){
    char letter;
    cout <<"请输入一个字母:_\b";
    cin >> letter;
    if (letter=='a'||letter=='e'||letter=='i'||letter=='o'||letter=='u'||letter=='A'||letter=='E'||letter=='I'||letter=='O'||letter=='U')
        cout <<"元音"<<endl;
     else if ('a'<letter&&letter<='z'||'A'<letter&&letter<='Z')
        cout <<"辅音"<<endl;
        else
            cout <<"不是英文字母"<<endl;


}
