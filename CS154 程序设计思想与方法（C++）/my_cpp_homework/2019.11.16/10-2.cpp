#include <iostream>
#include <cstring>

using namespace std;

char *mystrrchr(char *str, char ch);

int main()
{
    int MAXSIZE = 200;
    char str[MAXSIZE], ch;

    cout << "Please input a string:";
    cin.getline(str, MAXSIZE);
    cout << "Please input a char:";
    cin >> ch;
    if (mystrrchr(str, ch) == NULL)
        cout << "Not Found";
    else
        cout << mystrrchr(str, ch);
}

char *mystrrchr(char *str, char ch)
{
    if (strrchr(str, ch) == NULL)
        return NULL;
    int len;
    char *arr;
    len = strlen(strrchr(str, ch));
    arr = new char[len + 1];
    strcpy(arr, strrchr(str, ch));
    arr[len] = '\0';
    return arr;
}
