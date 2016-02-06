#include <bits/stdc++.h>
#include<stdlib.h>
#include<cctype>

#define mod 1000000007
#define inf 1<<30
#define pb push_back
#define MAX 50009

using namespace std;
 
static struct IO {
	char tmp[1 << 10];
 
	// fast input routines
	char cur;
 
//#define nextChar() (cur = getc_unlocked(stdin))
//#define peekChar() (cur)
	inline char nextChar() { return cur = getc_unlocked(stdin); }
	inline char peekChar() { return cur; }
 
	inline operator bool() { return peekChar(); }
	inline static bool isBlank(char c) { return (c < '-' && c); }
	inline bool skipBlanks() { while (isBlank(nextChar())); return peekChar() != 0; }
 
	inline IO& operator >> (char & c) { c = nextChar(); return *this; }
 
	inline IO& operator >> (char * buf) {
		if (skipBlanks()) {
			if (peekChar()) {
				*(buf++) = peekChar();
				while (!isBlank(nextChar())) *(buf++) = peekChar();
			} *(buf++) = 0; } return *this; }
 
	inline IO& operator >> (string & s) {
		if (skipBlanks()) {	s.clear(); s += peekChar();
			while (!isBlank(nextChar())) s += peekChar(); }
		return *this; }
 
	inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this;	}
 
#define defineInFor(intType) \
	inline IO& operator >>(intType & n) { \
		if (skipBlanks()) { \
			int sign = +1; \
			if (peekChar() == '-') { \
				sign = -1; \
				n = nextChar() - '0'; \
			} else \
				n = peekChar() - '0'; \
			while (!isBlank(nextChar())) { \
				n += n + (n << 3) + peekChar() - 48; \
			} \
			n *= sign; \
		} \
		return *this; \
	}
 
defineInFor(int)
defineInFor(unsigned int)
defineInFor(long long)
 
	// fast output routines
 
//#define putChar(c) putc_unlocked((c), stdout)
	inline void putChar(char c) { putc_unlocked(c, stdout); }
	inline IO& operator << (char c) { putChar(c); return *this; }
	inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }
 
	inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }
 
	char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
	inline IO& operator << (double d) { return (*this) << toString(d); }
 
 
#define defineOutFor(intType) \
	inline char * toString(intType n) { \
		char * p = (tmp + 30); \
		if (n) { \
			bool isNeg = 0; \
			if (n < 0) isNeg = 1, n = -n; \
			while (n) \
				*--p = (n % 10) + '0', n /= 10; \
			if (isNeg) *--p = '-'; \
		} else *--p = '0'; \
		return p; \
	} \
	inline IO& operator << (intType n) { return (*this) << toString(n); }
 
defineOutFor(int)
defineOutFor(long long)
 
#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;

/*bool operator<(person a,person b) {
	return a.ht<b.ht;
}*/

typedef struct
{
	int nr[2];
	int p;
}node;

typedef pair<int,int> pii;

int si[20][MAX],lcp[MAX],suffix_arr[MAX];
node L[MAX];
bool cmp(node x,node y)
{
	if(x.nr[0]==y.nr[0])
		return x.nr[1]<y.nr[1];
	return x.nr[0]<y.nr[0];
}

int main()
{
	int t,n,k,x,y,answer,step,cnt;
	long long fans;
	char str[50009];
	//cin>>t;
	scanf("%d",&t);
	while(t--)
	{
		//cin>>s;
		scanf("%s",str);
		n=strlen(str);
		fans=n*(n+1)/2;
		//cout<<"fans "<<fans<<endl;
		for(int i=0;i<n;i++)
		{
			si[0][i]=str[i]-'a';
		}
		for(step=1,cnt=1;cnt<n;step++,cnt*=2)
		{
			for(int i=0;i<n;i++)
			{
				L[i].nr[0] = si[step-1][i];
				L[i].nr[1] = (i+cnt < n) ? si[step-1][i+cnt] : -1;
				L[i].p = i;
			}
			sort(L,L+n,cmp);
			for(int i=0;i<n;i++)
			{
				si[step][L[i].p]=( i>0 && L[i].nr[0]==L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1] )? si[step][L[i-1].p] : i;
			}
		}	
		for(int i=0;i<n;i++)
		{	
			suffix_arr[si[step-1][i]]=i;
		}	
		/*for(int i=0;i<n;i++)
			cout<<suffix_arr[i]<<" ";
		cout<<endl;*/
		lcp[0]=0;
		k=ceil(log(n)/log(2));
		for(int i=1;i<n;i++)
		{
			answer=0;
			x=suffix_arr[i];
			y=suffix_arr[i-1];
			for(int j=k;j>=0 && x<n && y<n;j--)
			{
				if(si[j][x]==si[j][y])
				{	
					answer+=(1<<j);
					x+=(1<<j);
					y+=(1<<j);
				}
			}
			lcp[i]=answer;
			fans-=lcp[i];
			// cout<<"fans "<<fans<<" i "<<i<<" answer "<<answer<<endl;
		}
		/*for(int i=0;i<n;i++)
			cout<<lcp[i]<<" ";
		cout<<endl;*/
		//cout<<fans<<endl;
		printf("%lld\n",fans);
	}
	return 0;
}
