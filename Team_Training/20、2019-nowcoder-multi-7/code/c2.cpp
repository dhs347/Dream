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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n;
int h[N], c[N], p[N], cur[N];
ll cnt[222];

bool cmp(int i, int j) {
	return h[i] < h[j];
}

ll calc(ll k) {
	ll ans = 0;
	per(i, 1, 201) {
		ll t = min(k, cnt[i]);
		ans += t * i;
		k -= t;
		if(k == 0) return ans;
	}
	return ans;
}

void solve() {
	rep(i, 1, n + 1) cur[i] = i;
	sort(cur + 1, cur + 1 + n, cmp);
	ll tot = 0; rep(i, 1, n + 1) tot += 1ll * p[i] * c[i];
	memset(cnt, 0, sizeof(cnt));
	ll sum = 0, ans = tot, S = 0;
	for(int i = 1, j = 1; j <= n; ++j) {
		int u = cur[j];
		sum += p[u];
		S += p[u] * 1ll * c[u];
		if(j == n || h[u] != h[cur[j + 1]]) {
			ll t = calc(sum - 1);
			ans = min(ans, tot - t - S);
			sum = S = 0;
			rep(k, i, j + 1) cnt[c[cur[k]]] += p[cur[k]];
			i = j + 1;
		}
	}
	/*
	rep(i, 1, n + 1) {
		int u = cur[i];
		sum += p[u];
		cnt[c[u]] += p[u];
		if(i == n || h[u] != h[cur[i + 1]]) {
			ll t = calc(sum * 2);
			ans = min(ans, tot - t);
			sum = 0;
		}
	}*/
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		rep(i, 1, n + 1) cin >> h[i] >> c[i] >> p[i];
		solve();
	}
	return 0;
}
