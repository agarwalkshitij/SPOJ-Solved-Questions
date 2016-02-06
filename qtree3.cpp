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
#define N 100010
#define MXN 1000000000000000000

using namespace std;

vector<int> adj[N];
int subSize[N],parent[N],chainNo,ptr,chainHead[N],posBase[N],chainInd[N],st[6*N],color[N];
int baseOrg[N],n;

void update_tree(int cur,int ss,int se,int u)
{
	if(ss>u||se<u)
		return;
	if(ss==se&&ss==u)
	{
		if(st[cur]==-1)
			st[cur]=u;
		else
			st[cur]=-1;
		return;
	}
	int mid=(ss+se)/2;
	update_tree(2*cur,ss,mid,u);
	update_tree(2*cur+1,mid+1,se,u);
	if(st[2*cur]==-1||(st[2*cur+1]!=-1&&st[2*cur+1]<st[2*cur]))
		st[cur]=st[2*cur+1];
	else
		st[cur]=st[2*cur];
}

int query_tree(int cur,int ss,int se,int qs,int qe)
{
	if(qs>se||qe<ss)
		return -1;
	if(ss>=qs&&se<=qe)
		return st[cur];
	int mid=(ss+se)/2;
	int t1=query_tree(2*cur,ss,mid,qs,qe);
	int t2=query_tree(2*cur+1,mid+1,se,qs,qe);
	if(t1==-1||(t2!=-1&&t2<t1))
		return t2;
	else
		return t1;
}

void HLD(int cur,int prev)
{
	if(chainHead[chainNo]==-1)
		chainHead[chainNo]=cur;
	posBase[cur]=ptr;
	baseOrg[ptr++]=cur;
	chainInd[cur]=chainNo;
	int sc=-1;
	for(int i=0;i<adj[cur].size();i++)
	{
		if(adj[cur][i]!=prev)
		{
			if(sc==-1||subSize[adj[cur][i]]>subSize[sc])
				sc=adj[cur][i];
		}
	}
	if(sc!=-1)
		HLD(sc,cur);
		
	for(int i=0;i<adj[cur].size();i++)
	{
		if(adj[cur][i]!=prev&&adj[cur][i]!=sc)
		{
			chainNo++;
			HLD(adj[cur][i],cur);
		}
	}
}

void dfs(int cur,int prev)
{
	subSize[cur]=1;
	parent[cur]=prev;
	for(int i=0;i<adj[cur].size();i++)
	{
		if(adj[cur][i]!=prev)
		{
			dfs(adj[cur][i],cur);
			subSize[cur]+=subSize[adj[cur][i]];
		}
	}
}

int query_up(int u,int v)
{
	//cout<<"Inside query up"<<endl;
	int uchain,vchain=chainInd[v],temp,ans=-1;	
	while(1)
	{
		uchain=chainInd[u];
		//cout<<"uchain "<<uchain<<" vchain "<<vchain<<endl;
		if(uchain==vchain)
		{
			//cout<<"hello"<<endl;
			temp=query_tree(1,0,ptr-1,posBase[v],posBase[u]);
			//cout<<"temp "<<temp<<endl;
			if(ans==-1||(temp!=-1&&temp<ans))
				ans=temp;
			break;
		}
		temp=query_tree(1,0,ptr-1,posBase[chainHead[uchain]],posBase[u]);
		if(ans==-1||(temp!=-1&&temp<ans))
			ans=temp;
		u=chainHead[uchain];
		u=parent[u];
	}
	//cout<<"ans "<<ans<<endl;
	return ans;
}

int query(int u,int v)
{
	int lca=u,t;
	//cout<<"Inside query lca="<<lca<<endl;
	int ans=color[posBase[u]]>0?u:-1;
	//cout<<"ans "<<ans<<endl;
	if(v!=lca)
	{
		//cout<<"hello"<<endl;
		t=query_up(v,lca);
		//cout<<" t "<<t<<endl;
		if(ans==-1||(t!=-1&&t<ans))
			ans=t;
	}
	return ans;
}

void change(int u)
{
	//cout<<"Inside change u="<<u<<endl;
	color[posBase[u]]=(-1)*color[posBase[u]];
	/*for(int i=0;i<n;i++)
		cout<<color[i]<<" ";
	cout<<endl;*/
	update_tree(1,0,ptr-1,posBase[u]);
	/*for(int i=1;i<2*n+1;i++)
		cout<<st[i]<<" ";
	cout<<endl;*/
}

int main()
{
	int q,a,b,ans;
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		cin>>a>>b;
		a--;b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	ptr=0;
	chainNo=0;
	memset(chainHead,-1,sizeof chainHead); 
	memset(st,-1,sizeof st);
	memset(color,-1,sizeof color);
	dfs(0,-1);
	/*for(int i=0;i<n;i++)
		cout<<subSize[i]<<" ";
	cout<<endl;*/
	HLD(0,-1);
	/*for(int i=0;i<n;i++)
		cout<<posBase[i]<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)
		cout<<chainInd[i]<<" ";
	cout<<endl;
	cout<<"ptr "<<ptr<<endl;*/
	for(int i=1;i<=q;i++)
	{
		cin>>a>>b;
		b--;
		//cout<<"b "<<b<<endl;
		if(a==0)
		{
			change(b);
		}
		else
		{
			ans=query(0,b);
			//cout<<"ans "<<ans<<endl;
			if(ans!=-1)
				ans=baseOrg[ans]+1;
			cout<<ans<<endl;
		}
	}
	return 0;
}
