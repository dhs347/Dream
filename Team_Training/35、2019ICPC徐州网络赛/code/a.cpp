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
typedef __int128 ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 7;
long long a[N], mod[N];
ll ans;
int n;
	__int128 M, R;
	void exgcd(ll a, ll b, ll &x, ll &y) {
		if (b == 0) {x = 1; y = 0; return;}
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	ll Inv(ll a, ll mod) {
		ll x = 0, y = 0;
		exgcd(a, mod, x, y);
		x %= mod;
		return x < 0 ? x + mod : x;
	}
	ll CRT(int n, long long *a, long long *mod) {
		M = mod[1], R = a[1];
		rep(i, 2, n+1) {
			if (M > 1e15) {
				rep(j, 1, n+1) if (R % mod[i] != a[i]) return -1;
				return R;
			}
			ll g = __gcd(M, (__int128)mod[i]);
			ll inv = Inv(M / g, mod[i] / g);
			if ((a[i] - R) % g) return -1;
			R += inv * ((a[i] - R) / g) % (mod[i] / g) * M;
			M = M / g * mod[i];
			R = (R % M + M ) % M;
		}
		if (R == 0) R = M;
		return R;
	}

long long f[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) cin >> mod[i] >> a[i], a[i] %= mod[i];
	ans = CRT(n, a, mod);
	if (ans == -1) {
		cout << "Tankernb!" << endl;
	}else {
		f[0] = f[1] = 1;
		rep(i, 2, N) {
			f[i] = f[i-1] + f[i-2];
			if (f[i] >= ans) {
				if (f[i] == ans) cout << "Lbnb!"; else cout << "Zgxnb!";
				cout << endl;
				return 0;
			}
		}
	}

	return 0;
}
