#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1e6+5;
char aa[N],bb[N],cc[N],gg[N]; int p,a,b,c,g;

int mul(int x,int y) {
	return (ll)x*y%p;
}

int put(char s[],int p) {
	int ret=0,n=strlen(s);
//	de(n);
	rep(i,0,n) {
		assert(s[i]>='0' && s[i]<='9');
		ret=((ll)ret*10+s[i]-'0')%p;
	}
	assert(ret>=0);
	return ret; 
}

int Pow(int x,int k) {
//	assert(k>=0);
	int ret=1;
	for (; k; k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

ll kpow(ll a, ll b, ll P) {
//	assert(b>=0);
    ll r = 1;
    for (; b; b>>=1, a = a * a % P) if (b & 1) r = r * a % P;
    return r; 
}

void ex_gcd(int a, int b, int &x, int &y){
	b ? (ex_gcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}

inline int Inv(int a, int P) {
	int x, y; ex_gcd(a, P, x, y);
	return x < 0 ? x + P : x;
}


struct BSGS{
    static const int M = 65535, A = 2939;
	ll rx[M + 10];
	int ls[M + 10], LS;
	int ry[M + 10];
	inline void ins(int x, int i) {
		int now = x & M;
		while (ls[now] == LS && rx[now] != x)
			now = now + A & M;
		ls[now] = LS;
		rx[now] = x;
		ry[now] = i;
		return;
	}
	inline int find(int x) {
		int now = x & M;
		while (ls[now] == LS) {
			if (rx[now] == x)
				return ry[now];
			now = now + A & M;
		}
		return -1;
	}
	ll bsgs(ll a, ll b, ll p) {
		LS++;
		register int i;
		a %= p;
		ll m = ceil(sqrt(p));
		ll tmp, ans = b % p;
		for (i = 0; i <= m; ++i) {
			ins(ans, i);
			ans = ans * a % p;
		}
		assert(m>=0);
		tmp = kpow(a, m, p);
		ans = 1;
		for (i = 1; i <= m; ++i) {
			ans = ans * tmp % p;
			int j = find(ans);
			if (j != -1)
				return i * m - j;
		}
		return -1;
	}
};

BSGS BB;

int main() {
//	file_put();
	
	scanf("%s",aa);
	scanf("%s",bb);
	scanf("%s",cc);
	scanf("%s",gg);
	scanf("%d",&p);
	
	a=put(aa,p-1);
	b=put(bb,p-1);
	c=put(cc,p);
	g=put(gg,p);
//	assert(a>=0);
//	if (a<0) return 0;
	a=Pow(g,a),b=Pow(g,b);
	if (b==0) {
		if (c==0) return 0*printf("1\n");
		return 0*printf("no solution\n");
	}
	b=mul(Pow(b,p-2),c);
	int n=BB.bsgs(a,b,p);
	if (n==-1) return 0*printf("no solution\n");
	assert(n>0);
	printf("%d\n",n);
	
	return 0;
}

