#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn=1e5;

struct Edge
{
    int u,v;
};

int vis[maxn+5];
int cnt[maxn+5];
vector<int> v;
vector<int> G[maxn+5];
vector<Edge> E;
int n;

void print()
{
    for (auto e:E)
    {
        printf("%d %d\n",e.u,e.v);
    }
}

void solve()
{
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    v.clear();
    E.clear();
    for (int i=1;i<=n;++i)
    {
        G[i].clear();
    }

    for (int i=1;i<=n-2;++i)
    {
        int x=rand()%n+1;
        v.push_back(x);
        cnt[x]++;
    }

    for (int i=0;i<n-2;++i)
    {
        int e=v[i];
        for (int j=1;j<=n;++j)
        {
            if (!vis[j] && !cnt[j])
            {
                vis[j]=true;
                G[e].push_back(j);
                G[j].push_back(e);
                E.push_back((Edge){e,j});
                break;
            }
        }
        --cnt[e];
    }

    vector<int> last_p;
    for (int i=1;i<=n;++i)
    {
        if (!vis[i]) last_p.push_back(i);
    }

    G[last_p[0]].push_back(last_p[1]);
    G[last_p[1]].push_back(last_p[0]);
    E.push_back((Edge){last_p[0],last_p[1]});

    print();
}

int main(void)
{
	#ifdef ex
	//freopen ("in","r",stdin);
	#endif

	while (scanf("%d",&n)==1)
    {
        solve();
    }
}
