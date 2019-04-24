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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 55;
int n, m, a[N];
db f[N][N];

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) cin >> a[i];
	f[1][0] = 1;
	rep(i, 2, n+1) rep(j, 0, i) {
		rep(k, 1, m+1) {
			int t = (a[k] - 1)% i, p;
			if (t != j) {
				if (t < j) p = j - t - 1;
				else {
					p = i - t - 1;
					p += j;
				}
				f[i][j] += f[i-1][p] / m;
			}
		}
	} 
	rep(i, 0, n) cout << f[n][i] * 100 << "% ";
	return 0;
}


