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

const int N = 505050;

int n, m, pre[N];
pair<int, pii> e[N];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	ll ans = 0;
	rep(i, 1, m + 1) {
		cin >> e[i].se.fi >> e[i].se.se >> e[i].fi, ans += e[i].fi;
		e[i].fi = max(0, e[i].fi);
	}
	sort(e + 1, e + 1 + m);
	reverse(e + 1, e + 1 + m);
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, m + 1) {
		int u = find(e[i].se.fi), v = find(e[i].se.se);
		if(u != v) {
			ans -= e[i].fi;
			pre[u] = v;
		}
	}
	cout << ans << endl;
	return 0;
}
