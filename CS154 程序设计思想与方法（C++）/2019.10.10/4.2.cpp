#include<iostream>

using namespace std;

int main(){
    int change1,change2,max5fen,max2fen,remain,i,Methods=0;
    cout<<"Input the change(8<=K<100):__\b\b";
    cin>>change1;
    change2=change1-8; //��ȥһ��1�ǡ�2�ǡ�5�ǣ�change2��1�֣�2�֣�5��������Ϊ0
    max5fen=change2/5;
    for (i=0;i<=max5fen;++i){
        remain=change2-5*i;
        max2fen=remain/2;
        Methods+=max2fen+1;//2�ǵĸ�����ȡ0��1��2��������max2fen�����Ҷ��ж�Ӧ�ķǸ�������1�Ǹ���
        }
    cout<<"Methods="<<Methods<<endl;
}
