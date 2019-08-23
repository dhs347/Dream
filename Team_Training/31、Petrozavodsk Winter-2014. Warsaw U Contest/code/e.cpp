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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 1000, M = 1000;

int m;
ll a[N], dp[M], dp2[M], T, n;
ll t[1010101];

bool check(ll nn) {
	int l = 1, r = m;
	while (l <= r) {
		while (r > l && t[l] + t[r] > nn) r--;
		if (t[l] + t[r] == nn) return 1;
		l++;
	}
	return 0;
}

ll solve(ll n) {
	rep(k, 1, 10) if ((n - k) % 3 == 0){
		ll nn = (n - k) / 3;
		if (nn % 2 == 0) {
			if (k >= 3) return k;
			//int p = sqrt(nn);
			ll l = 1, r = sqrt(nn) + 10, ans = 0;
			while (l <= r) {
				ll mid = (l + r) >> 1;
				if (mid * (mid - 1) <= nn) ans = mid, l = mid + 1;
				else r = mid - 1;
			}
		//	if (n == 7) de(nn);
			if (ans * (ans - 1) == nn) return k;
			nn /= 2;
			if (k == 2 && check(nn * 8 + 2)) return k; 
		}
	}
	return -1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ll ma = 1e12;
	ma = ma / 6 * 8 + 2;
	for (int i = 1; 1ll * i * i <= ma; i += 2) {
		t[++m] = 1ll * i * i;
	}
	while (cin >> n) {
		if (n == 0) break;
		cout << solve(n) << endl;
	}
	return 0;
	
	rep(i, 1, N) a[i] = 3ll * i * i - 3 * i + 1;
	//de(a[N - 1]);
	memset(dp, 0x3f, sizeof(dp));
	memset(dp2, 0x3f, sizeof(dp2));
	dp[0] = 0;dp2[0] = 0;
	rep(i, 1, N) rep(j, a[i], M) dp[j] = min(dp[j], dp[j - a[i]] + 1);
	//rep(i, 1, N) rep(j, t[i], M) dp2[j] = min(dp2[j], dp2[j - t[i]] + 1);
/*	rep(i, 1, 100) {
		if (!(i & 1)) dd(i), de(dp2[i]);
	}
	return 0;
	*/
	rep(i, 1, M) if(dp[i] != solve(i)) {
		dd(i);dd(dp[i]), de(solve(i));
		break;
	}
	return 0;
}
