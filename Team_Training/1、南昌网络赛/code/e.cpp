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
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 200004;
int vis[N], m, T, n, a[N], s[N], ans, ansr, ansl, r, l;

int sg(int x) {
	return x * 2 + (__builtin_popcount(x) % 2 == 0);
}

map<int, int> M;

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) cin >> a[i], s[i] = s[i-1] ^ sg(a[i]);
		a[n+1] = m;
		ans = 0;
		a[0] = -1;
		rep(i, 1, n+2) {
			r = a[i] - 1;
			l = a[i-1] + 1;
			if (r - l + 1 > ans) {
				ans = r - l + 1;
				ansl = l;
				ansr = r;
			}
		} 
		M.clear();
		M[0] = -1;
		rep(i, 1, n+1) {
			r = a[i+1] - 1;
			if (M.count(s[i])) {
				if (ans < r - M[s[i]]) ans = r - M[s[i]], ansr = r, ansl = M[s[i]] + 1;
			}else M[s[i]] = a[i];
		}	
		cout << "Case " << cas + 1 << ":" << endl;
		cout << ans << endl;
		if (ans > 0) cout << ansl << " " << ansr << endl; 
	}
	return 0;
}

