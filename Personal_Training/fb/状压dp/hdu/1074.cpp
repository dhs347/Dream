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

const int N = 20;
string s[N];
int d[N], c[N], T, p, fa[1 << 15], f[1 << 15], n, S, w, a[1 << 15];
int main() {
	freopen("a.in","r",stdin);
	//std::ios::sync_with_stdio(false);
	//std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, n) {
			cin >> s[i] >> d[i] >> c[i];
		}
		S = pw(n) - 1;
		memset(f, 0x3f, sizeof(f));
		f[S] = 0;
		rep(i, 0, S+1) {
			a[i] = 0;
			rep(j, 0, n) if (!(pw(j) & i)) a[i] += c[j];
		}
		per(i, 0, S+1) rep(j, 0, n) if (pw(j) & i) {
			p = i ^ pw(j);
			w = max(0, a[p] - d[j]);
			if (f[p] > f[i] + w) {
				f[p] = f[i] + w;
				fa[p] = i;
			}
		}
		vi ans;
		p = 0;
		while (p != S) {
			ans.pb(__builtin_ctz(p ^ fa[p]));
			p = fa[p];
		}
		reverse(all(ans));
		cout << f[0] << endl;
		for (auto v : ans) cout << s[v] << endl;
	}
	return 0;
}


