#include<cstdio>
#include<algorithm>
#include<iostream>
#include<map>
#include<stdlib.h>
#include<cmath>

using namespace std;

long long int  n,k,p;

long long int  gcd(long long int  a,long long int  b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

long long int  lcm(long long int  a,long long int  b)
{
	return ((a/gcd(a,b))*b);
}

void subsets(long long int lo,long long int hi,long long int coprime[],long long int product,long long int t)
{
	long long int product1;
	for(long long int i=lo;i<=hi;i++)
	{
		product1=lcm(product,coprime[i]);
		if(t%2!=0)
			n=n-p/product1;
		else
			n=n+p/product1;
		subsets(i+1,hi,coprime,product1,t+1);
	}
}

int main()
{
	long long int i,j,a,b,num=0,m,y,x,product;
	cin>>n>>k;
	m=k,p=n;
	long long int  *coprime=(long long int *)calloc(m,sizeof(int));
	for(i=0;i<k;i++)
	{
		cin>>coprime[i];
	}
	subsets(0,k-1,coprime,1,1);
	cout<<n<<endl;
	return 0;
}
