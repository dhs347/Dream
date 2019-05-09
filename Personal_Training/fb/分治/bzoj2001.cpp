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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5e4 + 7;

int f[N], pos[N], id[N], w[N], m[30], n, q;
ll ans[N];
struct edge{
	int u, v, w, id;
	bool operator < (const edge & c) const { return w < c.w;} 
} a[30][N], b[N], c[N];

int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

void init(int m) {
	rep(i, 1, m+1) {
		int u = b[i].u, v = b[i].v;
		f[u] = u; f[v] = v;
	}
} 

void reduction(int &m, int l, int r) {
	rep(i, l, r+1) b[pos[id[i]]].w = pw(30);
	sort(b + 1, b + m + 1); init(m); int mm = 0;
	rep(i, 1, m+1) {
		int u = get(b[i].u), v = get(b[i].v);
		if (u != v) {
			f[u] = v;
			b[++mm] = b[i];
		}else if (b[i].w == pw(30)) b[++mm] = b[i];
	}
	m = mm;
	rep(i, 1, m+1) pos[b[i].id] = i;
}

void contraction(int &m, int l, int r, ll &sum) {
	rep(i, l, r+1) b[pos[id[i]]].w = -pw(30);
	sort(b + 1, b + m + 1); init(m); int mm = 0;
	rep(i, 1, m+1) {
		int u = get(b[i].u), v = get(b[i].v);
		if (u != v) f[u] = v, c[++mm] = b[i];
	}
	init(m);
	rep(i, 1, mm+1) {
		int u = get(c[i].u), v = get(c[i].v);
		if (c[i].w != -pw(30) && u != v) f[u] = v, sum += c[i].w;
	}
	mm = 0;
	rep(i, 1, m+1) {
		int u = get(b[i].u), v = get(b[i].v);
		if (b[i].w == -pw(30) || u != v) b[++mm] = b[i], b[mm].u = u, b[mm].v = v;
	}
	m = mm;
}

void solve(int l, int r, int now, ll sum) {
	//if (l == r) a[0][id[l]].w = w[l];
	rep(i, 1, m[now]+1) a[now][i].w = a[0][a[now][i].id].w, b[i] = a[now][i], pos[b[i].id] = i;
	if (l + 2 <= r) {
		rep(j, l, r+1) {
			rep(i, 1, m[now]+1) pos[b[i].id] = i;
			init(m[now]); ans[j] = sum;
			b[pos[id[j]]].w = w[j];
			a[0][id[j]].w = w[j];
			sort(b+1, b+m[now]+1);
			rep(i, 1, m[now]+1) {
				int u = get(b[i].u), v = get(b[i].v);
				if (u != v) f[u] = v, ans[j] += b[i].w;
			}
		}
		return;
	}
	m[now+1] = m[now];
	reduction(m[now+1], l, r);
	contraction(m[now+1], l, r, sum);
	rep(i, 1, m[now+1]+1) a[now+1][i] = b[i]; 
	int mid = (l + r) >> 1;
	solve(l, mid, now+1, sum);
	solve(mid+1, r, now+1, sum); 
	return;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m[0] >> q;
	rep(i, 1, m[0]+1) cin >> a[0][i].u >> a[0][i].v >> a[0][i].w, a[0][i].id = i;
	rep(i, 1, q+1) cin >> id[i] >> w[i];
	solve(1, q, 0, 0);
	rep(i, 1, q+1) cout << ans[i] << endl;
	return 0;
}


