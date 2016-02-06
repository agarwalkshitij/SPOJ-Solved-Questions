#include <bits/stdc++.h>

#define mod 1000000007
#define inf 1<<30
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


typedef pair<int,int> pii;

int n;

typedef struct
{
	int a,b,c,d;
}node;

bool cmp(node x,node y)
{
	return x.a<y.a;
}

int getsum(int tree[],int ind)
{
	ind=ind+1;
	int sum=inf;
	while(ind>0)
	{
		//sum+=tree[ind];
		if(tree[ind]<sum)
			sum=tree[ind];
		ind=ind-(ind & (-ind));
	}
	return sum;
}

void update(int tree[],int ind,int val)
{
	ind=ind+1;
	while(ind<=n)
	{
		//tree[ind]+=val;
		if(tree[ind]>val)
			tree[ind]=val;
		ind=ind+(ind & (-ind));
	}
}

int main()
{
	int t,ans,t1,t2;
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		node arr[n+1];
		int tree[n+1];
		for(int i=0;i<=n;i++)
			tree[i]=inf;
		for(int i=0;i<n;i++)
		{
			cin>>arr[i].a>>arr[i].b>>arr[i].c;
			arr[i].d=i;
		}		
		sort(arr,arr+n,cmp);	
		/*for(int i=0;i<n;i++)
			cout<<arr[i].a<<" "<<arr[i].b<<" "<<arr[i].c<<endl;*/
		update(tree,arr[0].b,arr[0].c);
		ans=1;
		for(int i=1;i<n;i++)
		{
			//cout<<"i "<<i<<endl;
			t1=getsum(tree,arr[i].b-1);
			//t2=getsum(tree2,arr[i].c);
			//cout<<"t1 "<<t1<<" t2 "<<t2<<endl;
			if(t1>arr[i].c)
				ans++;
			update(tree,arr[i].b,arr[i].c);
			//update(tree2,arr[i].c,1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
