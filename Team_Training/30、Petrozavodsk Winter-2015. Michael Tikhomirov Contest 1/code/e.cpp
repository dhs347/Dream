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
#define pw(c) (1ll<<(c))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

const int N = 505;

namespace Gu {

int n, m;
	bitset<N> a[N];
	int x[N];
	int p, col, k;
	int free[N], fnum;

	void genx(int msk, int var) {
		rep(i, 0, fnum) x[free[i]] = (msk>>i&1);
		per(i, 0, k) {
			rep(j, 0, var) if(a[i][j]) {
				p = j; break;
			}
			x[p] = a[i][var];
			rep(j, p + 1, var) x[p] ^= (a[i][j] && x[j]);
		}
	}
	int guss(int equ,int var) {
		fnum = 0;
		for(k = 0, col = 0; k < equ && col < var; k++, col++) {
			p = k; rep(i, k, equ) if(a[i][col]) {
				p = i; break;
			}
			if(p != k) swap(a[k], a[p]);
			if(!a[k][col]) {
				k--; free[fnum++] = col;
				continue;
			}
			rep(i, 0, equ) if(i != k && a[i][col]) a[i] ^= a[k];
		}
		rep(i, col, var) free[fnum++] = i;
		rep(i, k, equ) if(a[i][var]) return -1;
		if(k < var) {
			genx(0, var);
			return var - k;
		}
		per(i, 0, var) {
			x[i] = a[i][var];
			rep(j, i + 1, var) x[i] ^= (a[i][j] && x[j]);
		}
		return 0;
	}
	void gao(int i, int j) {
		a[i].flip(i);;
		a[i].flip(j);;
		a[i].flip(n);;
	}
	void solve() {
		cin >> n >> m;
		rep(i, 1, m + 1) {
			int u, v; cin >> u >> v;
			--u, --v;
			gao(u, v); gao(v, u);
		}
		int t = guss(n, n);
		if(t == -1) {
			cout << "IMPOSSIBLE" << endl;
		} else {
			rep(i, 0, n) cout << (char)(x[i] + 'A'); cout << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	Gu::solve();
	return 0;
}
