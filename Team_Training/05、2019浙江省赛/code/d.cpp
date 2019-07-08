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
const int N = 1e5 + 8;
bool vis[N];
int n, T, nn, now;
int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		fill_n(vis, n+1, 0);
		nn = n;
		while (nn >= 1) {
			vis[nn] = 1;
			nn = nn / 2 - 1;
		}
		vi ans;
		now = 1;vis[0] = 1;
		while (1) {
			vis[now] = 1; ans.pb(now);
			if (vis[now-1]) {
				if (now * 2 > n) break;
				if (vis[now * 2]) now = now * 2;
				else if (vis[now * 2 + 1]) now = now * 2 + 1;
				else now = now * 2;
			}else now = now - 1;
		}
		rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans)-1];
	}
	return 0;
}

