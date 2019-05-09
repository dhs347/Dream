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
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 4e5 + 7;
int k, b[N * 3], ma, n, m, pre[N], h[N], p, x, y, M;
vi a[N];
ll ans;
vi tmp;

void Add(int x) {
	for (; x <= ma; x += x & -x) b[x]++;
}

void Del(int x) {
	for (; x <= ma; x += x & -x) b[x]--;//if (b[x]) b[x] = 0;else break;
}

int qry(int x)
 {
	int res = 0;
	for (; x; x -= x & -x) res += b[x];
	return res;
}

void solve(int l, int r) {
	if (l == r) {
		sort(all(a[l]));
		p = 1;
		rep(i, 0, sz(a[l])) {
			while (p < sz(a[l]) && a[l][p] - a[l][i] <= k) p++;
			ans += p - i - 1;
		}
		return;
	}
	int mid = l + r >> 1;
	per(i, l, mid+1) pre[i] = i < mid ? min(pre[i+1], h[i]) : h[i];
	rep(i, mid+1, r+1) pre[i] = i > mid+1 ? min(pre[i-1], h[i]) : h[i];
	
	vector<pair<int, pii> > vl, vr;
	rep(i, l, mid+1) rep(j, 0, sz(a[i])) vl.pb(mp(i < mid ? min(pre[i+1], a[i][j]) : a[i][j], mp(i, a[i][j])));
	rep(i, mid+1, r+1) rep(j, 0, sz(a[i])) vr.pb(mp(i > mid+1 ? min(pre[i-1], a[i][j]) : a[i][j], mp(i, a[i][j])));
	sort(all(vl));
	sort(all(vr));
	p = sz(vr) - 1;
	per(i, 0, sz(vl)) {
		while (p >= 0 && vr[p].fi >= vl[i].fi) {
			int t = vr[p].se.se + vr[p].se.fi + M;
			tmp.pb(t); Add(t); 
			p--;
		}
		ans += qry(k + vl[i].se.fi + 2 * vl[i].fi - vl[i].se.se + M);
	}
	//rep(i, 0, sz(vl)) de(vl[i].fi);
	rep(i, 0, sz(tmp)) Del(tmp[i]); tmp.clear();
	p = sz(vl) - 1;
	per(i, 0, sz(vr)) {
		while (p >= 0 && vl[p].fi > vr[i].fi) {
			int t = vl[p].se.se - vl[p].se.fi + n + M;
			tmp.pb(t); Add(t);
			p--;
		}
		ans += qry(k - vr[i].se.fi + 2 * vr[i].fi - vr[i].se.se + n + M);
	}
	//dd(l), dd(mid), dd(r), de(ans);
	rep(i, 0, sz(tmp)) Del(tmp[i]); tmp.clear();
	solve(l, mid);
	solve(mid+1, r);
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	rep(i, 1, n+1) cin >> h[i], ma = max(ma, h[i]);
	M = ma;
	ma *= 2;
	ma += M + n + k;
	cin >> m;
	rep(i, 1, m+1) cin >> x >> y, a[x].pb(y);
	//sort(a+1, a+m+1);
	solve(1, n); 
	cout << ans << endl;
	return 0;
}


