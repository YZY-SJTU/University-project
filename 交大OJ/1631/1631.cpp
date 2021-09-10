#include <iostream>
#include <cstring>

using namespace std;

void reverse(char *str)
{
    char tmp[502];
    for (int i=0; i<strlen(str); i++)
        tmp[i] = str[strlen(str)-i-1];
    tmp[strlen(str)]='\0';
    strcpy(str, tmp);
}

char *Divide(char *str1, char *str2)
{
    char remain[502],substr[502],result[502],complement[502],tmp[502];
    int i,digit = 0,cnt;
    while(strlen(remain) > strlen(str2) ||(strlen(remain) == strlen(str2) && strcmp(remain, str2) < 0))
    {
        if (strcmp(remain, str2)<0)
            {
                strncpy(substr, remain, strlen(str2)+1);
                //减法
                for (i = strlen(str2); i > 0; i--)
                {
                    if (substr[i] - digit < str2[i-1])
                        tmp[strlen(str2)-i]= substr[i] - str2[i-1] + 10 - digit +'0';
                    else tmp[strlen(str2)-i]= substr[i] - str2[i-1] - digit +'0';
                }
                tmp[strlen(str2)] = substr[0]- digit;
            }
        else strncpy(substr, remain, strlen(str2));
        
        
    }


}


int main()
{
    char str1[502], str2[502];
    cin >> str1 >> str2;
    reverse(str1);
    reverse(str2);

}
