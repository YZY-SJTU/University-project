#include<iostream>

using namespace std;

int main(){
    char letter;
    cout <<"������һ����ĸ:_\b";
    cin >> letter;
    if (letter=='a'||letter=='e'||letter=='i'||letter=='o'||letter=='u'||letter=='A'||letter=='E'||letter=='I'||letter=='O'||letter=='U')
        cout <<"Ԫ��"<<endl;
     else if ('a'<letter&&letter<='z'||'A'<letter&&letter<='Z')
        cout <<"����"<<endl;
        else
            cout <<"����Ӣ����ĸ"<<endl;


}
