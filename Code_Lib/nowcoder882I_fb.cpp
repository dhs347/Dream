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

const int N = 55;

int w[N], b[N][N], sum[N][N], a[N][N], dp[N][N][N][N], dp2[N][N][N][N], pre[N][N], suf[N][N], n, m, ans;
int pre1[N][N][N], pre2[N][N][N], suf1[N][N][N], suf2[N][N][N]; 
int dp3[N][N][N][N], dp4[N][N][N][N];

int solve(int n, int m) {
	int res = 0;
	rep(i, 1, n+1) {
		rep(j, 1, m+1) w[j] = 0;
		rep(j, i, n+1) {
			rep(k, 1, m+1) w[k] += b[j][k];
			int t = 0;
			rep(k, 1, m+1) t = max(0, t + w[k]), res = max(res, t); 
		} 
	}
	return res;
}

int get(int l1, int r1, int l2, int r2) {
	return sum[l2][r2] - sum[l2][r1-1] - sum[l1-1][r2] + sum[l1-1][r1-1];
}

int solve2(int n, int m) {
	memset(pre, -0x3f, sizeof(pre));
	memset(suf, -0x3f, sizeof(suf));
	rep(i, 1, n+1) rep(j, 1, m+1) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + b[i][j];
	rep(i, 1, n+1) rep(j, 1, m+1) {
		rep(k, 1, i+1) rep(l, 1, j+1) {
			int t = get(k, l, i, j);
			pre[k][l] = max(t, max(pre[k-1][l], pre[k][l-1]));
			dp[i][j][k][l] = pre[k][l] - t;
		}
	}
	per(i, 1, n+1) per(j, 1, m+1) {
		per(k, i, n+1) per(l, j, m+1) {
			int t = get(i, j, k, l);
			suf[k][l] = max(t, max(suf[k+1][l], suf[k][l+1]));
			dp2[i][j][k][l] = suf[k][l] - t;
		}
	}
	int ans = 0, l1, l2, r1, r2;
	rep(i, 1, n+1) rep(j, 1, m+1) rep(k, 1, i+1) rep(l, 1, j+1) {
 		ans = max(ans, dp[i][j][k][l] + dp2[k][l][i][j]);
	}
	return ans;
}

int solve3(int n, int m) {
	int res = 0;
	memset(dp, 0x3f, sizeof(dp));
	memset(dp2, 0x3f, sizeof(dp2));
	rep(i, 1, n+1) rep(j, 1, m+1) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + b[i][j];
	rep(i, 1, n+1) rep(j, 1, m+1) per(k, 1, i+1) per(l, 1, j+1) {
		dp2[k][l][i][j] = min(get(k, l, i, j), min(dp2[k+1][l][i][j], dp2[k][l+1][i][j]));
	}
	rep(i, 1, n+1) rep(j, 1, m+1) rep(k, i, n+1) rep(l, j, m+1) {
		dp[i][j][k][l] = min(dp2[i][j][k][l], min(dp[i][j][k-1][l], dp[i][j][k][l-1]));
		res = max(res, get(i, j, k, l) - dp[i][j][k][l]);
	}
	return res;
}

int solve4(int n, int m) {
	int res = 0;
	memset(dp, -0x3f, sizeof(dp));
	memset(dp2, -0x3f, sizeof(dp2));
	memset(dp3, -0x3f, sizeof(dp3));
	memset(dp4, -0x3f, sizeof(dp4));
	rep(i, 1, n+1) {
		rep(j, 1, m+1) w[j] = 0;
		rep(j, i, n+1) {
			rep(k, 1, m+1) w[k] += b[j][k];
			int t = 0; rep(k, 1, m+1) t = max(0, t + w[k]), pre1[i][j][k] = t; 
			t = 0; per(k, 1, m+1) t = max(0, t + w[k]), suf1[i][j][k] = t;
			
			rep(k, 1, m+1) {
				int t = 0; rep(l, k, m+1) { t += w[l];dp[i][j][k][l] = max(dp[i][j][k][l-1], t);} 
				t = 0; per(l, 1, k+1) {t += w[l]; dp2[i][j][k][l] = max(dp2[i][j][k][l+1], t);}
			}
		} 
	}
	rep(i, 1, m+1) {
		rep(j, 1, n+1) w[j] = 0;
		rep(j, i, m+1) {
			rep(k, 1, n+1) w[k] += b[k][j];
			int t = 0; rep(k, 1, n+1) t = max(0, t + w[k]), pre2[i][j][k] = t; 
			t = 0; per(k, 1, n+1) t = max(0, t + w[k]), suf2[i][j][k] = t;
			
			rep(k, 1, n+1) {
				int t = 0; rep(l, k, n+1) { t += w[l];dp3[i][j][k][l] = max(dp3[i][j][k][l-1], t);} 
				t = 0; per(l, 1, k+1) {t += w[l]; dp4[i][j][k][l] = max(dp4[i][j][k][l+1], t);}
			}
		} 
	}

	rep(i, 1, n+1) rep(j, 1, m+1) rep(k, i, n+1) rep(l, j, m+1) {
		res = max(res, pre1[i][k][j-1] + suf1[i][k][l+1] + pre2[j][l][i-1] + suf2[j][l][k+1]);
		res = max(res, pre1[i][k][j-1] + suf1[i][k][l+1] + suf2[j][l][k+1] + dp3[j][l][i][k]);
		res = max(res, pre1[i][k][j-1] + suf1[i][k][l+1] + pre2[j][l][i-1] + dp4[j][l][k][i]);
		res = max(res, pre2[j][l][i-1] + suf2[j][l][k+1] + suf1[i][k][l+1] + dp[i][k][j][l]);
		res = max(res, pre2[j][l][i-1] + suf2[j][l][k+1] + pre1[i][k][j-1] + dp2[i][k][l][j]);
	}
	return res;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) rep(j, 1, m+1) cin >> a[i][j]; 
	rep(i, 1, n+1) {
		rep(j, 1, i+1) rep(k, 1, m+1) b[j][k] = a[j][k];
		int t = solve(i, m);
		rep(j, i+1, n+1) rep(k, 1, m+1) b[j - i][k] = a[j][k];
		ans = max(ans, t + solve(n - i, m));
	}
	rep(i, 1, m+1) {
		rep(j, 1, n+1) rep(k, 1, i+1) b[j][k] = a[j][k];
		int t = solve(n, i);
		rep(j, 1, n+1) rep(k, i+1, m+1) b[j][k - i] = a[j][k];
		ans = max(ans, t + solve(n, m - i));
	}
	rep(i, 1, n+1) rep(j, 1, m+1) b[i][j] = a[i][j]; 
	ans = max(ans, solve2(n, m));
	rep(i, 1, m+1) rep(j, 1, n+1) b[i][j] = a[n - j + 1][i];
	ans = max(ans, solve2(m, n));
	rep(i, 1, n+1) rep(j, 1, m+1) b[i][j] = a[i][j]; 
	ans = max(ans, solve3(n, m));
	ans = max(ans, solve4(n, m));
	cout << ans << endl;
	return 0;
}


