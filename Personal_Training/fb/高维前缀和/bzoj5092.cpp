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
int n, a[N], b[N], m, S, ans, now;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i], a[i] ^= a[i-1];
	m = 20; S = pw(m) - 1;
	rep(i, 0, S+1) b[i] = n + 1;
	rep(i, 1, n+1) {
		b[a[i]] = min(b[a[i]], i);
	} 
	rep(i, 0, m) rep(j, 0, S+1) if (!(j & pw(i))) b[j] = min(b[j], b[j ^ pw(i)]);
	rep(i, 1, n+1) {
		ans = 0;now = 0;
		per(j, 0, m) {
			if (pw(j) & a[i]) {
				ans += pw(j);	
			}else {
				now += pw(j);
				if (b[now] <= i) ans += pw(j) * 2;
				else now -= pw(j);
			}
		}
		cout << ans << endl;
	}
	return 0;
}


