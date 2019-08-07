#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 50505, inf = N;

int tim, res, vis[N], vec[N], f[N], ind[N], pre[N];
int n, p[N], k[N], ans[N];

void gao(int pos) {
	++tim;
	rep(i, 1, pos + 1) vec[i] = k[i];
	sort(vec + 1, vec + 1 + pos);
	rep(i, 0, pos + 2) f[i] = inf;
	rep(i, 1, pos + 1) {
		int u = vec[i];
		int po = lower_bound(f + 1, f + 1 + pos, p[u]) - f;
		pre[u] = ind[po - 1];
		f[po] = p[u];
		ind[po] = u;
	}
	int po = lower_bound(f + 1, f + 1 + pos, inf) - f;
	int now = ind[po - 1];
	while(now) {
		vis[now] = tim;
		now = pre[now];
	}
	res = po - 1;
}

void solve() {
	srand(time(0));
	cin >> n;
	n = 5e4;
	rep(i, 1, n + 1) cin >> p[i], p[i] = i;
	rep(i, 1, n + 1) cin >> k[i], k[i] = i;
	random_shuffle(p + 1, p + 1 + n);
	random_shuffle(k + 1, k + 1 + n);
	gao(n);
	per(i, 1, n + 1) {
		if(vis[k[i]] == tim) gao(i);
		ans[i] = res;
	}
}

int main() {
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
