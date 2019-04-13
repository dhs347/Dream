// 概率的形式可以用多项式表示，以及多项式除两项多项式可以O(n)做到 
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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 205;
int n, p[N][N], u, v, op, x, a[N], b[N], q, w, k, ans, c[N], d[N], Inv[N];

int inv(int x) {
	return kpow(x, P - 2);
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i], p[i][a[i]] = 1;
	cin >> q;
	Inv[1] = 1;
	rep(i, 2, n+1) Inv[i] = mul(P - P / i, Inv[P % i]); 
	rep(cas, 0, q) {
		cin >> op;
		if (op == 0) {
			cin >> x >> u >> v;
			w = mul(u, inv(v));
			rep(i, 0, a[x]+1) {
				if (i != 0) p[x][i] = add(mul(p[x][i], 1 - w + P), mul(p[x][i+1], w));
				else p[x][i] = add(p[x][i], mul(p[x][i+1], w));
			}
		}else {
			cin >> k;
			rep(i, 1, k+1) {
				cin >> x;
				b[i] = (1 - p[x][0] + P) % P; 
			}
			rep(i, 1, k+1) c[i] = 0;
			c[0] = 1;
			rep(i, 1, k+1) {
				per(j, 0, i+1) {
					c[j+1] = add(c[j+1], mul(c[j], b[i]));
					c[j] = mul(c[j], 1 - b[i] + P);
				}
			}
			rep(i, 1, k+1) {
				if (b[i] != 1) {
					int tmp = inv(1 - b[i] + P);
					d[0] = mul(c[0], tmp);
					rep(j, 1, k+1) {
						d[j] = sub(c[j], mul(d[j-1], b[i]));
						d[j] = mul(d[j], tmp);
					}
				}else rep(j, 0, k+1) d[j] = c[j+1];
				ans = 0;
				rep(j, 0, k) ans = add(ans, mul(mul(Inv[j+1], d[j]), b[i])); 
				cout << ans << " ";
			}
			cout << endl;
		}
	}
	rep(i, 1, n+1) {
		ans = 0;
		rep(j, 1, a[i]+1) ans = add(ans, mul(j, p[i][j])); 
		cout << ans << " ";
	}
	return 0;
}

