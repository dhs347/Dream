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
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

int solve(int pp) {
	x = 0; len = sz(h[pp]);
	S = pw(len) - 1;
	rep(i, 0, sz(h[pp])) {
		u = h[pp].fi.fi; v = h[pp].fi.se; o = h[pp].se;
		if (o == 0) x |= pw(i); 
	}
	dfs(x, )
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(i, 1, N) {
		x = 0; y = 0; t = i;
		while (t % 2 == 0) { t /= 2; x++;}
		while (t % 3 == 0) { t /= 3; y++;}
		p[i] = t; w[i] = mp(x, y);
	}
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, 20) {
			rep(j, 1, 20)
				rep(k, 1, m+1) if (j * k <= i) {
					int t = 0;
					rep(l, 0, k+1) t |= pw(i - j * l);
					way[i].pb(t); 
				}
		}
		rep(i, 1, n+1) {
			cin >> a[i];
			tmp.pb(p[i]);
			h[p[i]].pb(mp(w[i], a[i]));
		}
		sort(all(tmp));
		tmp.erase(unique(all(tmp)), tmp.end());
		now = 0;
		rep(i, 0, sz(tmp)) now ^= solve(tmp[i]);
	}
	return 0;
}


