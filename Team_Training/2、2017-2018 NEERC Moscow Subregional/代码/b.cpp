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

const int N = 5005;
string s;
int n, f[N][N], g[N][N], jc[N], ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> s;
	n = sz(s);
	s = " " + s;
	if (n == 1) {
		cout << 1 << endl;
		return 0; 
	}
	jc[0] = 1; rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	f[0][0] = 1;
	g[n+1][0] = 1;
	rep(i, 1, n+1) {
		if (s[i] == '>') rep(j, 1, i+1) f[i][j] = add(f[i][j], add(f[i-1][j-1], mul(f[i-1][j], j)));  
		else rep(j, 1, i+1) f[i][j] = add(f[i][j], add(mul(f[i-1][j], j), mul(f[i-1][j+1], j * (j + 1))));
	}
	per(i, 1, n+1) {
		if (s[i] == '<') rep(j, 1, n - i + 2) g[i][j] = add(g[i][j], add(g[i+1][j-1], mul(g[i+1][j], j)));  
		else rep(j, 1, n - i + 2) g[i][j] = add(g[i][j], add(mul(g[i+1][j], j), mul(g[i+1][j+1], j * (j + 1))));
	}
	rep(i, 1, n+1) {
		ans = 0;
		rep(j, 0, i) {
			ans = add(ans, mul(mul(f[i-1][j], g[i+1][j]), mul(mul(jc[j], 2), jc[j])));
			ans = add(ans, mul(mul(f[i-1][j], g[i+1][j+1]), mul(jc[j], jc[j+1])));
			ans = add(ans, mul(mul(f[i-1][j+1], g[i+1][j]), mul(jc[j], jc[j+1])));
		}
		cout << ans << " \n"[i == n];
	}
	return 0;
}


