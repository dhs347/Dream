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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N= 30;
int n, k, ans;
string t;
vi co[N], col[N], now;
int a[N];

int calc() {
	int time = k;
	now.clear();
	rep(i, 1, n+1) co[i] = col[i];
	int i = 1, ii = 1;
	while (1){
		if (time <= 0) break;
		rep(j, 0, a[i]) {
			int o = -1;
			if (time <= 0) break;
			int p = sz(now) - 1, q = sz(co[ii]) - 1;
			while (p >= 0 && q >= 0) {
				if (o != -1) break;
				if (now[p] != co[ii][q]) o = co[ii][q];
				q--; p--;
			}
			if (o == -1) now.pb(1), co[ii].pb(0);
			else now.pb(o), co[ii].pb(o ^ 1);
			time--;
		}
		i++; ii++;
		if (ii > n) ii = 1; 
	}
	int res = 0;
	rep(i, 0, sz(now)) if (now[i] == 1) res++;
	return res;
}

void dfs(int d, int s) {
	if (s <= 0) {
		ans = max(ans, calc());
		return;
	}
	a[d] = 1; dfs(d+1, s-1);
	a[d] = 2; dfs(d+1, s-2);
}

int main() {
	freopen("checkers.in", "r", stdin);
	freopen("checkers.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> t;
		rep(j, 0, sz(t)) col[i].pb(t[j] == 'W');
	}
	dfs(1, k);
	cout << ans << endl;
	return 0;
}
