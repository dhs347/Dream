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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9 + 7, N = 1010; // todo

int lr(ll n, int m, vi a, vi c) {
	if(n < m) return (a[n] + P) % P;
	vector<ll> v(m, 0), u(m << 1, 0);
	v[0] = 1;
	for(ll x = 0, W = n ? 1ll << (63 - __builtin_clzll(n)) : 0; W; W >>= 1, x <<=1) {
		fill(all(u), 0);
		int b = !!(n & W); if(b) x++;
		if(x < m) {
			u[x] = 1;
		} else {
			rep(i, 0, m) rep(j, 0, m) (u[i + b + j] += v[i] * v[j]) %= P;
			per(i, m, 2 * m) rep(j, 0, m) (u[i - m + j] += c[j] * u[i]) %= P;
		}
		copy(u.begin(), u.begin() + m, v.begin());
	}
	ll ans = 0;
	rep(i, 0, m) (ans += v[i] * a[i]) %= P;
	return (ans + P) % P;
}
int add(int a, int b) {
		if((a += b) >= P) a -= P;
		return a < 0 ? a + P : a;
	}
	int mul(int a, int b) {
		return 1ll * a * b % P;
	}
	int kpow(int a, int b) {
		int r = 1;
		while(b) {
			if(b & 1) r = mul(r, a);
			a = mul(a, a); 
			b >>= 1;
		}
		return r;
	}


namespace GI {
	static const int N = ::N;
	int a[N][N], x[N];
	int free[N], fnum, k, col, p;
	void genx(int var) {
		int pre = var; fnum = 0;
		per(i, 0, k) {
			rep(j, 0, var) if (a[i][j]) { p = j; break; }
			rep(j, 0, i) if (a[j][p]) {
				int t = a[j][p];
				rep(l, p, var+1) a[j][l] = add(a[j][l], -mul(a[i][l], t));
			}
			rep(j, p+1, pre) free[fnum++] = j, x[j] = 0; pre = p; 
			x[p] = a[i][var];
			rep(j, p+1, var) x[p] = add(x[p], -mul(a[i][j], x[j]));
		}
		rep(j, 0, pre) free[fnum++] = j;
	}
	
	int Gauss(int equ, int var) {
		for(k = col = 0; k < equ && col < var; ++k, ++col) {
			p = k; rep(i, k, equ) if(a[i][col]) {
				p = i; break;
			}
			if(p != k) rep(j, col, var + 1) swap(a[p][j], a[k][j]);
			if(!a[k][col]) {
				k--; continue;
			}
			int inv = kpow(a[k][col], P - 2);
			//de(mul(2, inv));
			rep(i, col, var + 1) a[k][i] = mul(a[k][i], inv);
			rep(i, k + 1, equ) if(a[i][col]) {
				int t = a[i][col];
				rep(j, col, var + 1) a[i][j] = add(a[i][j], -mul(a[k][j], t));
			}
		}
		rep(i, k, equ) if(a[i][var]) return -1;
		if(k < var) {
			genx(var);
			return var - k;
		}
		per(i, 0, var) {
			int t = a[i][var];
			rep(j, i + 1, var) if(a[i][j]) t = add(t, -mul(a[i][j], x[j]));
			x[i] = t;
		}
		return 0;
	}

};

int k, T, w[200];
ll n;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> k >> n;
		rep(i, 1, k * 2+1) cin >> w[i];
		rep(i, 0, k) {
			rep(j, 0, k) GI :: a[i][j] = w[i + k - j];
			GI :: a[i][k] = w[k + i + 1];
		}
		GI :: Gauss(k, k);
		vi t1, t2;
		t1.pb(P - GI :: x[k - 1]);
		rep(i, 0, k-1) t1.pb(add(GI :: x[k - i - 1],  - GI :: x[k - i - 2])); 
		t1.pb(add(GI :: x[0], 1));
		t2.pb(w[1]);
		rep(i, 1, k+1) t2.pb(add(t2.back(), w[i+1]));
		cout << lr(n - 1, k + 1, t2, t1) << endl;
	}
	return 0;
}
