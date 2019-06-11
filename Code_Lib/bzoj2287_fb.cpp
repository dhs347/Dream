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
const int P = 10;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e3 + 7;
ll g[N], f[20][N], a[N];
int n, m;

void solve(int l, int r, int now) {
	if (l == r) {
		rep(i, 1, m+1) cout << f[now][i];
		cout << endl;
		return;
	}
	int mid = l + r >> 1;
	rep(i, 0, m+1) f[now+1][i] = f[now][i];
	rep(i, mid+1, r+1) per(j, a[i], m+1) f[now+1][j] = add(f[now+1][j], f[now+1][j - a[i]]); 
	solve(l, mid, now+1);
	rep(i, 0, m+1) f[now+1][i] = f[now][i];
	rep(i, l, mid+1) per(j, a[i], m+1) f[now+1][j] = add(f[now+1][j], f[now+1][j - a[i]]); 
	solve(mid+1, r, now+1);
	return;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) cin >> a[i];
	/*f[0] = 1;
	rep(i, 1, n+1) per(j, a[i], m+1) f[j] = add(f[j], f[j - a[i]]);
	rep(i, 1, n+1) {
		rep(j, 0, m+1) g[j] = f[j];
		rep(j, a[i], m+1) g[j] = add(g[j], -g[j-a[i]]);
		rep(j, 1, m+1) cout << g[j];
		cout << endl;
	}*/
	f[0][0] = 1;
	solve(1, n, 0);
	return 0;
}


