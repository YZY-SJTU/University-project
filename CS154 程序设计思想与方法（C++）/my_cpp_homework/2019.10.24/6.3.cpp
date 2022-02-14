#include<iostream>

using namespace std;

int main() {
    const int MAXSIZE=80;
    int i,j,order=1;
    bool flag1=true,flag2;
    char tmp,ch1[MAXSIZE+1],ch2[MAXSIZE+1];
    cout<<"Please input a string(without ' '):";
    cin.getline(ch1,MAXSIZE+1);

    //È¥³ýÖØ¸´×Ö·û
    ch2[0]=ch1[0];
    for (i=1;ch1[i]!='\0';++i)
    { for (j=0;j<order;++j)
        {if (ch1[i]==ch2[j]) flag1=false;}
      if (flag1)
      {ch2[order]=ch1[i]; ++order;}
      else flag1=true;
    }

    //°´ASCIIÂëÅÅÐò
    for (i=1;i<order;++i)
    { flag2=false;
        for (j=0;j<order-i;++j)
        { if (ch2[j+1]>ch2[j])
            {tmp=ch2[j]; ch2[j]=ch2[j+1]; ch2[j+1]=tmp; flag2=true;}
        }
      if (!flag2) break;
    }

    for (i=0;i<order;++i)
        cout<<ch2[i];
}
