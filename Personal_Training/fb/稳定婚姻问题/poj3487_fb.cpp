#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
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
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 55;
int now, id[200], T, n, c1, c2, cnt;
char cc[200];

string s;

bool check(int x) { return 'a' <= x && x <= 'z'; }

int mat1[N], mat[N], pos[N]; 
vi g1[N], g2[N];
queue<int> q;

void match(int n, vi *g, vi *rank) { 
	rep(i, 1, n+1) q.push(i), pos[i] = 0, mat[i] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		int &p = pos[u], v = g[u][p];
		if (!mat[v]) mat[v] = u;
		else if (rank[v][mat[v]] > rank[v][u]) {
			q.push(mat[v]);
			mat[v] = u;
		}else q.push(u);
		p++;
	}
	rep(i, 1, n+1) mat1[mat[i]] = i;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		memset(id, 0, sizeof(id));
		c1 = c2 = 0;
		rep(i, 1, n+1) g1[i].clear(), g2[i].resize(n+1);
		rep(i, 0, 2 * n) {
			cin >> s;
			if (check(s[0])) id[s[0]] = ++c1; else id[s[0]] = ++ c2, cc[c2] = s[0];
 		} 
 		rep(i, 0, 2 * n) {
			cin >> s;
			if (check(s[0])) {
				rep(j, 2, sz(s)) g1[id[s[0]]].pb(id[s[j]]);
			} else rep(j, 2, sz(s)) g2[id[s[0]]][id[s[j]]] = j - 1;
		}
		match(n, g1, g2);
		rep(i, 'a', 'z'+1) if (id[i]) cout << (char) i << " " << cc[mat1[id[i]]] << endl; 
		cout << endl;
	}
	return 0;
}


