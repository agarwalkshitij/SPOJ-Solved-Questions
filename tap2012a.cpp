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
#define INF 1<<30
    
using namespace std;

int main()
{
	int n,f,x,ct,temp;
	while(1)
	{
		cin>>n;
		f=0;
		if(n==-1)
			break;
		int arr[n+1];
		for(int i=1;i<=n;i++)
		{
			cin>>arr[i];
			if(arr[i]>i)
				f=1;
		}
		for(int i=n;i>=1;i--)
		{
			if(arr[i]==0)
				continue;
			else if(arr[i]<i)
			{
				f=1;
				break;
			}
			else
			{
				temp=i;
				break;
			}
		}
		if(f==0)
		{
			//cout<<"h"<<endl;
			n=temp;
			ct=0;	
			for(int i=n;i>=2;i--)
			{
				//cout<<"i "<<i<<endl;
				if(ct<=i)
				{
				//	cout<<"1"<<endl;
					temp=i-ct;
					ct++;
				}
				else
				{	
				//	cout<<"2"<<endl;
					x=ct%i;
					temp=i-x;
					ct+=(ceil((double)ct/i));
				}
				//cout<<"temp "<<temp<<endl;
				//cout<<"ct "<<ct<<endl;
				if((temp==0||temp==i)&&i!=n)
				{
					//cout<<"xy"<<endl;
					if(arr[i]==i)
						ct++;
				}
				else if(temp!=arr[i])
				{
					f=1;
					break;
				}
			}
		}
		if(f==0)
			cout<<"S"<<endl;
		else
			cout<<"N"<<endl;
	}
}
