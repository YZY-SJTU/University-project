#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <map>//map是一个键值对容器。处理一对一数据时有效
//map内部自建一颗红黑树，这棵树具有对数据自动排序的功能，因此，map内的数据都是按key的值排好序的
#include <set>//set是集合，一个内部自动有序而且不重复元素的容器
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cctype>
#include <string>

#define MAX 1024

using namespace std;

class WordString
{
    public:
    char left;//句子左部
    vector<string> right;//右部集合
    WordString (const char& str)//定义初始化
    {
        left = str;
    }
    void insert(char str[])//向右部塞入句式串
    {
        right.push_back(str);
    }
    void print()//打印集合后的文法串
    {
        printf("%c->%s", left, right[0].c_str());
        for(int i = 1; i < right.size(); i++)
            printf("|%s", right[i].c_str());
        puts("");
    }
};


char source;//归约结束时的非终结符
char relation[MAX][MAX];//用于记录算符优先文法分析表
vector<char> VT; //所有终结符的集合
vector<WordString> VN_set;//文法串输入的整理集合
map<char,int> VN_dic;//char为键，int为对应的值
set<char> first[MAX];//记录所有非终结符对应的firstvt集合元素
set<char> last[MAX];//记录所有非终结符对应的lastvt集合元素
int used[MAX];//形成VT的辅助集合
int vis[MAX]; //表示对应左值是否进行过dfs寻找
bool flag = false;//表示文法是否具有二义性 
//默认小写字母为终结符，反之为非终结符


void handle_input(ifstream &inFile)//处理输入文本，使用usd，完成VT,VN_set的记录
{
    char s[MAX];//读取每一行的文法
    char ch;
    int cnt = 0;
    memset(used, 0, sizeof(used));//初始化
    while((ch = inFile.get()) != EOF)
	{
        if(ch != '\n')
        {
            if(ch != ' ')
            {
                s[cnt] = ch;
                cnt++;
            }
            continue;
        }
        if(cnt == 0)
        continue;
        s[cnt] = '\0';

        int len = strlen(s), j = 1;
        s[1] = '\0';//隔断左右两部分
        if (!VN_dic[s[0]])//未查到这个表达式左值
        {
            VN_set.push_back(WordString(s[0]));
            VN_dic[s[0]] = VN_set.size();//map中元素个数即为其对应的值
        }
        int x = VN_dic[s[0]] - 1;
        int begin = 3;
        for(int k = 3; k< len; k++)//将右部全部放入VN_set中
        {
            if(s[k] == '|')
            {
                s[k] = '\0';
                VN_set[x].insert( s + begin );
                begin = k + 1;
            }
        }
        VN_set[x].insert( s + begin );
        for(int k = 0; k < j; k++)//处理左部终结符
            if(!isupper(s[k]))
            {
                if(used[s[k]]) continue;
                used[s[k]] = 1;
                VT.push_back(s[k]);
            }
        for(int k = j + 2; k < len; k++)//处理右部终结符
            if(!isupper(s[k]) && s[k] != '\0')
            {
                if(used[s[k]]) continue;
                VT.push_back(s[k]);
                used[s[k]] = VT.size();
            }


        for(int i = 0; i< cnt + 1; ++i)
        s[cnt] = ' ';
        cnt = 0;
    }

    if(cnt != 0)
    {
        s[cnt] = '\0';

        int len = strlen(s), j = 1;
        s[j] = '\0';
        if(!VN_dic[s[0]])//未查到这个表达式左值
        {
            VN_set.push_back(WordString(s[0]));
            VN_dic[s[0]] = VN_set.size();//map中元素个数即为其对应的值
        }
        int x = VN_dic[s[0]] - 1;
        int begin = 3;
        for(int k = 3; k < len; k++)//将右部全部放入VN_set中
        {
            if(s[k] == '|')
            {
                s[k] = '\0';
                VN_set[x].insert( s + begin );
                begin = k + 1;
            }
        }
        VN_set[x].insert( s + begin );
        for(int k = 0; k < j; k++)//处理左部终结符
            if(!isupper(s[k]))
            {
                if(used[s[k]]) continue;
                used[s[k]] = 1;
                VT.push_back(s[k]);
            }
        for(int k = j + 2; k < len; k++)//处理右部终结符
            if(!isupper(s[k]) && s[k] != '\0')
            {
                if(used[s[k]]) continue;
                VT.push_back(s[k]);
                used[s[k]] = VT.size();
            }

        for(int i = 0; i < cnt + 1; ++i)
            s[cnt] = ' ';
        cnt = 0;
    }
    VT.push_back('$');//结束符比较特殊，我们不在map中存放，避免不必要的寻找
}

void find_origin()//寻找最终归约到的非终结符,若循环我们规定最后的非终结符是第一个语句的左侧的非终结符
{
    bool *origin;
    origin = new bool[VN_set.size()];
    for(int i = 0; i < VN_set.size(); i++)
        origin[i] = true;
    vector<char> left;//非终结符存放表
    for(int i = 0; i < VN_set.size(); i++)
    left.push_back(VN_set[i].left);
    for(int i = 0; i < VN_set.size(); i++)
    {
        char tmp = VN_set[i].left;
        for(int j = 0; j < VN_set[i].right.size(); j++)
        {
            string& str = VN_set[i].right[j];
            for (int k = 0; k < str.length(); k++)
            {
                if(isupper(str[k]) && str[k] != tmp)
                {
                    for(int l = 0; l < left.size(); l++)
                        if(str[k] == left[l])
                        {
                            origin[l] = false;
                            break;
                        }
                }
            }
        }
    }

    int i;
    for(i = 0; i < VN_set.size(); i++)
        if(origin[i])
        {
            source = left[i];
            //cout <<"final is "<< left[i];
            break;
        }
    if(i == VN_set.size())
    {
        source = left[0];
        //cout <<"final is "<< source;
    }
    delete origin;
}

//用于寻找FIRSTVT集合 
void first_dfs (int x)//将x对应下标的终结符的FIRSTVT集合进行完善
{
    if(vis[x]) return;
    vis[x] = 1;//标记寻找过
    char& left = VN_set[x].left;//取左值
    for (int i = 0; i < VN_set[x].right.size(); i++)//对所有右表达式进行寻找
    {
        string& str = VN_set[x].right[i];
        if (isupper(str[0]))//A->B…，即以非终结符开头
        {
            int y = VN_dic[str[0]] - 1;//开头非终结符对应的值下标
            if (str.length() > 1 && !isupper(str[1]))//A->Ba…，即先以非终结符开头，紧跟终结符，则终结符入Firstvt
                first[x].insert(str[1]);
            first_dfs(y);
            set<char>::iterator it = first[y].begin();//A->B…，即以非终结符开头，该非终结符的Firstvt入A的Firstvt
            for (; it!= first[y].end(); it++)
                first[x].insert(*it);
        }
        else 
            first[x].insert(str[0]);//A->a…，即以终结符开头，该终结符入Firstvt
    }
}

void make_first()//寻找所有终结符FIRSTVT集合
{
    memset(vis, 0, sizeof(vis));//初始化vis区域所有值为0
    for(int i = 0; i < VN_set.size(); i++)
        if(vis[i]) continue;
        else first_dfs(i);
//     puts("------------FIRSTVT set-------------------");
//     for ( int i = 0 ; i < VN_set.size() ; i++ )
//     {
//         printf ( "%c : " , VN_set[i].left);
//         set<char>::iterator it = first[i].begin();
//         for ( ; it!= first[i].end() ; it++ )
//             printf ( "%c " , *it );
//         puts ("");
//     }
}

//用于寻找LASTVT集合
void last_dfs(int x)////将x对应下标的终结符的LASTVT集合进行完善
{
    if(vis[x]) return;
    vis[x] = 1;
    char& left = VN_set[x].left;
    for (int i = 0 ;i < VN_set[x].right.size(); i++)
    {
        string& str = VN_set[x].right[i];
        int n = str.length() - 1;
        if (isupper(str[n]))//A->…B，即以非终结符结尾
        {
            int y = VN_dic[str[n]] - 1;
            if (str.length() > 1 && !isupper(str[n-1]))//A->…aB，即先以非终结符结尾，前面是终结符，则终结符入Lastvt
                last[x].insert(str[1]);
            last_dfs(y);
            set<char>::iterator it = last[y].begin();//A->…B，即以非终结符结尾，该非终结符的Lastvt入A的Lastvt
            for (; it != last[y].end(); it++)
                last[x].insert(*it);
        }
        else 
            last[x].insert(str[n]);//A->…a，即以终结符结尾，该终结符入Lastvt
    }
}


void make_last()//寻找所有终结符LASTVT集合
{
    memset(vis, 0 ,sizeof(vis));//初始化vis区域所有值为0
    for (int i = 0; i < VN_set.size(); i++)
        if(vis[i]) continue;
        else last_dfs(i);

    // puts("--------------LASTVT set---------------------");
    // for ( int i = 0 ; i < VN_set.size() ; i++ )
    // {
    //     printf ( "%c : ", VN_set[i].left);
    //     set<char>::iterator it = last[i].begin();
    //     for ( ; it!= last[i].end() ; it++ )
    //         printf ( "%c " , *it );
    //     puts ("");
    // }
}

void make_table(ofstream &outFile)
{
    for(int i = 0; i < MAX; i++)//Table初始化
        for( int j = 0; j < MAX; j++)
            relation[i][j] = ' ';
    for(int i = 0; i < VN_set.size(); i++)
        for(int j = 0; j < VN_set[i].right.size(); j++)
        {
            string& str = VN_set[i].right[j];
            for (int k = 0; k < str.length() - 1; k++)
            {
                if (!isupper(str[k]) && !isupper(str[k+1]))//两终结符紧贴的符号对(左=右)
                {
                    if(relation[str[k]][str[k+1]] != '=' && relation[str[k]][str[k+1]] != ' ')
                    flag = true;
                    relation[str[k]][str[k+1]] = '=';
                }    
                if (!isupper(str[k]) && isupper(str[k+1]))//终结符在左边，非终结符在右边的符号对(左<右)
                {
                    int x = VN_dic[str[k+1]] - 1;
                    set<char>::iterator it = first[x].begin();
                    for (; it != first[x].end() ; it++)
                    {    
                        if(relation[str[k]][*it] != '<' && relation[str[k]][*it] != ' ')
                        flag = true;
                        relation[str[k]][*it] = '<';
                    }
                }
                if (isupper(str[k]) && !isupper(str[k+1]))//非终结符在左边，终结符在右边的符号对(左>右)
                {
                    int x = VN_dic[str[k]] - 1;
                    set<char>::iterator it = last[x].begin();
                    for (; it != last[x].end() ; it++)
                    {
                        if(relation[*it][str[k+1]] != '>' && relation[*it][str[k+1]] != ' ')
                        flag = true;
                        relation[*it][str[k+1]] = '>';
                    }    
                }
                if (k > str.length() - 2) continue;
                if (!isupper(str[k]) && !isupper(str[k+2]) && isupper(str[k+1]) )//两终结符紧贴在一终结符两边的符号对(终结符=)
                {
                    if(relation[str[k]][str[k+2]] != '=' && relation[str[k]][str[k+2]] != ' ')
                    flag = true;
                    relation[str[k]][str[k+2]] = '=';
                }    
            }
        }
    int refer = VN_dic[source] - 1;//$的表格构造
    set<char>::iterator it = first[refer].begin();
    for (; it != first[refer].end(); it++)
        relation[VT[VT.size()-1]][*it] = '<';
    it = last[refer].begin();
    for (; it != last[refer].end(); it++)
        relation[*it][VT[VT.size()-1]] = '>';
    relation[VT[VT.size()-1]][VT[VT.size()-1]] = '=';


        
    if(flag)
    {
        outFile << "grammar is ambiguous\nprogram exit\n";
        cout << "\ngrammar is ambiguous\nprogram exit\n";
        return;
    }
    for(int i = 0; i < VT.size() * 5; i++)
        outFile <<"-";
    outFile << "operator precedence table";
    for(int i = 0; i < VT.size() * 5; i++)
        outFile <<"-";
    outFile << endl;
    outFile << "|        |";
    for(int i = 0; i < VT.size(); i++)
    outFile << "    " << VT[i] << "    |";
    outFile << endl;
    for(int i = 0; i < (VT.size() + 1) * 10; i++)
        outFile <<"-";
    outFile << endl;
    for(int i = 0; i < VT.size(); i++)
    {
        outFile << "|   " << VT[i] << "    |";
        for(int j = 0; j < VT.size(); j++)
            outFile << "    " << relation[VT[i]][VT[j]] << "    |" ;
        outFile << endl;
        for(int i = 0; i < (VT.size() + 1) * 10; i++)
            outFile <<"-";
        outFile << endl;
    }
}



int main()
{
    string inputFile, outputFile;
    printf("Input the name of the input file name\n");
    cin >> inputFile;
    printf("Input the name of the ouput file name\n");
    cin >> outputFile;
    ifstream inFile(inputFile);
	if(!inFile)
	{
		cerr << "open file error" << endl;
		return -1;
	}
    handle_input(inFile); 
    inFile.close();

    ofstream outFile(outputFile);
    if(!outFile)
    {
        cerr << "open file error\n";
        return 1;
    }
        // puts ("************VT set*******************");
        // for ( int i = 0 ; i < VT.size() ; i++ )
        //     printf ( "%c " , VT[i] );
        // printf("\n");
        // puts("*************production*****************");
        // for ( int i = 0 ; i < VN_set.size() ; i++ )
        //     VN_set[i].print();
        // puts("************************************");
    find_origin();
    make_first();
    make_last();
    make_table(outFile);
    outFile.close();
    return 0;
}
