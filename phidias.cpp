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

typedef pair<int,int> pii;

int w[210],h[210],dp[610][610],n;

int solve(int W,int H)
{
	if(dp[W][H]!=-1)
		return dp[W][H];
	int res=W*H;
	for(int i=0;i<n;i++)
	{
		if(W-w[i]<0||H-h[i]<0)
			continue;
		res=min(res,solve(W,H-h[i])+solve(W-w[i],h[i]));
		res=min(res,solve(W-w[i],H)+solve(w[i],H-h[i]));
	}
	dp[W][H]=res;
	return dp[W][H];
}

int main()
{
	int t,W,H,ans;
	cin>>t;
	while(t--)
	{
		memset(dp,-1,sizeof dp);
		cin>>W>>H;	
		cin>>n;
		for(int i=0;i<n;i++)
			cin>>w[i]>>h[i];
		ans=solve(W,H);
		cout<<ans<<endl;
	}
	return 0;
}
