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

int dp[2001][2001],n,arr[2005];

int solve(int i,int j)
{
	if(i>j||i>n||j<1)
		return 0;
	if(dp[i][j]!=0)
		return dp[i][j];
	dp[i][j]=max(solve(i+1,j)+arr[i]*(n-(j-i)),solve(i,j-1)+arr[j]*(n-(j-i)));
	return dp[i][j];
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	dp[1][n]=max(solve(2,n)+arr[1]*(n-(n-1)),solve(1,n-1)+arr[n]*(n-(n-1)));
	cout<<dp[1][n]<<endl;
	return 0;
}
