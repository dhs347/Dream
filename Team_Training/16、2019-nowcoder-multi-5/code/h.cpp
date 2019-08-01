#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, m, in[N], cnt[11];
bool vis[11];
vi g[N], V;

bool gao(char ch, string s) {
	int o = ch - 'a';
	int c = 0;
	rep(i, 0, sz(s)) c += (s[i] == ch);
	if(vis[o]) {
		return c == cnt[o];
	} else {
		cnt[o] = c;
		vis[o] = 1;
	}
	return 1;
}

void add(int u, int v) {
	++in[v];
	g[u].pb(v);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	int M = m * (m - 1) / 2;
	rep(i, 1, M + 1) {
		string s, t; int len;
		cin >> s >> len;
		if(len) cin >> t;
		if(!gao(s[0], t) || !gao(s[1], t)) {
			cout << -1 << endl;
			return 0;
		}
		int c[2] = {0}, pre = 0;
		for(auto k : t) {
			++c[k == s[1]];
			int u = c[k == s[1]] * 10 + k - 'a';
			if(pre) add(pre, u);
			pre = u;
			V.pb(u);
		}
	}
	int len = 0;
	rep(i, 0, m) len += cnt[i];
	if(len != n) {
		cout << -1 << endl;
		return 0;
	}
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	vi que;
	for(auto u : V) if(!in[u]) que.pb(u);
	vi ans;
	rep(i, 0, sz(que)) {
		int u = que[i];
		ans.pb(u % 10);
		for(auto v : g[u]) {
			--in[v];
			if(in[v] == 0) que.pb(v);
		}
	}
	if(sz(ans) != n) {
		cout << -1 << endl;
	} else {
		for(auto u : ans) cout << (char)(u + 'a'); cout << endl;
	}
	return 0;
}
