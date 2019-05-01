#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2000;
int b[N][N], n, k;

namespace Gauss{
	static const int N = 2e3 + 10;
	bitset<N> a[N];
	int Gauss(int equ, int var) {
		int p, col, k;
		for (k = 0, col = 0; k < equ && col < var; k ++, col++) {
			p = k; rep(i, k, equ) if (a[i][col]) {p = i;break;}
			if (p != k) swap(a[k], a[p]);
			if (!a[k][col]) {
				k--;
				continue;
			}
			rep(i, 0, equ) if (i != k && a[i][col]) a[i] ^= a[k];
		}
		rep(i, k, equ) if (a[i][var]) return -1;
		return 1;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 0, n) {
		rep(j, 0, k) cin >> b[i][j];
	}
	rep(j, 0, k) {
		rep(i, 0, n) Gauss :: a[j][i] = abs(b[i][j]) & 1; 
	}
	rep(i, 0, n+1) Gauss :: a[k][i] = 1;
	if (Gauss :: Gauss(k + 1, n) != -1) {
		cout << "No";
	}else cout << "Yes";
	return 0;
}
