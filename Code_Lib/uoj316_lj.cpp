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
const int _p=998244353;

#define mem(a,x) memset(a,x,sizeof(a))

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

inline int mul(int x,int y) {
    return (ll)x*y%_p;
}

inline int add(int x,int y) {
    x+=y;
    if (x>=_p) x-=_p;
    return x;
}

inline int sub(int x,int y) {
    x-=y;
    if (x<0) x+=_p;
    return x;
}

inline ll Pow(ll x,ll k) {
    ll ret=1;
    for (;k;k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
    return ret;
}

inline int inv(int x) { return Pow(x,_p-2); }

int linear_recurrence(ll n, int m, vi a, vi c,int P=_p) {
	if (n<m) return (a[n]+P)%P;
	vector<ll> v(m, 0), u(m<<1, 0);
	v[0] = 1;
	for(ll x = 0, W = n ? 1ll<<(63 - __builtin_clzll(n)) : 0; W; W >>= 1, x <<= 1) {
		fill(all(u), 0);
		int b = !!(n & W); if(b) x++;
		if(x < m) u[x] = 1;
		else {
			rep(i, 0, m) rep(j, 0, m) (u[i + b + j] += v[i] * v[j]) %= P;
			per(i, m, 2*m) rep(j, 0, m) (u[i - m + j] += c[j] * u[i]) %= P;
		}
		copy(u.begin(), u.begin() + m, v.begin());
	}
	ll ans = 0;
	rep(i, 0, m) (ans += v[i] * a[i]) %= P;
	return (ans+P)%P;
}

const int N=2005;
int n,k,x,y,q,p,P[N],Q[N],f[N],h[N][N],g[N][N];

int solve(int n,int k) {
    if (!k) return Pow(p,n);
    mem(f,0),mem(g,0),mem(h,0);
    g[k][0]=h[k][0]=f[0]=1;
    g[k][1]=h[k][1]=mul(Q[k],p);
    per(i,1,k) {
        h[i][0]=g[i][0]=1;
        rep(j,1,k/i+1) rep(kk,0,j) h[i][j]=add(h[i][j],mul(mul(h[i][kk],g[i+1][j-1-kk]),mul(Q[i],p)));
        rep(j,1,k/i+1) rep(kk,0,j+1) g[i][j]=add(g[i][j],mul(h[i][kk],g[i+1][j-kk]));
    }
    rep(i,1,k+1) rep(kk,0,min(i,k+1)) f[i]=add(f[i],mul(f[i-1-kk],mul(g[1][kk],p)));
    if (n<k) return mul(f[n+1],inv(p));
    vi a,c;
    rep(i,0,k+1) a.pb(f[i]);
    rep(i,0,k+1) c.pb(mul(g[1][i],p));
    reverse(all(c));
    return mul(linear_recurrence(n+1,k+1,a,c),inv(p));
}

int main() {
	//file_put();
	
    scanf("%d%d%d%d",&n,&k,&x,&y),q=mul(x,inv(y)),p=sub(1,q);
    P[0]=Q[0]=1; rep(i,1,k+1) P[i]=mul(P[i-1],p),Q[i]=mul(Q[i-1],q);
    printf("%d\n",sub(solve(n,k),solve(n,k-1)));
    
	return 0;
}


