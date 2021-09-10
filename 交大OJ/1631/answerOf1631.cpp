#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

const int digit = 10;

string DeZero(string a)
{
	int i;
	for(i=0;i<a.length();i++)
	{
		if(a.at(i)>48) break;
	}
	if(i==a.length()) return "0";
	a.erase(0,i);
	return a;
}
int Judge(string a,string b)//判断两个正数的大小
{
	if(a.length()>b.length()) return 1;
	if(a.length()<b.length()) return -1;
	int i;
	for(i=0;i<a.length();i++)
	{
		if(a.at(i)>b.at(i)) return 1;
		if(a.at(i)<b.at(i)) return -1;
	}
	return 0;
}
string StrMinus(string a,string b)//自然数减法
{
	a=DeZero(a);
	b=DeZero(b);
	int i,j = 0;
	string c="0";
	string c1,c2;
	string d="-";
	if(Judge(a,b)==0) return c;
	if(Judge(a,b)==1)
	{
		c1=a;
		c2=b;
	}
	if(Judge(a,b)==-1)
	{
		c1=b;
		c2=a;
		j=-1;
	}
	reverse(c1.begin(),c1.end());
	reverse(c2.begin(),c2.end());
	for(i=0;i<c2.length();i++)
	{
		if(c2.at(i)>=48&&c2.at(i)<=57) c2.at(i)-=48;
		if(c2.at(i)>=97&&c2.at(i)<=122) c2.at(i)-=87;
	}
	for(i=0;i<c1.length();i++)
	{
		if(c1.at(i)>=48&&c1.at(i)<=57) c1.at(i)-=48;
		if(c1.at(i)>=97&&c1.at(i)<=122) c1.at(i)-=87;
	}
	for(i=0;i<c2.length();i++)
	{
		c1.at(i)=c1.at(i)-c2.at(i);
	}
	for(i=0;i<c1.length()-1;i++)
	{
		if(c1.at(i)<0)
		{
			c1.at(i)+=digit;
			c1.at(i+1)--;
		}
	}
	for(i=c1.length()-1;i>=0;i--)
	{
		if(c1.at(i)>0) break;
	}
	c1.erase(i+1,c1.length());
	for(i=0;i<c1.length();i++)
	{
		if(c1.at(i)>=10) c1.at(i)+=87;
		if(c1.at(i)<10) c1.at(i)+=48;
	}
	reverse(c1.begin(),c1.end());
	if(j==-1) c1.insert(0,d);
	return c1;
}
string divide(string a,string b)//自然数除法
{
	if(b.length()==1&&b.at(0)==48) return "error";
	long int i,j;
	string c1,c2,d,e;
	if(Judge(a,b)==0) return "1";
	if(Judge(a,b)==-1)
	{
		return "0";
	}
	c1=DeZero(a);
	c2=DeZero(b);
	d="";
	e="";
	for(i=0;i<c1.length();i++)
	{
		j=0;
		d=d+c1.at(i);
		d=DeZero(d);
		while(Judge(d,b)>=0)
		{
			d=StrMinus(d,b);
			d=DeZero(d);
			j++;
		}
		e=e+"0";
		e.at(i)=j;
	}
	for(i=0;i<e.length();i++)
	{
		if(e.at(i)>=10) e.at(i)+=87;
		if(e.at(i)<10) e.at(i)+=48;
	}
	e=DeZero(e);
	return e;
}

int main()
{
    string str1, str2, str3;
    cin >> str1 >> str2;
    reverse(str1.begin(),str1.end());
    reverse(str2.begin(),str2.end());
    str3 = divide(str1, str2);
    reverse(str3.begin(),str3.end());
    cout << str3;
	return 0;
}