#include <bits/stdc++.h>

using namespace std;
const int maxn=500;

int n;
int H[maxn+5];
int C[maxn+5];
long long dp[maxn*100+5];

void solve()
{
    scanf("%d",&n);
    memset(dp,-1,sizeof(dp));
    for (int i=1;i<=n;++i)
    {
        scanf("%d%d",&H[i],&C[i]);
    }
    
    dp[0]=0;
    for (int i=1;i<=n;++i)
    {
        for (int j=100*n;j>=C[i];--j)
        {
            if (dp[j-C[i]]!=-1) dp[j]=max(dp[j],dp[j-C[i]]+H[i]);
        }
    }
    
    long long ans=-1e18;
    for (int i=0;i<=100*n;++i)
    {
        if (dp[i]!=-1)
        {
            ans=max(ans,dp[i]*dp[i]-dp[i]*i-i*i);
        }
    }
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