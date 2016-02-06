#include<algorithm>
#include<iostream>
#include<map>

using namespace std;

long long int arr[2][2],n,M,l,h,mod,mat[2][2],arr1[2][2];

void multiply(long long int n)
{
	if(n==0||n==1)
		return ;
	multiply(n/2);
	arr1[0][0]=((arr[0][0]*arr[0][0])%mod+(arr[0][1]*arr[1][0])%mod)%mod;
	arr1[0][1]=((arr[0][0]*arr[0][1])%mod+(arr[0][1]*arr[1][1])%mod)%mod;
	arr1[1][0]=((arr[1][0]*arr[0][0])%mod+(arr[1][1]*arr[1][0])%mod)%mod;
	arr1[1][1]=((arr[1][0]*arr[0][1])%mod+(arr[1][1]*arr[1][1])%mod)%mod;
	arr[0][0]=arr1[0][0];
	arr[0][1]=arr1[0][1];
	arr[1][0]=arr1[1][0];
	arr[1][1]=arr1[1][1];	
	if(n%2==0)
	{
		return;
	}
	else
	{
		arr1[0][0]=((arr[0][0]*mat[0][0])%mod+(arr[0][1]*mat[1][0])%mod)%mod;
		arr1[0][1]=((arr[0][0]*mat[0][1])%mod+(arr[0][1]*mat[1][1])%mod)%mod;
		arr1[1][0]=((arr[1][0]*mat[0][0])%mod+(arr[1][1]*mat[1][0])%mod)%mod;
		arr1[1][1]=((arr[1][0]*mat[0][1])%mod+(arr[1][1]*mat[1][1])%mod)%mod;
		arr[0][0]=arr1[0][0];
		arr[0][1]=arr1[0][1];
		arr[1][0]=arr1[1][0];
		arr[1][1]=arr1[1][1];
		return;
	}
}

int main()
{
	long long int t,ans;
	cin>>t;
	while(t--)
	{
		cin>>n>>M;
		mod=M;
		mat[0][0]=1;mat[0][1]=1;mat[1][0]=1;mat[1][1]=0;
		arr[0][0]=1;arr[0][1]=1;arr[1][0]=1;arr[1][1]=0;
		multiply(n+1);
		ans=(((2%M)*(arr[0][0]+(-1)%M+M)%M)%M+(-1*n)%M+M)%M;
		cout<<ans<<endl;
	}
	return 0;
}
