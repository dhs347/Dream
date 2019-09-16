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
typedef unsigned int uint;
typedef uniform_int_distribution<ll> RR;
mt19937 gen(998244353);
ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5e4+ 10;
uint p17[20], p19[20], seed, p2[20];
int L, R, o;
bool aa[N * 2];

struct mat{
	unsigned short a[16], b[16];
	mat() {memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));}
	mat operator * (const mat & c) const {
		mat r;
		rep(i, 0, 16) if (a[i]) {
			rep(j, 0, 16) if (aa[a[i] & c.b[j]]) r.a[i] += p2[j], r.b[j] += p2[i];
		}	 
		return r; 
	}
	uint get() {
		uint t = 0;
		rep(i, 0, 16) rep(j, 0, 16) if (a[i] & p2[j]) t += p17[i] * p19[j];
		return t;
	}
} ans, pre[N], suf[N], a[N], e;

int l1, r1, l2, r2;

mat get() {
	mat r;
	rep(i, 0, 16) { 
		seed ^= seed * seed + 15; 
		rep(j, 0, 16) if ((seed >> j) & 1) r.a[i] += p2[j], r.b[j] += p2[i];
	}
	return r;
}

int main() {
	//FO(a); 
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	int T;
	p17[0] = p19[0] = p2[0] = 1;
	rep(i, 1, 20) p17[i] = p17[i-1] * 17, p19[i] = p19[i-1] * 19, p2[i] = p2[i-1] * 2; 
	rep(i, 0, N * 2) aa[i] = __builtin_parity(i);
	rep(i, 0, 16) e.a[i] += p2[i], e.b[i] += p2[i];
	cin >> T;
	rep(cas, 0, T) {
		int n, op;
		uint last;
		cin >> n; 
		last = 0; l1 = l2 = 1; r1 = r2 = 0;
		rep(i, 1, n+1) {
			cin >> op >> seed; seed ^= last;
			if (op == 2) {
				if (l2 > r2) {
					l2 = l1; r2 = r1; l1 = r1 + 1;
					suf[r2] = a[r2];
					per(i, l2, r2) suf[i] = suf[i+1] * a[i];
				}
				l2++;
				if (l2 > r2) {
					if (l1 > r1) cout << (last = 0) << endl;
					else cout << (last = pre[r1].get()) << endl;
				} else {
					cout << (last = ((l1 <= r1 ? pre[r1] : e) * suf[l2]).get()) << endl;
				}
 			} else {
				a[++r1] = get();
				pre[r1] = l1 == r1 ? a[r1] : a[r1] * pre[r1-1];
				cout << (last = (pre[r1] * (l2 <= r2 ? suf[l2] : e)).get()) << endl;
			}
		}
	}
	return 0;
}


