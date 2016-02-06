#include <bits/stdc++.h>

#define mod 1000000007
#define inf 1<<30
#define pb push_back
#define MAX 50009

using namespace std;

long long *lazy,*tree;

void update(long long lazy[],long long tree[],long long ss,long long se,long long qs,long long qe,long long val,long long node)
{
	if(lazy[node]!=0)
	{
		tree[node]+=(se-ss+1)*lazy[node];
		if(ss!=se)
		{
			lazy[2*node+1]+=lazy[node];
			lazy[2*node+2]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(ss>se||ss>qe||se<qs)
		return;
	if(ss>=qs&&se<=qe)
	{
		tree[node]+=(se-ss+1)*val;
		if(ss!=se)
		{
			lazy[2*node+1]+=val;
			lazy[2*node+2]+=val;
		}
		return ;
	}
	long long mid=(ss+se)/2;
	update(lazy,tree,ss,mid,qs,qe,val,2*node+1);
	update(lazy,tree,mid+1,se,qs,qe,val,2*node+2);
	tree[node]=tree[2*node+1]+tree[2*node+2];
}

long long query(long long lazy[],long long tree[],long long ss,long long se,long long qs,long long qe,long long node)
{
	if(ss>se||ss>qe||se<qs)
		return 0;
	if(lazy[node]!=0)
	{
		tree[node]+=(se-ss+1)*lazy[node];
		if(ss!=se)
		{
			lazy[2*node+1]+=lazy[node];
			lazy[2*node+2]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(ss>=qs && se<=qe)
		return tree[node];
	long long mid=(ss+se)/2;
	long long p1=query(lazy,tree,ss,mid,qs,qe,2*node+1);
	long long p2=query(lazy,tree,mid+1,se,qs,qe,2*node+2);
	return p1+p2;
}

int main()
{
	long long t,n,c,x,q,a,b;
	long long ans;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&q);
		lazy=(long long *)calloc((5*n),sizeof(long long));
		tree=(long long *)calloc((5*n),sizeof(long long));
		while(q--)
		{
			scanf("%lld",&x);
			if(x==0)
			{
				scanf("%lld%lld%lld",&a,&b,&c);
				update(lazy,tree,1,n,a,b,c,0);
			}
			else
			{
				scanf("%lld%lld",&a,&b);
				ans=query(lazy,tree,1,n,a,b,0);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
