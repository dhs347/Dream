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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 110;

ll f[N][N * 9][N * 9], g[N][N * 9][N * 9];
int ans[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	f[0][0][1] = 1;
	rep(i, 0, N - 1) rep(j, 0, N * 9) rep(k, 0, N * 9) if(f[i][j][k]) {
		rep(c, 1, 10) if(k * c < N * 9) {
			int nj = j + c, nk = k * c;
			f[i + 1][nj][nk] += f[i][j][k];
		}
	}
	ll cc = 0;
	rep(i, 1, N) rep(j, 0, N * 9) rep(k, 0, N * 9) g[i][j][k] = g[i - 1][j][k] + f[i][j][k], cc += f[i][j][k];
	de(cc - 1e18);
	ll k; cin >> k;
	k = 1e10;
	int p = 0;
	per(i, 1, N) {
		__int128 cnt = 0;
		rep(j, 1, N * 9) cnt += g[i][j][j];
		if(cnt >= k) {
			p = i;
		} else {
			k -= cnt;
			break;
		}
	}
	int sum = 0, tot = 1;
	per(i, 1, p) {
		rep(j, 1, 10) {
			int count = 0;
			for(int c = 1; c * j * tot < N * 9; ++c) {
				int t = c * j * tot - sum - j;
				if(t >= 0 && t < N * 9) count += f[i][t][c];
			}
			if(count >= k) {
				cout << j; 
				sum += j; 
				tot *= j;
				break;
			} else {
				k -= count;
			}
		}
	}
	rep(c, 1, 10) if(sum + c == tot * c) {
		--k;
		if(k == 0) {
			cout << c;
			break;
		}
	}
	cout << endl;
	return 0;
}
