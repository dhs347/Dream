#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 4e5 + 3, P = 1e9 + 7;

int n, m, pre[N], pw[N], cn[N], cm[N], res[N], fa[N];
vector<pair<pii, int> > e;

int find(int x, int pre[]) {
	return x == pre[x] ? x : pre[x] = find(pre[x], pre);
}
void join(int x, int y) {
	x = find(x, pre), y = find(y, pre);
//	if(x < y) swap(x, y);
	pre[x] = y;
}
void join(int x, int y, int &cn) {
	x = find(x, fa), y = find(y, fa);
	if(x == y) return ;
	--cn; fa[x] = y;
}

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) pre[i] = i, res[i] = 1, fa[i] = i;
	pw[0] = 1; rep(i, 1, m + 1) pw[i] = pw[i - 1] * 2ll % P;

	rep(i, 1, m + 1) {
		int u, v, w; cin >> u >> v >> w;
		join(u, v);
		e.pb(mp(mp(u, v), w));
	}
	rep(i, 1, n + 1) cn[find(i, pre)]++;
	for(auto t : e) {
		int u = t.fi.fi, v = t.fi.se, w = t.se;
		int k = find(u, pre);
		if(w % 2 == 1 || u == v) res[k] = mul(res[k], w), join(u, v, cn[k]);
		else res[k] = mul(res[k], w >> 1), cm[k]++;
	}
	int ans = 0;
	rep(i, 1, n + 1) if(i == find(i, pre)) {
	//	dd(i), dd(cn[i]), de(cm[i]);
		res[i] = mul(res[i], add(cn[i] * 1ll * (cn[i] - 1) / 2 % P, 1));
		res[i] = mul(res[i], pw[cm[i] - cn[i] + 1]);
		int t = res[i] - 1;
		if(t < 0) t += P;
		ans = add(ans, t);
	}
	cout << add(ans, 1) << endl;
	return 0;
}
