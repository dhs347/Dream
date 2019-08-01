#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 105;
int t, T, m, ans[105], t1, t2, n;
bool f[100][N][N];
pii now;
pair<int, pii> pre[100][N][N];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T; m = 100;
	rep(cas, 0, T) {
		cin >> n;
		//rep(n, 1, 101) {
			memset(f, 0, sizeof(f));
			f[0][0][0] = 1;
			rep(i, 1, m+1) {
				rep(j, 0, n) rep(k, 0, n) rep(l, 0, 10) if (f[i-1][j][k]){
					if (i == 1 && l == 0) continue;
					t1 = j * 10 + l;
					t1 %= n;
					t2 = k + l;
					t2 %= n;
					f[i][t1][t2] = 1;
					pre[i][t1][t2] = mp(l, mp(j, k));
				}
				if (f[i][0][0]) {
					vi tmp;
					t = i; now = mp(0, 0);
					while (t > 0) {
						auto s = pre[t][now.fi][now.se];
						now = s.se;
						tmp.pb(s.fi);
						t--;
					}
					reverse(all(tmp));
					for (auto u : tmp) cout << u;
					cout << endl;
					break;
				}
			}
	//	}
	}
	return 0; 
}
