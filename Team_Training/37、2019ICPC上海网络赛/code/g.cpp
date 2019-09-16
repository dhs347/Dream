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
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, ans[N], pre[26][N];
string s, t[N];
vi vec[N];
ull ha[N], ini[26];

inline ull gao(int a[]) {
	ull res = 0;
	rep(i, 0, 28) res = res * 131 + a[i];
	return res;
}
inline ull calc(int l, int r) {
	ull res = ha[r + 1] - ha[l] + s[l] * (ull)(131) + s[r];
	return res;
}
inline ull calc(int i) {
	int a[28] = {0};
	rep(j, 0, sz(t[i])) a[t[i][j] - 'a']++;
	a[26] = t[i][0];
	a[27] = t[i][sz(t[i]) - 1];
	return gao(a);
}
ull ve[N]; int cnt;
void solve(int len) {
	if(!sz(vec[len])) return ;
	cnt = 0;
	rep(i, len - 1, sz(s)) ve[++cnt] = calc(i - len + 1, i);
	sort(ve + 1, ve + 1 + cnt);
	for(register auto u : vec[len]) {
		register auto t = calc(u);
		register int l = lower_bound(ve + 1, ve + 1 + cnt, t) - ve;
		register int r = upper_bound(ve + 1, ve + 1 + cnt, t) - ve;
		ans[u] = r - l;
	}
}

void solve() {
	cin >> s >> n;
	rep(i, 1, n + 1) {
		cin >> t[i], ans[i] = 0;
		vec[sz(t[i])].pb(i);
	}
	ini[0] = 131 * 131;
	rep(i, 1, 26) ini[i] = ini[i - 1] * 131;
	rep(i, 1, sz(s) + 1) ha[i] = ha[i - 1] + ini[25 - (s[i - 1] - 'a')];
	rep(i, 1, sz(s) + 1) solve(i);
	rep(i, 1, n + 1) cout << ans[i] << endl;
	rep(i, 1, n + 1) vec[sz(t[i])].clear();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
