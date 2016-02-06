//Bottom Up approach

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

int main()
{
	long long int n,ans,temp,t1,t2;
	while(1)
	{
		cin>>n;
		ans=0;
		if(n==0)
			break;
		long long int arr[n+1];
		for(long long int i=1;i<=n;i++)
			cin>>arr[i];
		stack<int> st;
		for(long long int i=1;i<=n;i++)
		{
			//cout<<"i "<<i<<endl;
			if(st.empty()||arr[st.top()]<=arr[i])
			{
				//cout<<"hello1"<<endl;
				st.push(i);
			}
			else
			{
				//cout<<"hello2"<<endl;
				while(!st.empty()&&arr[st.top()]>arr[i])
				{
					t1=st.top();
					//cout<<"t1 "<<t1<<endl;
					st.pop();
					t2=st.empty()?1:st.top()+1;
					//cout<<"t2 "<<t2<<endl;
					temp=arr[t1]*(i-t2);
					//cout<<"temp "<<temp<<endl;
					if(temp>ans)
						ans=temp;
					//cout<<"ans "<<ans<<endl;
				}
				st.push(i);
			}
		}
		long long int i=st.top()+1;
		while(!st.empty())
		{
			t1=st.top();
			st.pop();
			t2=st.empty()?1:st.top()+1;
			temp=arr[t1]*(i-t2);
			if(temp>ans)
				ans=temp;
		}
		cout<<ans<<endl;
	}
	return 0; 
}
