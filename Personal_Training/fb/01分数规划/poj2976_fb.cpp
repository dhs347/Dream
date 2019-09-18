#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
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
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e3 + 7;
int n, k, a[N], b[N];
db l, r, mid, c[N];

bool check(db mid) {
	rep(i, 1, n+1) c[i] = a[i] - b[i] * mid;
	sort(c + 1, c + n + 1);
	db res = 0;
	per(i, 1, n+1) if (i > k){
		res += c[i];
	}
	return res >= 0;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n >> k) {
		if (n == 0 && k == 0) break;
		l = r = 0;
		rep(i, 1, n+1) cin >> a[i], r += a[i];
		rep(i, 1, n+1) cin >> b[i];
		rep(tim, 0, 50) {
			mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		cout << round(l * 100) << endl;
	}
	return 0;
}


