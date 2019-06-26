#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const ll P = pw(31);
ll inv[300000], x, t, invx, ok, a[300000];
ll kpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return res;
}

int n, cnt[50], nn;
int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) cout << i * 2 - 1 << " \n"[i == n];
	fflush(stdout); 
	rep(i, 1, 210000) inv[i] = kpow(i, P - pw(30) - 1);
	rep(i, 1, n/2+1) cin >> a[i];
	rep(i, 1, n+1) {
		x = a[1] * inv[i * 2 - 1] % P;
		invx = kpow(x, P - pw(30) - 1);
		ok = 1;
		rep(j, 1, n / 2 + 1) {
			t = a[j] * invx % P;
			if (t > n * 2 - 1) {
				ok = 0;
				break;
			}
		} 
		if (ok) {
			cout << x << endl;
			fflush(stdout);
			return 0;
		}
	}
	return 0;
}
