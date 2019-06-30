#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
int cnt[1 << 6];
vi sta;
int ans;

void print(int v) {
	rep(i, 0, n) cout << (v >> i & 1); 
	cout << endl;
}

void dfs(int u) {
	sta.pb(u);
	if(sz(sta) == 2) {
		for(auto v : sta) cout << v << ", "; cout << endl;
		/*
		for(auto v : sta) print(v);
		cout << endl;
		*/
	}
	ans = max(ans, sz(sta));
	rep(i, 0, n) ++cnt[u ^ pw(i)];
	rep(i, 0, n) {
		int v = (u ^ pw(i));
		if(cnt[v] == 1) {
			dfs(v);
		}
	}
	rep(i, 0, n) --cnt[u ^ pw(i)];
	sta.pop_back();
}

void solve() {
	++cnt[0];
	dfs(0);
	de(ans);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	n = 1;
	solve();
	return 0;
}
