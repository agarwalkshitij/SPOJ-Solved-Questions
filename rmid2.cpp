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
typedef pair<long long int,long long int> pll;

//int dist[500010],visit[500010],n,special[500010],div1[500010],spct;

double maxy(double a,double b)
{
	if(a>b)
		return a;
	else
		return b;
}

multiset<int> s1,s2;


template <class T>
void gint(T& n)
{
    n = 0;
    int sign=1;
    register char c=0;
    while(c<33)
        c=getchar_unlocked();
    if (c=='-')
    {
        sign=-1;
        c=getchar_unlocked();
    }
    while(c>='0'&&c<='9')
    {
        n=(n<<3)+(n<<1)+(c-'0');
        c=getchar_unlocked();
    }
    n *= sign;
}

template <class T>
void dint(T a) {
    char num[20];
    int i = 0;
    if(a < 0) {
        putchar_unlocked('-');
        a *= -1;
    }
    do {
        num[i++] = a%10 + 48;
        a /= 10;
    }  while (a != 0);
    i--;
    while (i >= 0)
        putchar_unlocked(num[i--]);
    putchar_unlocked('\n');
}

void median_ele()
{
	//cout<<*s1.rbegin()<<endl;
	//printf("%d\n",(*s1.rbegin()));
	dint(*s1.rbegin());
	s1.erase(s1.find(*s1.rbegin()));
	if(s1.size()<s2.size())
	{
		s1.insert(*s2.begin());
		s2.erase(s2.begin());
	}
}

void add_ele(int x)
{
	if(s1.size()==s2.size())
	{
		s2.insert(x);
		s1.insert(*s2.begin());
		s2.erase(s2.begin());
	}
	else if(s1.size()>s2.size())
	{
		s1.insert(x);
		s2.insert(*s1.rbegin());
		s1.erase(s1.find(*s1.rbegin()));
	}
}

int main()
{
	int t,x;
	gint(t);
	while(t--)
	{
		while(!s1.empty())
			s1.erase(s1.begin());
		while(!s2.empty())
			s2.erase(s2.begin());
		while(1)
		{
			gint(x);
			if(x==0)
				break;
			else if(x==-1)
				median_ele();
			else if(x>0)
				add_ele(x);
		}
	}
	return 0;
}
