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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

struct DLX{
#define FOR(i, ne, t) for(int i = ne[t]; i != t; i = ne[i])
	static const int N = 1e4 + 8;
	int n, m, tim, sz, ansd;
	int row[N], col[N], s[N], ans[N];
	int l[N], r[N], u[N], d[N];
	void init(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 0, m+1) l[i] = i-1, r[i] = i+1, u[i] = d[i] = i;
		l[0] = m, r[m] = 0, tim = m+1;
		rep(i, 0, m+1) s[i] = 0; 
	}
	void add(int R, vi tmp){
		int first = tim;
		rep(i, 0, sz(tmp)) if (tmp[i]) {
			int c = i+1;
			l[tim] = tim-1, r[tim] = tim+1, u[tim] = u[c], d[tim] = c;
			u[c] = tim; d[u[tim]] = tim;
			row[tim] = R, col[tim] = c;
			tim++, s[c]++;
		}
		l[first] = tim-1, r[tim-1] = first;
	}
	inline void remove(int c) {
		l[r[c]] = l[c];
		r[l[c]] = r[c];
		FOR(i, d, c)
			FOR(j, r, i) u[d[j]] = u[j], d[u[j]] = d[j], --s[col[j]];
	}
	inline void restore(int c) {
		FOR(i, u, c)
			FOR(j, l, i) u[d[j]] = j, d[u[j]] = j, ++s[col[j]];
		 l[r[c]] = c;
		 r[l[c]] = c;
	}
	bool dance(int dep) {
		if (!r[0]) return ansd = dep, 1;
		int c = r[0];
		FOR(i, r, 0) if (s[c] > s[i]) c = i;
		remove(c);
		FOR(i, d, c) {
			ans[dep] = row[i];
			FOR(j, r, i) remove(col[j]);
			if (dance(dep+1)) return 1;
			FOR(j, l, i) restore(col[j]);
		}
		restore(c);
		return 0;
	}
	void work() {
		cin >> n >> m;
		init(n, m);
		rep(i, 1, n+1) {
			vi tmp; int t;
			rep(j, 1, m+1) cin >> t, tmp.pb(t);
			add(i, tmp);
		}
	    bool flag = dance(1);
	    if (flag) rep(i, 1, ansd) cout << ans[i] << " \n"[i == ansd - 1];
		else cout << "No Solution!" << endl; 
	}
} T;

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	T.work();
	return 0;
}


