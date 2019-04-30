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

const int N = 1e6 + 7;
int a[N], b[N], tr[N * 4], tip[N * 4], lft[N], rht[N], tim, n, k;
vi g[N];
void dfs(int u) {
	lft[u] = ++tim;
	for (auto v : g[u]) dfs(v);
	rht[u] = tim;
}

#define ls (now << 1)
#define rs (ls | 1)

void change(int l, int r, int now, int L, int R, int w) {
	if (L <= l && R >= r) {
		tip[now] += w;
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) change(l, mid, ls, L, R, w);
	if (R > mid) change(mid + 1, r, rs, L, R, w);
	tr[now] = max(tr[ls] + tip[ls], tr[rs] + tip[rs]);
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	rep(i, 1, n+1) cin >> a[i];
	per(i, 1, n+1) {
		for (b[i] = i + 1; b[i] <= n && a[b[i]] <= a[i]; b[i] = b[b[i]]);
		g[b[i]].pb(i);
	}
	dfs(n+1);
	rep(i, 1, k+1) change(1, tim, 1, lft[i], rht[i], 1);
	cout << tip[1] + tr[1] << " ";
	rep(i, k+1, n+1) {
		change(1, tim, 1, lft[i], rht[i], 1);
		change(1, tim, 1, lft[i-k], lft[i-k], -pw(30));
		cout << tr[1] + tip[1] << " ";
	} 
	return 0;
}


