#include<iostream>
#include<cstring>
using namespace std;

int arr[7]={8,7,3,4,9,6,2};

char *encrypt(char *);
char *decrypt(char *);

int main()
{
    const int MAXSIZE=1000;
    char text[MAXSIZE],b[MAXSIZE];

    cout << "Please input plain text:";
    cin.getline(text,MAXSIZE);

    cout << "Encrypt:"<< encrypt(text)<<endl;  //把text存储的值加密了
    cout << "Decrypt:"<< decrypt(text);   //把修改后text存储的值解密
	
	return 0; 
}

char *encrypt(char *plain)
{
    int i,num;
    for (i=0;i<strlen(plain);++i)
    {
        num=i%7;
        plain[i]=char(32+(plain[i]+arr[num]-32)%91);
    }
    return plain;
}

char *decrypt(char *encrypted)
{
    int i,num;
    for (i=0;i<strlen(encrypted);++i)
    {
        num=i%7;
        encrypted[i]=char (32+(encrypted[i]-arr[num]-32+91)%91);
    }
    return encrypted;
}
