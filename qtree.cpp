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
#define N 10010
    
using namespace std;

typedef pair<int,int> pii;
vector<int> adj[N],indexx[N],costs[N];
int chainHead[N],chainIndex[N],posBase[N],baseArray[N],otherEnd[N],subSize[N],depth[N];
int pa[16][N],chainNo,ptr;
int st[6*N+10];

void build_tree(int v,int ss,int se)
{
	if(ss==se-1)
	{
		st[v]=baseArray[ss];
		return;
	}
	int mid=(ss+se)/2;
	build_tree(2*v,ss,mid);
	build_tree(2*v+1,mid,se);
	st[v] = max(st[2*v],st[2*v+1]);
}

void update_tree(int v,int ss,int se,int pos,int val)
{
	if(pos<ss||pos>=se)
		return;
	if(ss==se-1&&ss==pos)
	{
		st[v]=val;
		return;
	}
	int mid=(ss+se)/2;
	update_tree(2*v,ss,mid,pos,val);
	update_tree(2*v+1,mid,se,pos,val);
	st[v]=max(st[2*v],st[2*v+1]);
}

int query_tree(int v,int ss,int se,int qs,int qe)
{
	if(qs>=se||qe<=ss)
		return -1;
	if(ss>=qs&&se<=qe)
		return st[v];
	int mid=(ss+se)/2;
	int t1=query_tree(2*v,ss,mid,qs,qe);
	int t2=query_tree(2*v+1,mid,se,qs,qe);
	return max(t1,t2);
}

void HLD(int curNode,int prev,int cost)
{
	if(chainHead[chainNo]==-1)
		chainHead[chainNo]=curNode;
	chainIndex[curNode]=chainNo;
	posBase[curNode]=ptr;
	baseArray[ptr++]=cost;
	int ncost=-1,sc=-1;
	for(int i=0;i<adj[curNode].size();i++)
	{
		if(adj[curNode][i]!=prev)
		{
			if(sc==-1||subSize[adj[curNode][i]]>subSize[sc])
			{
				sc=adj[curNode][i];
				ncost=costs[curNode][i];
			}
		}
	}
	if(sc!=-1)
		HLD(sc,curNode,ncost);
	for(int i=0;i<adj[curNode].size();i++)
	{
		if(adj[curNode][i]!=prev)
		{
			if(adj[curNode][i]!=sc)
			{
				chainNo++;
				HLD(adj[curNode][i],curNode,costs[curNode][i]);
			}
		}
	}
}

int query_up(int u,int v)
{
	if(u==v)
		return 0;
	int uchain,vchain=chainIndex[v],ans=-1,temp;
	while(1)
	{
		uchain=chainIndex[u];
		if(uchain==vchain)
		{
			if(u==v)
				break;
			temp=query_tree(1,0,ptr,posBase[v]+1,posBase[u]+1);
			if(temp>ans)
				ans=temp;
			break;
		}
		temp=query_tree(1,0,ptr,posBase[chainHead[uchain]],posBase[u]+1);
		if(temp>ans)
			ans=temp;
		u=chainHead[uchain];
		u=pa[0][u];
	}
	return ans;
}

int getLCA(int u,int v)
{
	if(depth[u]<depth[v])
		swap(u,v);
	int diff=depth[u]-depth[v];
	for(int i=0;i<14;i++)
		if((diff>>i)&1)
			u=pa[i][u];
	if(u==v)
		return u;
	for(int i=13;i>=0;i--)
	{
		if(pa[i][u]!=pa[i][v])
		{
			u=pa[i][u];
			v=pa[i][v];
		}
	}
	return pa[0][u];
}

void query(int u,int v)
{
	int lca=getLCA(u,v);
	int ans=query_up(u,lca);
	int temp=query_up(v,lca);
	if(temp>ans)
		ans=temp;
	printf("%d\n",ans);
}

void change(int v,int val)
{
	int u=otherEnd[v];
	update_tree(1,0,ptr,posBase[u],val);
}

void dfs(int v,int prev,int d)
{
	pa[0][v]=prev;
	depth[v]=d;
	subSize[v]=1;
	for(int i=0;i<adj[v].size();i++)
	{
		if(adj[v][i]!=prev)
		{
			otherEnd[indexx[v][i]]=adj[v][i];
			dfs(adj[v][i],v,d+1);
			subSize[v]+=subSize[adj[v][i]];
		}
	}
}

int main()
{
	int t,n,a,b,c;
	scanf("%d",&t);
	while(t--)
	{
		ptr=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			adj[i].clear();
			costs[i].clear();
			indexx[i].clear();
			chainHead[i]=-1;
			for(int j=0;j<14;j++)
				pa[j][i]=-1;
		}
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--;b--;
			adj[a].pb(b);
			adj[b].pb(a);
			indexx[a].pb(i-1);
			indexx[b].pb(i-1);
			costs[a].pb(c);
			costs[b].pb(c);
		}
		chainNo=0;
		dfs(0,-1,0);
		HLD(0,-1,-1);
		//z	cout<<"ptr "<<ptr<<endl;
		build_tree(1,0,ptr);
		
		for(int i=1;i<14;i++)
			for(int j=0;j<n;j++)
				if(pa[i-1][j]!=-1)
					pa[i][j]=pa[i-1][pa[i-1][j]];
					
		char str[10];
		while(1)
		{
			scanf("%s",str);
			if(str[0]=='D')
				break;
			scanf("%d%d",&a,&b);
			if(str[0]=='Q')
				query(a-1,b-1);
			else
				change(a-1,b);
		}
	}
	return 0;
}
