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

const int N = 100;
int T, S, n;
db f[1 << 20], d[30][30];
pair<db, db> s, a[N];
db inf = 1e10;

db dis(pair<db, db> a, pair<db, db> b) {
	return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> s.fi >> s.se;
		cin >> n; n *= 2;
		rep(i, 0, n) cin >> a[i].fi >> a[i].se;
		S = pw(n) - 1;
		rep(j, 0, n)
			rep(k, j+1, n) 
				d[j][k] = d[k][j] = min(dis(s, a[j]), dis(s, a[k])) + dis(a[j], a[k]);
		rep(i, 0, S) f[i] = inf;
		f[S] = 0;
		per(i, 0, S+1) if (f[i] < 100000000){
			int t1 = lb(i);
			int p1 = __builtin_ctz(t1);
			for (int x = i - lb(i), t = lb(x); x > 0; x -= t, t = lb(x)) {
				int p = __builtin_ctz(t);
				f[i ^ t ^ t1] = min(f[i ^ t ^ t1], f[i] + d[p][p1]);
			}
		}
		cout << "Case #" << cas+1 << ": " << f[0] << endl;
	}
	return 0;
}


