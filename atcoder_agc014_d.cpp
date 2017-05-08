#include <bits/stdc++.h>

using namespace std;
const int maxn=1e5;

int n;
int deg[maxn+5];
int vis[maxn+5];
vector <int> G[maxn+5];
queue <int> Q;

void solve()
{
    memset(deg,0,sizeof(deg));
    memset(vis,0,sizeof(vis));
    while (!Q.empty()) Q.pop();
    for (int i=1;i<=n;++i)
    {
        G[i].clear();
    }

    int u,v;
    for (int i=1;i<=n-1;++i)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        ++deg[u];
        ++deg[v];
    }

    for (int i=1;i<=n;++i)
    {
        if (deg[i]==1)
        {
            Q.push(i);
        }
    }

    int cnt=0;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for (int i=0;i<G[x].size();++i)
        {
            int e=G[x][i];
            if (!vis[e])
            {
                vis[e]=true;
                vis[x]=true;
                cnt+=2;
                for (int j=0;j<G[e].size();++j)
                {
                    int ee=G[e][j];
                    if (vis[ee]) continue;
                    --deg[ee];
                    if (deg[ee]==1) Q.push(ee);
                }
            }
        }
    }

    if (cnt!=n)
    {
        printf("First\n");
    }
    else
    {
        printf("Second\n");
    }
}

int main()
{
    #ifdef ex
    freopen ("/home/zhongwang/Desktop/in","r",stdin);
    #endif // ex

    while (scanf("%d",&n)==1)
    {
        solve();
    }
}
