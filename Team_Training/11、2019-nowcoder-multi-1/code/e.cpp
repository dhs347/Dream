#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1e5 + 76, P = 1e9 + 7;
int f[2][N], n, m, o, d, nn;

int add(int a, int b) {
	a += b;
	return a % P;
}

int main() {
	//ios :: sync_with_stdio(0);
	//std :: cin.tie(0);
	while (cin >> n >> m) {
		nn = (n + m) * 2;
		d = 4001; o = 0;
		rep(j, -n-5, m+5) f[0][j + d] = 0;
		f[0][d] = 1;
		rep(i, 1, nn+1) {
			o ^= 1;	
			rep(j, -n-5, m+5) f[o][j + d] = 0;
			rep(j, max(-n, -i), min(m, i)+1) {
				f[o][j + d] = add(f[o ^ 1][j - 1 + d], f[o ^ 1][j + 1 + d]);
			}
		}
		cout << f[o][d] << endl;
	}
	return 0;
}
