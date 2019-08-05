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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010, M = 30;

int n, a[N], b[N], ne[N * M][2], L, cnt[N * M], rt, num[N * M];
vi vec[N * M];
bool vis[N];
priority_queue<pair<int, pii> > que;

int newnode() {
	fill_n(ne[L], 2, 0);
	cnt[L] = num[L] = 0;
	vec[L].clear();
	return L++;
}
void add(int x) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		if(!ne[p][c]) ne[p][c] = newnode();
		p = ne[p][c];
		++cnt[p];
	}
	num[p] = x;
}
void go(int x, int i) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		if(ne[p][c] && cnt[ne[p][c]]) p = ne[p][c];
		else p = ne[p][c ^ 1];
	}
	vec[p].pb(i);
	que.push(mp(-(x ^ num[p]), mp(p, i)));
}
void del(int x) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		p = ne[p][c];
		--cnt[p];
	}
	if(cnt[p]) return ;
	for(auto u : vec[p]) if(!vis[u]) go(b[u], u);
	vec[p].clear();
}
void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n + 1) cin >> b[i], vis[i] = 0;
	while(!que.empty()) que.pop();
	L = 0; rt = newnode();
	rep(i, 1, n + 1) add(a[i]);
	rep(i, 1, n + 1) go(b[i], i);
	rep(i, 1, n + 1) {
		while(1) {
			auto u = que.top(); que.pop();
			if(!cnt[u.se.fi]) continue;
			vis[u.se.se] = 1;
			cout << -u.fi << " \n"[i == n];
			del(num[u.se.fi]);
			break;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
