#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
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

const int N = 101010;

int n, m, p[N], pos[N], a[N], ans[N];
vector<pii> vec[N];

struct FW {
	#define lb(x) ((x)&-(x))
	static const int N = ::N;
	int a[N];
	void upd(int p) {
		for(; p <= n; p += lb(p)) a[p]++;
	}
	int _qry(int p) {
		int r = 0;
		for(; p; p ^= lb(p)) r += a[p];
		return r;
	}
	int qry(int l, int r) {
		return _qry(r) - _qry(l - 1);
	}
}fw;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i], pos[a[i]] = i;
	rep(i, 1, n + 1) for(int j = i + i; j <= n; j += i) {
		int l = pos[i], r = pos[j];
		if(l > r) swap(l, r);
		vec[r].pb(mp(1, l));
	}
	rep(i, 1, m + 1) {
		int l, r; cin >> l >> r;
		a[i] = l; vec[r].pb(mp(2, i));
	}
	rep(i, 1, n + 1) {
		for(auto u : vec[i]) {
			if(u.fi == 1) {
				fw.upd(u.se);
			} else {
				int ind = u.se;
				ans[ind] = fw.qry(a[u.se], i);
			}
		}
	}
	rep(i, 1, m + 1) cout << ans[i] << " \n"[1];
	return 0;
}
