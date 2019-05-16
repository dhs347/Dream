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
//---

const int N = 3e4 + 7;
int n, k, cnt[N], pp;

namespace PX{
	const int N = :: N, M = sqrt(N) + 5;
	const int K = 7;
	int n, k, B, pos[K][N];
	bitset<N> s[K][M];
	vector<pii> V[K];
	
	struct node{
		int d[K];
	} a[N];
	
	void init(int _n, int _k) {
		n = _n; k = _k;
		rep(i, 1, n+1) rep(j, 0, k) cin >> a[i].d[j];
		rep(i, 1, n+1) rep(j, 0, k) V[j].pb(mp(a[i].d[j], i));
		rep(j, 0, k) sort(all(V[j]));
		rep(i, 1, n+1) 
			rep(j, 0, k) 
				a[i].d[j] = lower_bound(all(V[j]), mp(a[i].d[j], i)) - V[j].begin(), pos[j][a[i].d[j]] = i;
		B = sqrt(n);
		rep(j, 0, k) {
			bitset<N> tmp; int id = 1; 
			rep(i, 0, n) {
				tmp.set(pos[j][i]);
				if (i == id * B - 1) s[j][id++] = tmp; 
			}
		}
	}	 
	int qry(node a) {
		bitset<N> ans; ans.set();
		rep(j, 0, k) {	
			int ed = lower_bound(all(V[j]), mp(V[j][a.d[j]].fi, n+1)) - V[j].begin() - 1;
			bitset<N> tmp;int id = ed / B, st = id ? (id - 1) * B : 0;
			if (id) tmp = s[j][id - 1];
			rep(i, st, ed+1) tmp[pos[j][i]] = 1;
			ans &= tmp;
		}
		return ans.count();	
	}
}



int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n; k = 5;
	PX :: init(n, k);
	//rep(i, 1, n+1) cout << PX :: qry(PX :: a[i]) << endl;
	rep(i, 1, n+1) cout << PX :: qry(PX :: a[i]) - 1 << endl;
	//cnt[PX :: qry(PX :: a[i])-1]++;
	//rep(i, 0, n) cout << cnt[i] << endl;
	return 0;
}

