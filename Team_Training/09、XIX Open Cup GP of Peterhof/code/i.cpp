#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll inf = 2e9;

int ans, now, cc;
map<int, int> dp, ne;

int dfs(int x) {
	if(dp.count(x)) return dp[x];
	int n = x; 
	while((n & 1) == 0) n >>= 1;
	while(n % 3 == 0) n /= 3;
	if(n == 1) return dp[x] = 0;
	int Ne = x + 1, res = inf;
	if((x & 1) == 0) {
		int t = dfs(x >> 1);
		if(res > t) res = t, Ne = (x >> 1);
	}
	if(x % 3 == 0) {
		int t = dfs(x / 3);
		if(res > t) res = t, Ne = x / 3;
	}
	if(x % 6 != 0) {
		int t = dfs(x + 1) + 1;
		if(res > t) Ne = x + 1, res = t;
	}
	ne[x] = Ne;
	return dp[x] = res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	for(ll i = 1; i <= inf; i <<= 1) for(ll j = 1; j * i <= inf; j *= 3) if(i * j != 1) {
		if(j != 1) ne[i * j] = i * j / 3;
		else ne[i * j] = (i * j >> 1);
	}
	int x; cin >> x; ans = dfs(x);
	cout << ans << endl;
	while(1) {
		cout << x << " \n"[x == 1];
		if(x == 1) break;
		x = ne[x];
	}
	return 0;
}
