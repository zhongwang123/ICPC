#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn=1e5;
const int inf=1e9;

struct segQuery
{
    int l,r;
    bool operator < (const segQuery& rhs) const
    {
        if (r!=rhs.r) return r<rhs.r;
        else return l<rhs.l;
    }
};

struct Tnode
{
    LL sum,max_sum;
    LL lazy,max_lazy;
};

int n,q,Tsize;
int A[maxn+5],pos[2*maxn+5];
LL ans[maxn+5];
vector <int> v[maxn+5];
segQuery Q[maxn+5];
Tnode T[4*maxn+5];

void push_down(int k)
{
    int l=(k<<1);
    int r=(k<<1)+1;

    int lazy=T[k].lazy;
    int max_lazy=T[k].max_lazy;

    T[l].max_lazy=max(T[l].max_lazy,T[l].lazy+max_lazy);
    T[l].lazy+=lazy; 
    T[l].max_sum=max(T[l].max_sum,T[l].sum+max_lazy);
    T[l].sum+=lazy;

    T[r].max_lazy=max(T[r].max_lazy,T[r].lazy+max_lazy);
    T[r].lazy+=lazy; 
    T[r].max_sum=max(T[r].max_sum,T[r].sum+max_lazy);
    T[r].sum+=lazy;

    T[k].lazy=0;
    T[k].max_lazy=0;
}

void push_up(int k)
{
    int l=(k<<1);
    int r=(k<<1)+1;
    T[k].sum=max(T[l].sum,T[r].sum);
    T[k].max_sum=max(T[l].max_sum,T[r].max_sum);
}

void update(int k,int cl,int cr,int l,int r,int v)
{
    if (r<cl || cr<l) return;
    else if (l<=cl && cr<=r)
    {
        T[k].lazy+=v;
        T[k].sum+=v;
        T[k].max_sum=max(T[k].max_sum,T[k].sum);
        T[k].max_lazy=max(T[k].max_lazy,T[k].lazy);
        return;
    }
    else
    {
        int mid=(cl+cr)>>1;
        push_down(k);
        update(k<<1,cl,mid,l,r,v);
        update((k<<1)+1,mid+1,cr,l,r,v);
        push_up(k);
    }
}

LL query(int k,int cl,int cr,int l,int r)
{
    if (r<cl || cr<l) return -1;
    else if (l<=cl && cr<=r) return T[k].max_sum;
    else
    {
        push_down(k);
        int mid=(cl+cr)>>1;
        LL res=0;
        res=max(res,query(k<<1,cl,mid,l,r));
        res=max(res,query((k<<1)+1,mid+1,cr,l,r));
        push_up(k);
        return res;
    }
}

void solve(void)
{
    for (int i=1;i<=n;++i)
        scanf("%d",&A[i]);
    for (int i=1;i<=n;++i)
        v[i].clear();

    scanf("%d",&q);
    for (int i=1;i<=q;++i)
    {
        scanf("%d%d",&Q[i].l,&Q[i].r);
        v[Q[i].r].push_back(i);
    }

    memset(pos,0,sizeof(pos));
    memset(T,0,sizeof(T));

    Tsize=1;
    while (Tsize<n) Tsize<<=1;

    for (int i=1;i<=n;++i)
    {
        update(1,1,Tsize,pos[A[i]+maxn]+1,i,A[i]);
        pos[A[i]+maxn]=i;

        for (int j=0;j<v[i].size();++j)
        {
            int e=v[i][j];
            ans[e]=query(1,1,Tsize,Q[e].l,Q[e].r);
        }
    }

    for (int i=1;i<=q;++i)
    {
        printf("%lld\n",ans[i]);
    }
}

int main(void)
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while (scanf("%d",&n)==1)
    {
        solve();
    }
}