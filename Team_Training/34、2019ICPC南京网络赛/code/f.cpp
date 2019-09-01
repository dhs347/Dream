#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 303030;

int n, k, a[N], deg[N], ans[N];
vi g[N];

void add(int u, int v) {
	++deg[v];
	g[u].pb(v);
}

void solve() {
	cin >> n >> k;
	rep(i, 1, n + 1) cin >> a[i], deg[i] = 0, g[i].clear();
	set<int> st;
	int l = 1, r = min(k + 1, n);
	rep(i, l, r + 1) st.insert(a[i]);
	rep(i, 1, n + 1) {
		int L = max(1, i - k), R = min(n, i + k);
		if(l != L) st.erase(a[l++]);
		if(r != R) st.insert(a[++r]);
		auto p = st.lower_bound(a[i]); 
		if(p != st.begin()) {
			--p; add(*p, a[i]);
		}
	}
	vi que;
	rep(i, 1, n + 1) if(!deg[i]) {
		ans[i] = 1;
		que.pb(i);
	}
	rep(i, 0, sz(que)) {
		int u = que[i];
		for(auto v : g[u]) {
			--deg[v]; ans[v] = ans[u] + 1;
			if(!deg[v]) que.pb(v);
		}
	}
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; while(T--) solve();
	return 0;
}
