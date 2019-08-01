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
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

ll P, Q, ans;

ll mul(ll a, ll b, ll P) {
	return (__int128)a * b % P;
}

ll kpow(ll a, ll b, ll P) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = mul(res, a, P);
		a = mul(a, a, P);
		b >>= 1;
	}
	return res;
}

int spp(ll n, int base) {
	ll n2 = n-1, res;
	int s = 0;
	while (n2 % 2 == 0) n2 >>= 1, s++;
	res = kpow(base, n2, n);
	if (res == 1 || res == n - 1) return 1;
	s--;
	while (s >= 0) {
		res = mul(res, res, n);
		if (res == n - 1) return 1;
		s--;
	}
	return 0;
}

int isprime(ll n) {
	static ll testNum[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	static ll lim[] = {4, 0, 1373653ll, 25326001ll, 25000000000ll, 2152302898747ll, 3474749660383ll, 34155007172832ll, 0, 0, 0, 0};
	if (n < 2 || n == 3215031751ll) return 0;
	rep(i, 0, 12) {
		if (n < lim[i]) return 1;
		if (spp(n, testNum[i]) == 0) return 0; 
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	cin >> T;
	rep(cas, 0, T) {
		cin >> P;
		for (ll i = P - 1; i >= 0; i--) {
			if (isprime(i)) {
				Q = i;
				break;
			}
		}
		ans = P - 1;
		for(ll i = P - 1; i >= Q + 1; i--) ans = mul(ans, kpow(i, P - 2, P), P);
		cout << ans << endl;
	}
	return 0;
}
