#include<iostream>

using namespace std;

int main(){
    int change1,change2,max5fen,max2fen,remain,i,Methods=0;
    cout<<"Input the change(8<=K<100):__\b\b";
    cin>>change1;
    change2=change1-8; //减去一个1角、2角、5角，change2的1分，2分，5分数量可为0
    max5fen=change2/5;
    for (i=0;i<=max5fen;++i){
        remain=change2-5*i;
        max2fen=remain/2;
        Methods+=max2fen+1;//2角的个数可取0，1，2，……，max2fen，并且都有对应的非负整数的1角个数
        }
    cout<<"Methods="<<Methods<<endl;
}
