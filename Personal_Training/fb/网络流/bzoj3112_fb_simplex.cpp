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
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r=1;
	for(; b; b>>=1,a=mul(a,a)) {
		if(b&1)r=mul(r,a);
	}
	return r;
}
//----


const db EPS = 1e-8;
const db DINF = 1e9;
const int MAXN = 1005;
struct Simplex {
	int n, m, B[MAXN * 10], N[MAXN * 10];
	db v, ans[MAXN * 10], b[MAXN * 10], c[MAXN * 10], A[MAXN][MAXN * 10];
	/* n - variables, m - equations
	*maxf(x)=cx
	*s.t.Ax<=b,x>=0 */
	void init(int _n, int _m) {
		n = _n, m = _m, v = 0;
		rep(i, 1, n + 1) N[i] = i;
		rep(i, 1, m + 1) B[i] = i + n;
	}
	inline int sgn(db x) {
		return (x > EPS) - (x < -EPS);
	}
	void pivot(int l, int e) {
		db tmp = A[l][e];
		b[l] /= tmp, A[l][e] = 1 / tmp;
		rep(i, 1, n + 1) if (i != e) A[l][i] /= tmp;
		rep(i, 1, m + 1) if (i != l) {
			b[i] -= A[i][e] * b[l];
			rep(j, 1, n + 1) A[i][j] -= (j!=e) * A[i][e] * A[l][j];
			A[i][e] = - A[i][e] / tmp;
		}
		rep(i, 1, n + 1) c[i] -= (i!=e) * c[e] * A[l][i];
		v += b[l] * c[e];
		c[e] *= -A[l][e];
		swap(B[l], N[e]);
	}
	db run() {
		while (1) {
			int r, l, e = -1;
			db delt = -DINF;
			//int cc = 0;
			//rep(i, 1, n+1) {if (c[i] > EPS) break;cc++;}
			//if (cc == n) break;
			rep(j, 1, n + 1) if (sgn(c[j]) > 0) {
				db tmp = DINF;
				rep(i, 1, m + 1) if (sgn(A[i][j]) > 0 && b[i] / A[i][j] < tmp)
					r = i, tmp = b[i] / A[i][j];
				if (delt < tmp * c[j]) l = r, e = j, delt = tmp * c[j];
			}
			if (e == -1) break;
			pivot(l, e);
		}
		rep(i, 1, n + 1) rep(j, 1, m + 1)
		if (B[j] == i) {
			ans[i] = (j <= m ? b[j] : 0);
			break;
		}
		return v;
	}
} sp;

int n, m, l, r;

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	n = 1000; m = 10000;
	sp.init(m, n);
	rep(i, 1, n+1) sp.b[i] = i;//
	//cin >> sp.b[i];
	rep(i, 1, m+1) {
		l = i % n + 1; r = (i + i) % n + 1;
		if (l > r) swap(l, r);
		sp.c[i] = i; 
		//cin >> l >> r >> sp.c[i];
		rep(j, l, r+1) sp.A[j][i] = 1;
	}
	//cout << (ll)(sp.run() + 0.4);
	printf("%.0lf", sp.run());
	return 0;
}
