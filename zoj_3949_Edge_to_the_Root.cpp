#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn=2e5;

vector<int> G[maxn+5];
vector<int> path;
int sz[maxn+5];
int mid[maxn+5];
LL val[maxn+5];
int n;
LL ans,sum;

void dfs(int x,int p,int d)
{
    path.push_back(x);
    sz[x]=1;
    for (int i=0;i<G[x].size();++i)
    {
        int e=G[x][i];
        if (e==p) continue;
        dfs(e,x,d+1);
        sz[x]+=sz[e];
    }
    sum+=d;
    
    if (path.size()>2) mid[x]=path[path.size()/2+1];
    else mid[x]=0;
    
    path.pop_back();
}

void dfs2(int x,int p)
{
    if (mid[x])
    {
        val[x]=val[p]+sz[x];
        if (mid[p]) val[x]-=(sz[mid[p]]-sz[x]);
    }
    else val[x]=0;
    
    ans=min(ans,sum-val[x]);
    
    for (int i=0;i<G[x].size();++i)
    {
        int e=G[x][i];
        if (e==p) continue;
        dfs2(e,x);
    }
    //printf("sz[%d]=%d val[%d]=%lld mid[%d]=%d\n",x,sz[x],x,val[x],x,mid[x]);
}

void solve()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        G[i].clear();
    }
    memset(sz,0,sizeof(sz));
    memset(mid,0,sizeof(mid));
    memset(val,0,sizeof(val));
    path.clear();
    sum=0;
    ans=1e18;
    
    int u,v;
    for (int i=1;i<=n-1;++i)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    dfs(1,-1,0);
    dfs2(1,-1);
    printf("%lld\n",ans);
}

int main(void)
{
    #ifdef ex
    freopen ("in.txt","r",stdin);
    #endif
    
    int T;
    scanf("%d",&T);
    
    while (T--)
    {
        solve();
    }
}