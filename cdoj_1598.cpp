#include <iostream>

using namespace std;
const int maxn=5e5;
const int inf=1e9;

struct P
{
    int l_ans,r_ans,sum,ans;
};

struct Node
{
    int L,R;
    int l_ans,r_ans,sum,ans;
};


int n,m;
int A[maxn+5];
Node tree[4*maxn+5];
P INF;

void build(int L,int R,int o,int A[])
{
    tree[o].L=L;
    tree[o].R=R;

    if (L==R)
    {
        tree[o].l_ans=tree[o].r_ans=tree[o].ans=A[R];
        tree[o].sum=A[R];
        return;
    }

    int mid=(L+R)>>1;
    int lo=o<<1;
    int ro=(o<<1)+1;
    build(L,mid,lo,A);
    build(mid+1,R,ro,A);

    tree[o].ans=max(max(tree[lo].ans,tree[ro].ans),tree[lo].r_ans+tree[ro].l_ans);
    tree[o].sum=tree[lo].sum+tree[ro].sum;
    tree[o].l_ans=max(tree[lo].l_ans,tree[lo].sum+tree[ro].l_ans);
    tree[o].r_ans=max(tree[ro].r_ans,tree[ro].sum+tree[lo].r_ans);
}

P query(int QL,int QR,int o)
{
    int L=tree[o].L;
    int R=tree[o].R;
    if (QL>R || QR<L) return INF;
    else if (L==R)
    {
        return (P){tree[o].sum,tree[o].sum,tree[o].sum,tree[o].sum};
    }
    else if (QL<=L && R<=QR)
    {
        return (P){tree[o].l_ans,tree[o].r_ans,tree[o].sum,tree[o].ans};
    }
    else
    {
        int mid=(L+R)>>1;
        if (QR<=mid)
        {
            return query(QL,QR,o<<1);
        }
        else if (QL>mid)
        {
            return query(QL,QR,(o<<1)+1);
        }
        P Lres = query(QL,QR,o<<1);
        P Rres = query(QL,QR,(o<<1)+1);
        P res;
        res.sum=Lres.sum+Rres.sum;
        res.l_ans = max(Lres.sum+Rres.l_ans,Lres.l_ans);
        res.r_ans = max(Rres.sum+Lres.r_ans,Rres.r_ans);
        res.ans = max(max(Rres.ans,Lres.ans),Rres.l_ans+Lres.r_ans);
        return res;
    }
}

void update(int o,int pos,int v)
{
    int L=tree[o].L;
    int R=tree[o].R;
    if (pos<L || pos>R) return;
    if (L==R)
    {
        tree[o].sum=v;
        tree[o].l_ans=tree[o].r_ans=tree[o].ans=tree[o].sum;
        return;
    }

    int mid=(L+R)>>1;
    int lo=o<<1;
    int ro=(o<<1)+1;


    if (pos<=mid)
    {
        update(lo,pos,v);
    }
    else
    {
        update(ro,pos,v);
    }
    tree[o].ans=max(max(tree[lo].ans,tree[ro].ans),tree[lo].r_ans+tree[ro].l_ans);
    tree[o].sum=tree[lo].sum+tree[ro].sum;
    tree[o].l_ans=max(tree[lo].l_ans,tree[lo].sum+tree[ro].l_ans);
    tree[o].r_ans=max(tree[ro].r_ans,tree[ro].sum+tree[lo].r_ans);
}

int main()
{
    #ifdef ex
    freopen("/home/zhongwang/Desktop/in","r",stdin);
    #endif // ex
    INF = (P){-inf,-inf,-inf,-inf};
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&A[i]);
    }
    build(1,n,1,A);

    int op,a,b;
    for (int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&op,&a,&b);
        if (op==1)
        {
            P res=query(a,b,1);
            printf("%d\n",res.ans);
        }
        else
        {
            update(1,a,b);
        }
    }
}
