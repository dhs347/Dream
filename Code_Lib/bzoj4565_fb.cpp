// 一个01串可选k个合并为一个，得到对应2^k种权值中一个，求最大价值
// 区间dp，主要把合并过程看成一棵树，枚举后缀为0或1以及前缀的状态合并 
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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1500;
ll n, k, a[N], w[N], x, S, f[305][305][1 << 7], ans;
string s;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	cin >> s;
	S = pw(k) - 1;
	rep(i, 0, S+1) cin >> a[i] >> w[i];
	memset(f, -0x3f, sizeof(f));
	rep(i, 0, n) f[i][i][s[i]-'0'] = 0;
	rep(len, 2, n+1) {
		rep(l, 0, n) if (l + len - 1>= n) break;
		else {
			int r = l + len - 1;
			for (int t = r; t > l; t -= k - 1) {
				x = (r - l) % (k - 1);
				if (x != 0) {
					x = pw(x);
					rep(msk, 0, x) {
						if (f[l][t-1][msk] < 0) continue;
						ll &t1 = f[l][r][msk * 2];
						ll &t2 = f[l][r][msk * 2 + 1];
						t1 = max(t1, f[l][t-1][msk] + f[t][r][0]);
						t2 = max(t2, f[l][t-1][msk] + f[t][r][1]);
					}
				}else {
					x = pw(k-1);
					rep(msk, 0, x) {
						if (f[l][t-1][msk] < 0) continue;
						ll &t1 = f[l][r][a[msk * 2]];
						ll &t2 = f[l][r][a[msk * 2 + 1]];
						t1 = max(t1, f[l][t-1][msk] + f[t][r][0] + w[msk * 2]);
						t2 = max(t2, f[l][t-1][msk] + f[t][r][1] + w[msk * 2 + 1]);
					}
				}
			}
		}
	}
	rep(i, 0, S) ans = max(ans, f[0][n-1][i]);
	cout << ans;
	return 0;
}


