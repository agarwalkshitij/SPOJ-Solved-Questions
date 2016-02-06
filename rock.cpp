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

int dp[300][300],zero[300][300],one[300][300],n;

int solve(int i,int j)
{
	//cout<<"i "<<i<<" j "<<j<<endl;
	int x;
	//cin>>x;
	int temp,ans=0;
	if(i>j||j<0||i>=n)
		return 0;
	if(dp[i][j]!=-1)
		return dp[i][j];
	if(one[i][j]>zero[i][j])
		dp[i][j]=j-i+1;
	else
	{
		for(int k=i;k<j;k++)
		{
			//cout<<"k "<<k<<endl;
			temp=solve(i,k)+solve(k+1,j);
			if(temp>ans)
			ans=temp;
		}
		dp[i][j]=ans;
	}
	return dp[i][j];
}

int main()
{
	int t,ans,temp;
	cin>>t;
	string s;
	while(t--)
	{
		ans=0;
		memset(dp,-1,sizeof dp);
		memset(zero,0,sizeof zero);
		memset(one,0,sizeof one);
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='1')
				one[i][i]=1;
			else 
				zero[i][i]=1;
		}
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				zero[i][j]=zero[i][j-1]+zero[j][j];
				one[i][j]=one[i][j-1]+one[j][j];
				//cout<<"i "<<i<<" j "<<j<<" zero "<<zero[i][j]<<" one "<<one[i][j]<<endl;
			}
		}
		int i,j,x,y;
		i=0;
		j=n-1;
		if(one[i][j]>zero[i][j])
		{
			dp[i][j]=j-i+1;
		}
		else
		{
			for(int k=0;k<n;k++)
			{
				//cout<<"k "<<k<<endl;
				x=solve(i,k);
				//cout<<"x "<<x<<endl;
				y=solve(k+1,j);
				//cout<<"y "<<y<<endl;
				temp=x+y;
				//cout<<"temp "<<temp<<endl;
				if(temp>ans)
					ans=temp;
			}
			dp[i][j]=ans;
		}
		cout<<dp[0][n-1]<<endl;
	}
	return 0;	
}
