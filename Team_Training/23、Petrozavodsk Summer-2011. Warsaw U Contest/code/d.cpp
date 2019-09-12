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

const int N = 202020;

int n, m, q, ans[N], dis[N], inf;
bool vis[N];
vector<pii> vec, qry;
vi g[N];

void add(int st, int ed) {
	priority_queue<pii> que;
	if(dis[ed] > dis[st] + 1) {
		dis[ed] = dis[st] + 1;
		que.push(mp(-dis[ed], ed));
	}
	while(!que.empty()) {
		auto u = que.top(); que.pop(); 
		for(auto v : g[u.se]) {
			if(dis[v] > dis[u.se] + 1) {
				dis[v] = dis[u.se] + 1;
				que.push(mp(-dis[v], v));
			}
		}
	}
	g[st].pb(ed);
}

int main() {
	freopen("evacuation.in", "r", stdin);
	freopen("evacuation.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n >> m >> q;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		vec.pb(mp(u, v));
	}
	rep(i, 1, q + 1) {
		string o; int x; cin >> o >> x;
		qry.pb(mp(o[0] == 'E', x));
		if(o[0] == 'U') vis[x] = 1;
	}
	memset(dis, 0x3f, sizeof(dis)); inf = dis[1]; dis[1] = 0;
	rep(i, 1, m + 1) if(!vis[i]) add(vec[i - 1].fi, vec[i - 1].se);
	per(i, 1, q + 1) {
		int x = qry[i - 1].se;
		if(qry[i - 1].fi == 0) {
			add(vec[x - 1].fi, vec[x - 1].se);
		} else {
			ans[i] = dis[x];
			if(ans[i] == inf) ans[i] = -1;
		}
	}
	rep(i, 1, q + 1) if(ans[i]) cout << ans[i] << endl;
	return 0;
}

