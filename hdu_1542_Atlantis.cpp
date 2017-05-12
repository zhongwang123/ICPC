#include <bits/stdc++.h>

using namespace std;

const int maxn=1e5;

struct Line
{
    double x1,x2;
    double h;
    int flag;
    
    bool operator < (const Line& rhs) const
    {
        return h<rhs.h;
    }
};

struct treenode
{
    int L,R;
    int lazy;
    double sum;
    double sz;
};

struct SgTree
{
    treenode tree[8*maxn+5];
    
    double SumQuery(int QL,int QR,int o)
    {
        int L=tree[o].L;
        int R=tree[o].R;
        if (QL<=L && R<=QR) return tree[o].sum;
        else if (QL>R || QR<L) return 0;
        else
        {
            return SumQuery(QL,QR,o*2)+SumQuery(QL,QR,o*2+1);
        }
    }
    
    void update(int QL,int QR,int v,int o)
    {
        int L=tree[o].L;
        int R=tree[o].R;
        if (QL<=L && R<=QR)
        {
            tree[o].lazy+=v;
            check(o);
        }
        else if (QL>R || QR<L) return;
        else if (L!=R)
        {
            push_down(o);
            update(QL,QR,v,2*o);
            update(QL,QR,v,2*o+1);
            push_up(o);
        }
    }
    
    void check(int o)
    {
        if (tree[o].lazy>0) tree[o].sum=tree[o].sz;
        else if (tree[o].lazy==0)
        {
            if (tree[o].L==tree[o].R)
            {
                tree[o].sum=0;
            }
            else
            {
                tree[o].sum=tree[2*o].sum+tree[2*o+1].sum;
            }
        }
        else
        {
            push_down(o);
            push_up(o);
        }
    }
    
    void push_down(int o)
    {
        int lazy=tree[o].lazy;
        tree[2*o].lazy+=lazy;
        tree[2*o+1].lazy+=lazy;
        check(2*o);
        check(2*o+1);
        tree[o].lazy=0;
        tree[o].sum=0;
    }
    
    void push_up(int o)
    {
        tree[o].sum=tree[2*o].sum+tree[2*o+1].sum;
    }
    
    void build(int L,int R,int o,double A[])
    {
        tree[o].L=L;
        tree[o].R=R;
        tree[o].lazy=0;
        tree[o].sum=0;
        
        if (L<R)
        {
            int mid=(L+R)>>1;
            build(L,mid,2*o,A);
            build(mid+1,R,2*o+1,A);
            tree[o].sz=tree[2*o].sz+tree[2*o+1].sz;
        }
        else
        {
            tree[o].sz=A[R];
        }
    }
};

int n;
Line L[205];
SgTree T;
vector<double> X;
double sg[2*maxn+5];

void solve(int iCase)
{
    X.clear();
    
    double x1,x2,y1,y2;
    for (int i=1;i<=n;++i)
    {
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        L[i]=(Line){x1,x2,y1,-1};
        L[i+n]=(Line){x1,x2,y2,1};
        X.push_back(x1);
        X.push_back(x2);
    }
    
    sort(L+1,L+1+2*n);
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
    for (int i=1;i<X.size();++i)
    {
        sg[i]=X[i]-X[i-1];
    }
    
    T.build(1,X.size()-1,1,sg);
    double curH=0;
    double ans=0;
    
    for (int i=1;i<=2*n;++i)
    {
        int lb=lower_bound(X.begin(),X.end(),L[i].x1)-X.begin()+1;
        int rb=lower_bound(X.begin(),X.end(),L[i].x2)-X.begin();
        
        ans+=1LL*T.SumQuery(1,X.size()-1,1)*(L[i].h-curH);
        T.update(lb,rb,-L[i].flag,1);
        curH=L[i].h;
    }
    printf("Test case #%d\n",iCase);
    printf("Total explored area: %.2f\n\n",ans);
}

int main(void)
{
    #ifdef ex
    freopen ("in.txt","r",stdin);
    #endif
    
    int iCase=0;
    while (scanf("%d",&n)==1)
    {
        if (n==0) break;
        ++iCase;
        solve(iCase);
    }
}