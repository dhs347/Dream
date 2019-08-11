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
typedef long long ll;
typedef unsigned int uint;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 401;

int n, q;
int g[N][N], out[N], deg[N];
uint A, B;
uint a[N], b[N];
bitset<N> to[N];
int que[N], top;

void solve() {
	rep(i, 1, n + 1) to[i].reset(), deg[i] = out[i];
	top = 0;
	rep(i, 1, n + 1) if(!deg[i]) que[++top] = i;
	rep(i, 1, top + 1) {
		int u = que[i];
		to[u][u] = 1;
		rep(v, 1, n + 1) if(g[v][u]) {
			to[v] |= to[u];
			--deg[v];
			if(deg[v] == 0) que[++top] = v;
		}
	}
	uint ans = 0;
	rep(i, 1, n + 1) rep(j, 1, n + 1) if(i != j && to[i][j]) ans += a[i - 1] * b[j - 1];//, dd(i), de(j);
	cout << ans << endl;
}

int main() {
	freopen("reachability.in", "r", stdin);
	freopen("reachability.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q >> A >> B;
	a[0] = b[0] = 1;
	rep(i, 1, N) a[i] = a[i - 1] * A, b[i] = b[i - 1] * B;
	while(q--) {
		string a, b; int u, k;
		cin >> a >> b >> u >> k;
		rep(i, 1, k + 1) {
			int v; cin >> v;
			if(a[0] == '+') {
				if(b[0] == 'o') {
					g[u][v] = 1;
					++out[u];
				} else {
					g[v][u] = 1;
					++out[v];
				}
			} else {
				if(b[0] == 'o') {
					g[u][v] = 0;
					--out[u];
				} else {
					g[v][u] = 0;
					--out[v];
				}
			}
		}
		solve();
	}
	return 0;
}
