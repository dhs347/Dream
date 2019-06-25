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
ll inv[200000], x, t, invx, ok;
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
vi a[50];
int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> n;
	nn = n;
	rep(i, 1, 110000) inv[i] = kpow(i, P - pw(30) - 1);
	//de(inv[23] * 23 % P);
	per(i, 0, 31) {
		cnt[i] = min(pw(30 - i), 1ll * nn / (i + 1));
		nn -= cnt[i];
	}
	rep(i, 0, 31) {
		//de(cnt[i]);
		rep(j, 0, cnt[i]) {
			nn++;
			x = (2 * j + 1) * pw(i);
			assert(x < P);
			cout << x << " \n"[nn == n];
		}
	}
	fflush(stdout);
	assert(nn == n);
	rep(i, 1, n/2 + 1) {
		cin >> x;
		t = 0;
		while (x % 2 == 0) {
			x /= 2;
			t++;
		}
		a[t].pb(x);
	}
	per(i, 0, 31) {
		if (sz(a[i])) {
			rep(j, 0, cnt[i]) {
				x = a[i][0] * inv[j * 2 + 1] % P;
				invx = kpow(x, P - pw(30) - 1);
				ok = 1;
				rep(k, 0, 31) {
					rep(l, 0, sz(a[k])) if (a[k][l] * invx % P> cnt[k] * 2 - 1) {ok = 0; break;}
					if (!ok) break;
				}
				if (ok) {
					cout << x << endl;
					assert(x >= 1 && x < P);
					fflush(stdout);
					return 0;
				}
			} 
			break;
		}
	}
	return 0;
}
