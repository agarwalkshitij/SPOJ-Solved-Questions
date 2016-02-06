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

int abso(int a,int b)
{
	if(a<b)
		return b-a;
	else
		return a-b;
}

typedef struct
{
	int a,b,pos,c;
}node;

bool cmp(node x,node y)
{
	if(x.c==y.c)
		return x.b<y.b;
	return x.c<y.c;
}

int num[1000005],ans=1;

void remove(int val)
{
	num[val]--;
	if(num[val]==0)
		ans--;
}

void add(int val)
{
	num[val]++;
	if(num[val]==1)
		ans++;
}

int main()
{
	int q,n,s;
	scanf("%d",&n);
	s=(int)(1.514*sqrt(n)+1);
	int arr[n+1];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	scanf("%d",&q);
	node query[q+1];
	for(int i=0;i<q;i++)
	{
		scanf("%d%d",&query[i].a,&query[i].b);
		query[i].a--;
		query[i].b--;
		query[i].c=(query[i].a+1)/s;
		query[i].pos=i;
	}
	sort(query,query+q,cmp);
	/*for(int i=0;i<q;i++)
		cout<<query[i].a<<" "<<query[i].b<<" "<<query[i].pos<<endl;*/
	int cur_left=0,cur_right=0;
	num[arr[0]]++;
	int fans[q+1];
	for(int i=0;i<q;i++)
	{
		//cout<<"i "<<i<<" "<<query[i].a<<" "<<query[i].b<<endl;
		//cout<<cur_left<<" "<<cur_left<<endl;
		while(cur_left<query[i].a)
		{
			remove(arr[cur_left]);
			cur_left++;
		}
		while(cur_left>query[i].a)
		{
			cur_left--;
			add(arr[cur_left]);
		}
		while(cur_right>query[i].b)
		{
			remove(arr[cur_right]);
			cur_right--;
		}
		while(cur_right<query[i].b)
		{
			cur_right++;
			add(arr[cur_right]);
		}
		//cout<<cur_left<<" "<<cur_right<<endl;
		//cout<<"ans "<<ans<<endl;
		//cout<<" "<<num[31]<<endl;
		/*if(cur_left<0)
			cur_left=0;
		if(cur_right>n-1)
			cur_right=n-1;*/
		fans[query[i].pos]=ans;
	}
	for(int i=0;i<q;i++)
		printf("%d\n",fans[i]);
	return 0;
}
