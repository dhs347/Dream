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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef __int128 kll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 40;

int dig[N];
ll f[N][N * 9][N * 9];

ll dfs(int pos, int sum, int tot, bool lead, bool lim) {
	if(pos == -1) return !lead && sum == tot;
	if(!lim && !lead &&	~f[pos][sum][tot]) return f[pos][sum][tot];
	ll res = 0;
	int up = lim ? dig[pos] : 9;
	rep(i, 0, up + 1) {
		if(tot * i >= N * 9) break;
		res += dfs(pos - 1, sum + i, lead ? i : tot * i, lead && i == 0, lim & (i == up));
	}
	if(!lim && !lead) f[pos][sum][tot] = res;
	return res;
}

ll calc(kll x) {
	int pos = 0;
	while(x) dig[pos++] = x % 10, x /= 10;
	return dfs(pos - 1, 0, 1, 1, 1);
}
bool check(int i) {
	int sum = 0, tot = 1;
	while(i) {
		sum += i % 10;
		tot *= i % 10;
		i /= 10;
	}
	return sum == tot;
}
void bf(int x) {
	int cnt = 0;
	int ans = 0;
	rep(i, 1, x + 1) {
		if(check(i)) dd(++cnt), de(i);
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	memset(f, -1, sizeof(f));
//	de(calc(1000000));
	bf(1000000);
	ll k; cin >> k;
	kll l = 1, r = 1e37, ans = 0;
	while(l <= r) {
		kll mid = l + r >> 1;
		if(calc(mid) >= k) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	vi v; while(ans) v.pb(ans % 10), ans /= 10;
	reverse(all(v));
	for(auto u : v) cout << u; cout << endl;
	return 0;
}
