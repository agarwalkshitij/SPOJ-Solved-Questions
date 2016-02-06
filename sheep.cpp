#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int arr[300][300],sh=0,wo=0,visit[300][300],m,n;

void bfs(pii a)
{
	int csh=0,cwo=0,flag=0;
	visit[a.first][a.second]=1;
	queue<pii> q;
	q.push(a);
	pii u,temp;
	int r,c;
	r=a.first;
	c=a.second;
	if(arr[r][c]==3)
		csh++;
	else if(arr[r][c]==4)
	{
		//cout<<"hi"<<endl;
		cwo++;
	}
	while(!q.empty())
	{
		u=q.front();
		//cout<<"u.first "<<u.first<<" u.second "<<u.second<<endl;
		q.pop();
		for(int i=1;i<=4;i++)
		{
			switch(i)
			{
				case 1:
					r=u.first;
					c=u.second+1;
					break;
				case 2:
					r=u.first+1;
					c=u.second;
					break;
				case 3:
					r=u.first;
					c=u.second-1;
					break;
				case 4:
					r=u.first-1;
					c=u.second;
					break;
			}
		//	cout<<"r "<<r<<" c "<<c<<endl;
			if(arr[r][c]==2)
			{
		//		cout<<"a"<<endl;
				continue;
			}
			if(r<1||r>n||c<1||c>m)
			{
		//		cout<<"b"<<endl;
				flag=1;
				continue;
			}
			if(visit[r][c]==0)
			{
		//		cout<<"c "<<arr[r][c]<<endl;
				visit[r][c]=1;
				if(arr[r][c]==3)
					csh++;
				else if(arr[r][c]==4)
				{
		//			cout<<"hi"<<endl;
					cwo++;
				}
				q.push(pii(r,c));
			}
		}
	}
//	cout<<"csh "<<csh<<" cwo "<<cwo<<endl;
	if(flag==1)
	{
		sh+=csh;
		wo+=cwo;
	}
	else
	{
		if(csh>cwo)
		{
			sh+=csh;
		}
		else
		{
			wo+=cwo;
		}
	}
	return ;
}

int main()
{
	cin>>n>>m;
	string s;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		for(int j=0;j<m;j++)
		{
			if(s[j]=='.')
				arr[i][j+1]=1;
			else if(s[j]=='#')
				arr[i][j+1]=2;
			else if(s[j]=='k')
				arr[i][j+1]=3;
			else if(s[j]=='v')
				arr[i][j+1]=4;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(arr[i][j]!=2&&visit[i][j]==0)
			{
//				cout<<"i "<<i<<" j "<<j<<endl;
//				cout<<"h"<<endl;
				bfs(pii(i,j));
//				cout<<"sh "<<sh<<" wo "<<wo<<endl;
			}
		}
	}
	cout<<sh<<" "<<wo<<endl;
	return 0;
}
