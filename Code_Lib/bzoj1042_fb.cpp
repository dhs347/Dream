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

const int N = 1e5 + 7;
int c[10], w[10], T, S, s, num, o;
ll ans, f[N];
int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	rep(i, 0, 4) cin >> w[i]; cin >> T;
	int n = 100000;
	f[0] = 1;
	rep(i, 0, 4) 
		rep(j, w[i], n+1) {
			f[j] += f[j - w[i]];
		}
	S = pw(4) - 1;
	rep(cas, 0, T) {
		rep(i, 0, 4) cin >> c[i]; cin >> s;
		ans = 0;
		rep(i, 0, S+1) {
			num = 0; o = 1;
			rep(j, 0, 4) if (i & pw(j)) num += (c[j] + 1) * w[j], o *= -1;
			if (num <= s) {
				ans += o * f[s - num];
			}
		}
		cout << ans << endl;
	}
	return 0;
}


