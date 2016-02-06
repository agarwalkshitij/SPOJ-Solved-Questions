#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#define int_max 1<<30

using namespace std;

typedef struct
{
	int firsthalf,secondhalf,index;
}tuple;

int suffixrank[20][30000],m;

bool cmp(tuple a,tuple b)
{
	if(a.firsthalf==b.firsthalf)
		return a.secondhalf<b.secondhalf;
	else
		return a.firsthalf<b.firsthalf;
}

void compute_suffix(string s)
{
	memset(suffixrank,0,sizeof suffixrank);
	int stp,cnt,n=s.size(),crank;
	tuple l[n+1];	
	for(int i=0;i<s.size();i++)
		suffixrank[0][i]=s[i]-'a';
	for(cnt=1,stp=1;cnt<n;cnt*=2,stp++)
	{
		for(int i=0;i<n;i++)
		{
			l[i].firsthalf=suffixrank[stp-1][i];
			l[i].secondhalf=i+cnt<n?suffixrank[stp-1][i+cnt]:int_max;
			l[i].index=i;
		}
		sort(l,l+n,cmp);
		suffixrank[stp][l[0].index]=0;
		crank=0;
		for(int i=1;i<n;i++)
		{
			if(l[i-1].firsthalf!=l[i].firsthalf||l[i-1].secondhalf!=l[i].secondhalf)
				crank++;
			suffixrank[stp][l[i].index]=crank;
		}
	}
	/*for(int i=0;i<n;i++)	
		cout<<l[i].index<<endl;*/
	cout<<l[0].index+1<<endl;
}

int main()
{
	int n;
	cin>>n;
	string s;
	while(n--)
	{
		cin>>s;
		m=s.size();
		for(int i=0;i<m;i++)
			s.push_back(s[i]);
		//cout<<s<<endl;
		compute_suffix(s);
	}
	return 0;
}
