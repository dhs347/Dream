// n点m边强连通子图计数
//首先要会n点m边DAG计数，然后把枚举出度为零的点集容斥改为枚举缩点后出度为零的点集容斥
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
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1 << 15;
int n, cnt[N], S, g[N], f[N], u, v, a[N], m, p[300];

int get(int x) {
	int res = 0;
	while (x) {
		res++;
		x = (x - 1) & x;
	}
	return res;
}

int cal(int x, int y) {
	int res = 0, t;
	while (x) {
		t = x & (-x);
		res += cnt[a[t] & y];
		x ^= t;
	} 
	return res;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v;
		a[pw(u-1)] |= pw(v-1);
	}
	S = pw(n) - 1;
	rep(i, 1, S+1) cnt[i] = get(i);
	p[0] = 1;
	rep(i, 1, m+1) p[i] = mul(p[i-1], 2); 
	rep(i, 1, S+1) {
		u = i & (-i);
		for (int x = (i - 1) & i; x > 0; x = (x - 1) & i) {
			if (x & u) g[i] = sub(g[i], mul(f[x], g[i ^ x]));
		}
		f[i] = p[cal(i, i)];
		for (int x = i; x > 0; x = (x - 1) & i) {
			f[i] = sub(f[i], mul(g[x], p[cal(i ^ x, i)]));
		}
		g[i] = add(g[i], f[i]);
	}
	cout << f[S];
	return 0;
}


