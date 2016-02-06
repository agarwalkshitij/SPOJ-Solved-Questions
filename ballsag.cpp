//Bottom Up approach

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<cmath>
#include<vector>
#include<string>
#include<cstring>
#include<stack>
#include<stdlib.h>
#include<queue>
#include<set>
#include<list>
#define pb(x) push_back(x);
#define gc getchar_unlocked
#define pc(x) putchar_unlocked(x);
#define inf 1<<30
    
using namespace std;

int main()
{	
	int n,ans;
	while(1)
	{
		cin>>n;
		if(n==0)
			break;
		int dp[n+1][n+1];
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=i;j++)
				cin>>dp[i][j];
		}
		ans=dp[1][1];
		for(int i=2;i<=n;i++)
		{
			dp[i][1]+=dp[i-1][1];
			if(dp[i][1]>ans)
				ans=dp[i][1];
			dp[i][i]+=dp[i-1][i-1];
			if(dp[i][i]>ans)
				ans=dp[i][i];
		}
		for(int i=3;i<=n;i++)
		{
			for(int j=2;j<i;j++)
			{
				dp[i][j]+=(dp[i-1][j-1]+dp[i-1][j]-dp[i-2][j-1]);
				if(dp[i][j]>ans)
					ans=dp[i][j];
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
