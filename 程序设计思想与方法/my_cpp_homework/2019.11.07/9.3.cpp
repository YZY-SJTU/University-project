#include<iostream>
#include<cstring>
using namespace std;

char *julian(int, int);

int Runyear[12]={31,29,31,30,31,30,31,31,30,31,30,31},Pingyear[12]={31,28,31,30,31,30,31,31,30,31,30,31};
char *month[12]={"Jan","Feb","Mar","Apr","May","June","July","Aug","Sept","Oct","Nov","Dec"};

int main()
{   int year,day;
	char *p; 
    cout << "Please input year and day(Julian):";
    cin >> year>> day;
    p= julian( year, day);
    cout<< p;
    
	delete [] p;
    
	return 0;
} 

char *julian(int year, int day)
{
    int *p,TotalDay,i,digit,remain=day;
    if ((year%4==0&&year%100!=0)||year%400==0)
        {TotalDay=366; p=Runyear;}
    else {TotalDay=365; p=Pingyear;}
    if (day>TotalDay||day<=0) return NULL;
    else {  for (i=0;i<11;++i)
            if (remain<=p[i]) break;
            else remain-=p[i];
         }

    if (remain<10) digit = 1;
    else digit = 2;

    char *date = new char[strlen(month[i])+digit+2];
    
	// 将带输出值加到date上
    strcpy(date,month[i]);
    date[strlen(month[i])]=' ';

    if (digit == 2) {date[strlen(month[i])+1]=char('0' + remain/10); date[strlen(month[i])+2]=char('0' + remain%10);}
    else date[strlen(month[i])+1]=char('0' + remain);

    date[strlen(month[i])+digit+1]='\0';

    return date;
}
