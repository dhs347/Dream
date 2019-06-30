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
typedef int db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
//----

const db EPS = 1e-8, DINF = 1e9;
struct Simplex {
	static const int M = 10050;
	int n, m, B[M], N[M];
	db v, ans[M], b[M], c[M], A[M / 10][M]; // 全幺模矩阵可以改整数 
	/* n - variables, m - equations
	*maxf(x)=cx
	*s.t.Ax<=b,x>=0 */
	void init(int _n, int _m) {
		n = _n, m = _m, v = 0;
		rep(i, 1, n + 1) N[i] = i;
		rep(i, 1, m + 1) B[i] = i + n;
	}
	inline int sgn(db x) { return (x > EPS) - (x < -EPS); }
	void pivot(int l, int e) {
		db tmp = A[l][e];
		b[l] /= tmp, A[l][e] = 1 / tmp;
		rep(i, 1, n + 1) if (i != e) A[l][i] /= tmp;
		rep(i, 1, m + 1) if (i != l && sgn(A[i][e])) {
			b[i] -= A[i][e] * b[l];
			rep(j, 1, n + 1) A[i][j] -= (j!=e) * A[i][e] * A[l][j];
			A[i][e] = - A[i][e] / tmp;
		}
		rep(i, 1, n + 1) c[i] -= (i!=e) * c[e] * A[l][i];
		v += b[l] * c[e]; c[e] *= -A[l][e]; swap(B[l], N[e]);
	}
	db run() {
		rep(i, 1, n+1) ans[i] = 0; 
		while (1) {
			int r, l, e = -1;
			db delt = -DINF;
			rep(j, 1, n + 1) if (sgn(c[j]) > 0) { // 找非基变量 
				db tmp = DINF;
				rep(i, 1, m + 1) if (sgn(A[i][j]) > 0 && b[i] / A[i][j] < tmp) // 找基变量 
					r = i, tmp = b[i] / A[i][j];
				if (tmp == DINF) return DINF; // 无界 
				if (delt < tmp * c[j]) l = r, e = j, delt = tmp * c[j]; 
				break; 
				//贪心取最大 如果矩阵为全幺模或0很多可以加上break 因为转轴代价可能较小 
			}
			if (e == -1) break; // 找到最优解 
			pivot(l, e); 
		}
		rep(i, 1, m+1) if (B[i] <= n) ans[B[i]] = b[i];
		return v;
	}
} sp;

int n, m, l, r, d[100000];

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	sp.init(m, n);
	rep(i, 1, n+1) cin >> sp.b[i];
	rep(i, 1, m+1) {
		cin >> l >> r >> sp.c[i], d[i] = sp.c[i];
		rep(j, l, r+1) sp.A[j][i] = 1;
	}
	//cout << (ll)(sp.run() + 0.4);
	int ans;
	printf("%d\n", ans = sp.run());
	return 0;
}
