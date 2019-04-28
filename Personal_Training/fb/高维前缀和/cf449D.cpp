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

const int N = 1 << 20;

int n, a[N], p2[N], m, S, x, ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;m = 20; S = pw(m) - 1;
	rep(i, 1, n+1) {
		cin >> x; a[x]++;
	}
	p2[0] = 1; rep(i, 1, n+1) p2[i] = mul(p2[i-1], 2);
	rep(i, 0, m) rep(j, 0, S+1)  if (!(j & pw(i))) a[j] += a[j ^ pw(i)];
	rep(i, 1, S+1) {
		int t = __builtin_popcount(i);
		if (t & 1) ans = add(ans, p2[a[i]] - 1);
		else ans = add(ans, -(p2[a[i]] - 1));
	}
	ans = add(p2[n] - 1, -ans);
	cout << ans << endl;
 	return 0;
}


