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
const int P = 1e9;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5e5 + 7;
int sma[N], smi[N], hma[N], hmi[N], f[N], g[N], a[N], ans, n;

int calc(int l, int r) { 
	return 1ll * (l + r) * (r - l + 1) / 2 % P;
}

void solve(int l, int r) {
	if (l == r) {ans = add(ans, mul(a[l], a[l])); return;}
	int mid = l + r >> 1;
	int j = mid+1, k = mid+1, ma = a[mid+1], mi = ma;
	sma[mid] = smi[mid] = hma[mid] = hmi[mid] = f[mid] = g[mid] = 0;
	rep(i, mid+1, r+1) {
		ma = max(ma, a[i]); mi = min(mi, a[i]);
		sma[i] = add(sma[i-1], ma);
		smi[i] = add(smi[i-1], mi);
		hma[i] = add(hma[i-1], mul(ma, i));
		hmi[i] = add(hmi[i-1], mul(mi, i));
		f[i] = add(f[i-1], mul(ma, mi));
		g[i] = add(g[i-1], mul(ma, mul(mi, i)));
	}
	ma = a[mid]; mi = ma;
	per(i, l, mid+1) {
		ma = max(ma, a[i]); mi = min(mi, a[i]);
		while (j <= r && a[j] <= ma) j++;
		while (k <= r && a[k] >= mi) k++;
		int d = calc(mid + 1 - i + 1, min(j, k) - 1 - i + 1);
		ans = add(ans, mul(mul(ma, mi), d));
		if (j < k) ans = add(ans, mul(add(add(hma[k-1], -hma[j-1]),  -mul(i - 1, add(sma[k-1], -sma[j-1]))), mi));	
		if (k < j) ans = add(ans, mul(add(add(hmi[j-1], -hmi[k-1]),  -mul(i - 1, add(smi[j-1], -smi[k-1]))), ma));
		ans = add(ans, add(add(g[r], -g[max(j, k)-1]),  -mul(i - 1, add(f[r], -f[max(j, k)-1]))));	
	}
	solve(l, mid);
	solve(mid+1, r);
	return;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i];
	solve(1, n); 
	cout << ans << endl;
	return 0;
}


