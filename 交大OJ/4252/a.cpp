#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<climits>
#include<queue>
#include<set>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define swap(x,y) (x^=y,y^=x,x^=y)
using namespace std;
typedef long long ll;
const int N=1e6+50;
template<typename T>inline void read(T &x)
{
    x=0;
    T f=1;
    char c=getchar();
    for(; c<'0'||c>'9'; c=getchar()) if(c=='-') f=-1;
    for(; c>='0'&&c<='9'; c=getchar()) x=(x<<1)+(x<<3)+(c&15);
}
template<typename T>inline void print(T x)
{
    if(x<0) putchar('-'),x*=-1;
    if(x>=10) print(x/10);
    putchar(x%10+'0');
}
ll a[N],b[N],c[N];
struct node
{
    ll v,x,f;
};
node qq;
multiset<ll>pq;
priority_queue<node>q;
bool operator < (node a,node b)
{
    return a.v>b.v;
}
ll fac(ll i,ll x) 
{
    return a[i]*x*x+b[i]*x+c[i];
}
int n,k;
ll t[N];
int main()
{
    read(n);read(k);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld%lld",a+i,b+i,c+i);
        t[i]=(-b[i])/(2*a[i]);
        q.push((node){fac(i,t[i]),t[i],i});
    }
    ll e,w,r,y;
    for(int i=1;i<=2*k;i++) 
    {
        qq=q.top();
        pq.insert(qq.v);
        q.pop();
        if(qq.x==t[qq.f]){
        e=fac(qq.f,qq.x+1);
        w=fac(qq.f,qq.x-1);
        r=qq.x+1;
        y=qq.x-1;
        q.push((node){e,r,qq.f});
        q.push((node){w,y,qq.f});
        }
        else if(qq.x>t[qq.f])
        {
            e=fac(qq.f,qq.x+1);
            q.push((node){e,qq.x+1,qq.f});
        }
        else
        {
            e=fac(qq.f,qq.x-1);
            q.push((node){e,qq.x-1,qq.f});
        }
    }
    int temp=0;
    for(multiset<ll>::iterator it=pq.begin();it!=pq.end();it++) //set的遍历
    {
        cout<<*it<<' ';
        temp++;
        if(temp==k)
            break;
    }
    cout<<endl;
    return 0;
}