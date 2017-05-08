#include <bits/stdc++.h>

using namespace std;
const int maxn=5000;

char s[maxn+5];
int lsum[maxn+5];
int rsum[maxn+5];
int Count[maxn+5];

int len;

bool solve()
{
    len = strlen(s+1);

    int test_cnt=0;
    int test_min=1e9;
    for (int i=1;i<=len;++i)
    {
        if (s[i]=='(') ++test_cnt;
        else --test_cnt;
        test_min=min(test_cnt,test_min);
    }
    if (test_min>=0 && test_cnt==0) return true;

    memset(lsum,0,sizeof(lsum));
    memset(rsum,0,sizeof(rsum));
    memset(Count,0,sizeof(Count));

    for(int i=1;i<=len;++i)
    {
        lsum[i]=lsum[i-1]+(s[i]=='(');
        rsum[i]=rsum[i-1]+(s[i]==')');
    }

    for (int i=1;i<=len;++i)
    {
        int cnt=0;
        int res=1e9;
        for (int j=i;j<=len;++j)
        {
            if (s[j]=='(') ++cnt;
            else --cnt;
            res=min(res,cnt);
        }
        Count[i]=res;
    }

    int lcheck=0;
    for (int i=1;i<=len;++i)
    {
        if (i>1)
        {
            if (s[i-1]=='(') lcheck++;
            else lcheck--;
        }
        if (lcheck<0) break;
        int ncnt=lcheck;
        for (int j=i;j<=len;++j)
        {
            int lcnt=lsum[i-1]+lsum[len]-lsum[j]+(rsum[j]-rsum[i-1]);
            int rcnt=rsum[i-1]+rsum[len]-rsum[j]+(lsum[j]-lsum[i-1]);
            if (s[j]=='(') --ncnt;
            else ++ncnt;
            if (ncnt<0) break;
            if (lcnt!=rcnt) continue;

            if (j==len && ncnt==0) return true;
            else if (Count[j+1]+ncnt>=0) return true;
        }
    }
    return false;
}

int main()
{
    #ifdef ex
    freopen ("in","r",stdin);
    #endif // ex
    while (scanf("%s",s+1)==1)
    {
        bool f=solve();
        if (f) printf("possible\n");
        else printf("impossible\n");
    }
}
