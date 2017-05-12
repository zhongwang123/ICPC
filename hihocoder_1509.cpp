#include <bits/stdc++.h>

using namespace std;

int n;
long long A[100];
int vis[100];
vector<int> v[100];

void check(int x)
{
    v[x].clear();
    for (int i=0;i<=59;++i)
    {
        if (A[x] & (1LL<<i)) v[x].push_back(1);
        else v[x].push_back(0);
    }
}

bool f(int x,int y)
{
    for (int i=59;i>=0;--i)
    {
        if (v[x][i]!=v[y][i])
        {
            int bit=0;
            if (v[x][i]==1) bit=1;
            if (vis[i]!=-1 && vis[i]!=bit)
            {
                return false;
            }
            else
            {
                vis[i]=bit;
                return true;
            }
        }
    }
    return true;
}

void solve()
{
    memset(vis,-1,sizeof(vis));
    for (int i=1;i<=n;++i)
    {
        scanf("%lld",&A[i]);
        check(i);
    }
    
    for (int i=1;i<=n-1;++i)
    {
        if (!f(i,i+1))
        {
            printf("0\n");
            return;
        }
    }
    
    int cnt=0;
    for (int i=0;i<=59;++i)
    {
        if (vis[i]==-1) ++cnt;
    }
    printf("%lld\n",1LL<<(cnt));
}

int main(void)
{
    #ifdef ex
    freopen ("in.txt","r",stdin);
    #endif
    
    while (scanf("%d",&n)==1)
    {
        solve();
    }
}