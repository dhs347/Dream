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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202;

int q[N], g[N];

struct Node {
	string o;
	int q, g;
	void read() {
		cin >> o >> q >> g;
		::q[o[0] - 'a'] = q;
		::g[o[0] - 'a'] = g;
	}
	bool operator < (const Node &c) const {
		return q < c.q;
	}
}nd[N];

int n, m, k;
ll ans;
vector<pair<unsigned char, unsigned char> > vec[N][N];
//vector<pii> vec[N][N][N];
char s[N][N];
bool vis[N];
ll pre[N], tmp[N], val[N][N];

void solve(int u, char ch) {
	fill_n(vis + 1, m, 0);
	fill_n(pre + 1, m, 0);
	rep(d, u, n + 1) {
		rep(i, 1, m + 1) {
			if(s[d][i] == ch) vis[i] = 1;
			tmp[i] = val[d][i] + tmp[i - 1];
			pre[i] += tmp[i];
		}
		int pos = m + 1, it = m;
		per(l, 1, m + 1) {
			if(vis[l]) pos = l;
			while(it >= l && pre[it] - pre[l - 1] >= q[ch - 'a']) --it;
			if(pos <= it) {
				vec[d][l].pb(mp(pos, it));
			}
		}
	}
	rep(i, 1, n + 1) rep(j, 1, m + 1) if(s[i][j] == ch) val[i][j] = g[ch - 'a'];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	cin >> k;
	rep(i, 1, k + 1) nd[i].read();
	sort(nd + 1, nd + 1 + k);
	rep(u, 1, n + 1) {
		rep(i, 0, N) rep(j, 0, N) vec[i][j].clear(), val[i][j] = 0;
		rep(i, 1, k + 1) solve(u, nd[i].o[0]);//, cout << endl;	
		int i = u;
		rep(j, i, n + 1) rep(k, 1, m + 1) {
			auto &vp = vec[j][k];
			sort(all(vp));
			int cnt = 0, st = 0, ed = -1;
			for(auto u : vp) {
				int l = u.fi, r = u.se;
				if(!st || ed < l) {
					cnt += ed - st + 1;
					st = l, ed = r;
				} else {
					ed = max(ed, r);
				}
			}
			if(st <= ed) cnt += ed - st + 1;
			ans += m - k + 1 - cnt;
		}
	}
	cout << ans << endl;
	//	db x = sizeof(vec);
	//	de(x / 1024. / 1024);
	return 0;
}
