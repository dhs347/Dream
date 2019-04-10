// 求最大基环树 
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

const int N = 2e5 + 7;
int u, v, w, n, m, ans, f[N], cir[N];
pair<int, pii> a[N];

int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) f[i] = i;
	rep(i, 1, m+1) {
		cin >> u >> v >> w; 
		a[i] = mp(w, mp(u, v));
	}
	sort(a+1, a+m+1);
	per(i, 1, m+1) {
		u = a[i].se.fi; v = a[i].se.se; w = a[i].fi;
		u = get(u); v = get(v);
		if (u != v) {
			if (cir[u] && cir[v]) continue;
			f[u] = v;
			cir[v] |= cir[u];
			ans += w;
		} else if (!cir[u]){
			cir[u] = 1;
			ans += w;
		}
	}
	cout << ans << endl;
	return 0;
}

