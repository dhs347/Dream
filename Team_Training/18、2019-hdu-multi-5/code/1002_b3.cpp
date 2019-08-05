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

int n, a[N], b[N], ne[N * M][2], L, cnt[N * M], rt, num[N * M], to[N], ind[N * M], B[N], cc[N], m;
vi vec[N];
int vis[N];
priority_queue<pair<int, int> > que;

int newnode() {
	fill_n(ne[L], 2, 0);
	cnt[L] = num[L] = 0;
	return L++;
}
void add(int x, int i) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		if(!ne[p][c]) ne[p][c] = newnode();
		p = ne[p][c];
		++cnt[p];
	}
	num[p] = x;
	ind[p] = i;
}
void go(int x, int i) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		if(ne[p][c] && cnt[ne[p][c]]) p = ne[p][c];
		else p = ne[p][c ^ 1];
	}
	vec[ind[p]].pb(i);
	to[i] = p;
	que.push(mp(-(x ^ num[p]), i));
}
void del(int x) {
	int p = rt;
	per(i, 0, 30) {
		int c = (x >> i & 1);
		p = ne[p][c];
		--cnt[p];
	}
	if(cnt[p]) return ;
	for(auto u : vec[ind[p]]) if(vis[u]) go(b[u], u);
	vec[ind[p]].clear();
}
void solve() {
	cin >> n;
	rep(i, 1, n + 1) a[i] = rand(), vec[i].clear();
	rep(i, 1, n + 1) b[i] = rand();
	sort(b + 1, b + 1 + n);
	m = 0;
	rep(i, 1, n + 1) {
		if(i == 1 || b[i] != b[i - 1]) {
			b[++m] = b[i];
			cc[m] = 1;
		} else {
			++cc[m];
		}
	}
	rep(i, 1, m + 1) vis[i] = cc[i];

	de(m);
	while(!que.empty()) que.pop();
	L = 0; rt = newnode();
	rep(i, 1, n + 1) add(a[i], i);
	rep(i, 1, m + 1) go(b[i], i);
	rep(i, 1, n + 1) {
		while(1) {
			auto u = que.top(); 
			if(-u.fi != (num[to[u.se]] ^ b[u.se]) || !vis[u.se]) {
				que.pop();
				continue;
			}
			--vis[u.se];
			if(!vis[u.se]) que.pop();
			del(num[to[u.se]]);
			break;
		}
	}
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
