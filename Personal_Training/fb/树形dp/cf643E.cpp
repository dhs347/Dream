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
#define all(a) (a).begin(), (a).end()
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

const int N = 5e5 + 7, M = 41, tim = 40;

int op, u, n, q, v, cnt,fa[N];
db f[N][M], tmp[N][M], ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(8);
	cin >> q;n = 1;
	rep(cas, 0, q) {
		cin >> op >> u;
		if (op == 1) {
			fa[++n] = u; u = n;
			tmp[u][0] = 1; rep(j, 1, tim+1) tmp[u][j] = 0;
			cnt = 0; v = u; u = fa[u];
			vi tmp2;
			while (cnt < tim && u) {
				cnt++;
				rep(j, 1, tim+1) tmp[u][j] = 1 - (1 - f[u][j]) / (1 - 0.5 * f[v][j-1]) * (1 - 0.5 * tmp[v][j-1]); 
				tmp2.pb(u);
				v = u; u = fa[u];
			}
			f[n][0] = 1;
			for (auto v : tmp2) rep(j, 1, tim+1) f[v][j] = tmp[v][j];
		}else {
			ans = 0;
			rep(i, 1, tim+1) ans += f[u][i];
			cout << ans << endl;
		}
	}
	return 0;
}


