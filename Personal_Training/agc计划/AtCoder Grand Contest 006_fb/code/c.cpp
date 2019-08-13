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
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----
const int N = 1e5 + 7;
ll n, m, p[N], b[N], a[N], ans[N], now, vis[N], pp[N];
ll k;
int main(){
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i];
	per(i, 1, n+1) a[i] -= a[i-1];
//	rep(i, 1, n+1) de(a[i]);
	cin >> m >> k;
	rep(i, 1, m+1) cin >> b[i];
	rep(i, 1, n + 1) p[i] = i;
	rep(i, 1, m + 1) swap(p[b[i]], p[b[i]+1]);
	rep(i, 1, n+1) pp[p[i]] = i;
	rep(i, 1, n+1) p[i] = pp[i];
//	rep(i, 1, n+1) de(p[i]);
	rep(i, 1, n+1) if (!vis[i]){
		now = i;
		vi tmp;
		while (1) {
			vis[now] = 1;
			tmp.pb(now);
			now = p[now];
			if (now == i) break;
		}
		//de(sz(tmp));
		rep(i, 0, sz(tmp)) {
			int u = (i + k) % sz(tmp);
			//de(tmp[u]);
			ans[tmp[u]] = a[tmp[i]]; 
		}
	}
	//rep(i, 1, n+1) de(ans[i]);
	//de(a[1]);
	rep(i, 1, n+1) ans[i] += ans[i-1], cout << ans[i] << endl;	
	return 0; 
}


