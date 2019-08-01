#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 10;
int T, n, a[N], x, y, ans[N], b[3];
pair<char, char> pre[N][3][3];
bool f[N][3][3];
bool check(int x, int y, int z, int a) {
	b[0] = x; b[1] = y; b[2] = z;
	sort(b, b+3);
	return b[1] == a;
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n; n -= 2;
		rep(i, 1, n + 1) cin >> a[i];
		rep(i, 2, n + 3) rep(o1, 0, 3) rep(o2, 0, 3) f[i][o1][o2] = 0;
		rep(o1, 0, 2)  f[2][o1][0] = 1;
		rep(i, 3, n + 3) {
			rep(o1, 0, 3) 
				rep(o2, 0, 3) if (f[i-1][o1][o2]) {
					x = a[i - 1 - o1], y = a[i - 2 - o2];
					rep(o3, 0, 3) if (i - o3 <= n && check(x, y, a[i-o3], a[i-2])) {
						f[i][o3][o1] = 1;
						pre[i][o3][o1] = mp(o1, o2);
					}
				}
		}
		bool ok = 0;
		rep(o1, 0, 3) {
			rep(o2, 0, 3) if (f[n+2][o1][o2]) {
				pii t = mp(o1, o2); int m = n + 2;
				while (m >= 2) {
					ans[m] = a[m - t.fi];
					ans[m - 1] = a[m - 1 - t.se];
					t = pre[m][t.fi][t.se];
					m--;
					
				}
				ok = 1;break;
			}
			if (ok) break;
		}
		if (!ok) cout << -1 << endl;
		else rep(i, 1, n+3) cout << ans[i] << " \n"[i == n + 2];
	}
	 
	return 0;
}

