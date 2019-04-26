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
const db eps = 1e-10;
int n, S;
db p[N], ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(8);
	cin >> n;
	S = pw(n) - 1;
	rep(i, 0, S + 1) {
		cin >> p[i];
	} 
	rep(i, 0, n)
		rep(j, 0, S+1) if(j & pw(i)) p[j] += p[j ^ pw(i)];
	rep(i, 1, S + 1) {
		int t = __builtin_popcount(i);
		db x = (1 - p[~i & S]);
		if (x < eps) {
			cout << "INF";
			return 0;
		}
		if (t & 1) ans += 1 / x;
		else ans -= 1 / x;
	}
	cout << ans << endl;
	return 0;
}


