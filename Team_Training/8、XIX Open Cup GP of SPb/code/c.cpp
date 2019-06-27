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

const int N = (1 << 18) + 7;
bitset<N> a[20];
ll n, k, m, w[N], msk[N], vis[N], x, dis[50][50], S, cnt[N], ans, dp[N];
vector<pair<int, pii> > V;
int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	rep(i, 0, k) {
		cin >> w[i] >> m;
		rep(j, 0, m) {
			cin >> x; a[i][x] = 1;
			msk[x] |= pw(i);
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	rep(i, 0, k)
		rep(j, i, k) if ((a[i] & a[j]).count()) {
			if (i == j) dis[i][i] = 0;
			else {
				dis[i][j] = w[j];
				dis[j][i] = w[i];
			}
		}
	rep(l, 0, k)
		rep(i, 0, k)
			rep(j, 0, k) 
				dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
	rep(i, 0, k) rep(j, 0, k) dis[i][j] += w[i];
	S = pw(k) - 1;
	rep(i, 1, n+1) cnt[msk[i]]++; 
	rep(j, 0, S+1) dp[j] = cnt[j];
	rep(i, 0, k) rep(j, 1, S+1) if (j & pw(i)) dp[j] += dp[j ^ pw(i)];
	rep(i, 0, k) rep(j, 0, k) V.pb(mp(dis[i][j], mp(i, j)));
	sort(all(V));
	rep(i, 0, sz(V)) {
		int u = V[i].se.fi, v = V[i].se.se;
		rep(j, 1, S+1) if (j & pw(u)) {
			if (vis[j] & pw(v)) continue;
			ans += (dp[S ^ vis[j]] - dp[S ^ vis[j] ^ pw(v)]) * V[i].fi * cnt[j];
			vis[j] |= pw(v);
		}
	}
	rep(i, 1, S+1) {
		ll t = pw(30);
		rep(j, 0, k) if (pw(j) & i) t = min(t, dis[j][j]);
		ans -= t * cnt[i];
	}
	cout << ans / 2 << endl;
	return 0;
}


