#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 3030, P = 1e9 + 7;

int n, k, a[N], ans, res;
int val[N], lim[N], f[N], suf[N], sz[N], C[N][N], jc[N], in[N], St[N], Ed[N];
int vec[N], cntv;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

void dp(int u) {
	sz[u] = 1;
	f[u] = 1;
	int st = k * u + 1, ed = min(k * u + k, n - 1);
	rep(v, st, ed + 1) {
		dp(v);
		sz[u] += sz[v];
		f[u] = mul(f[u], f[v]);
		f[u] = mul(f[u], in[sz[v]]);
	}
	f[u] = mul(f[u], jc[sz[u] - 1]);
}
void dfs(int u) {
	if(!val[u]) {
		vec[++cntv] = u;
		return ;
	}
	int st = St[u], ed = Ed[u];
	rep(v, st, ed + 1) dfs(v);
}
bool cmp(int u, int v) {
	return lim[u] > lim[v];
}
int o;
int calc() {
	res = 1;
	if(o) { cntv = 0, dfs(0); }
	sort(vec + 1, vec + 1 + cntv, cmp);
	rep(i, 1, n + 1) suf[i] = 1;
	rep(i, 0, n) suf[val[i]] = 0;
	suf[n + 1] = 0;
	per(i, 1, n + 1) suf[i] += suf[i + 1];
	int tot = 0;
	rep(i, 1, cntv + 1) {
		int u = vec[i];
		int w = suf[lim[u] + 1];
		if(w - tot < sz[u]) return 0;
		int t = mul(C[w - tot][sz[u]], f[u]);
		tot += sz[u];
		res = mul(res, t);
	}
	return res;
}

void solve() {
	cin >> n >> k;
	rep(i, 0, n) {
		St[i] = i * k + 1, Ed[i] = min(i * k + k, n - 1);
	}
	rep(i, 0, n) cin >> a[i];
	//rep(i, 0, n) a[i] = i + 1;
	ans = 0; dp(0);
	rep(i, 0, n) val[i] = 0, lim[i] = 0;
	// i no certain
	rep(i, 0, n) {
		if(lim[i] < a[i] - 1) {
			int t = lim[i];
			o = 1;
			ans = add(ans, calc());
			o = 0;
			lim[i] = a[i] - 1;
			ans = sub(ans, calc());

			lim[i] = t;
		}
		val[i] = a[i]; 
		int st = k * i + 1, ed = min(k * i + k, n - 1);
		rep(j, st, ed + 1) lim[j] = val[i];
	}
	cout << add(ans, 1) << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, N) C[i][0] = C[i][i] = 1;
	rep(i, 0, N) rep(j, 1, i) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
	jc[0] = 1;
	rep(i, 1, N) jc[i] = mul(jc[i - 1], i);
	in[N - 1] = kpow(jc[N - 1], P - 2);
	per(i, 0, N - 1) in[i] = mul(in[i + 1], i + 1);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
	return 0;
}
