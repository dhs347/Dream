#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 7;
pii r[N];
int T, n, q, a[300][300], u, v, w, ans[N];
struct node {
	int u, v, w, i;
	node(int u = 0, int v = 0, int w = 0, int i = 0):u(u), v(v), w(w), i(i) {}
	bool operator < (const node &b) {
		return w < b.w;
	}
};

node Q[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> q;
		rep(i, 1, n+1) cin >> r[i].fi, r[i].se = i;
		rep(i, 1, n+1) rep(j, 1, n+1) cin >> a[i][j];
		sort(r+1, r+n+1);
		rep(i, 1, q+1) {
			cin >> u >> v >> w;
			Q[i] = node(u, v, w, i);
		}
		sort(Q+1, Q+q+1);
		int p = 0;
		rep(t, 1, q+1) {
			while (p + 1 <= n && r[p+1].fi <= Q[t].w) {
				int k = r[++p].se;
				rep(i, 1, n+1)
					rep(j, 1, n+1) if (i != j && i != k && j != k){
						a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
					}
			}
			ans[Q[t].i] = a[Q[t].u][Q[t].v];
		}
		cout << "Case #" << cas + 1 << ":" << endl;
		rep(i, 1, q+1) cout << ans[i] << endl; 
	}
	return 0;
}
