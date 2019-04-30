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
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;
int n, w[N], L, d[N], u, fa[N], f[N], vis[N], ans;
ll s[N], S;
priority_queue<pair<ll, int> > q;
vi g[N];

int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

void dfs(int u) {
	for (auto v : g[u]) {
		d[v] = d[u] + 1;
		s[v] = s[u] + w[v];
		dfs(v);
	}
	q.push(mp(s[u], u));
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> L >> S;
	rep(i, 1, n+1) {
		cin >> w[i];
		if (w[i] > S) {
			cout << - 1;
			return 0;
		}
	}
	s[1] = w[1];
	rep(i, 2, n+1) {
		cin >> u;
		g[u].pb(i);
		fa[i] = u;
	}
	dfs(1);
	rep(i, 1, n+1) f[i] = i;
	while (!q.empty()) {
		int x = q.top().se, y = x;
		q.pop();
		if (vis[x]) continue;
		ans++;
		while (x && d[y] - d[x] + 1 <= L && s[y] - s[x] + w[x] <= S) {
			vis[x] = 1;
			f[x] = get(fa[x]);
			x = f[x];
		}
	}
	cout << ans;
	return 0;
}


