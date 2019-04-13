// 暴力记忆化转移 
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
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

int T, n, a[20], w[200], b[20], m;
db ans1, ans2;

map<string, db> M; 
db dfs1(string s) {
	if (M.count(s)) return M[s];
	db res = n * n, w;
	int tim = 0, cnt = n * n;
	rep(i, 0, n)
		rep(j, 0, n) if (s[min(i, j)] <= s[max(i, j)]) tim++;
	w = (cnt - tim);
	rep(i, 0, n) rep(j, 0, n) if (s[min(i, j)] > s[max(i, j)]) {
		swap(s[min(i, j)], s[max(i, j)]);
		res += dfs1(s);
		swap(s[min(i, j)], s[max(i, j)]);
	}
	return M[s] = res / w;
}

db dfs2(string s) {
	if (M.count(s)) return M[s];
	db res = n - 1, w;
	int tim = 0, cnt = n - 1;
	rep(i, 0, n-1) if (s[i] <= s[i+1]) tim++;
	w = (cnt - tim);
	rep(i, 0, n-1) if (s[i] > s[i+1]) {
		swap(s[i], s[i+1]);
		res += dfs2(s);
		swap(s[i], s[i+1]);
	}
	return M[s] = res / w;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cin >> T;
	rep(cas, 0, T) {
		string s, t;
		cin >> n; 
		rep(i, 0, n) cin >> a[i], b[i] = a[i];
		sort(b, b+n);
		m = unique(b, b+n) - b;
		rep(i, 0, m) w[b[i]] = i;
		rep(i, 0, n) a[i] = w[a[i]], s += char(a[i] + 1);
		sort(a, a+n);
		rep(i, 0, n) t += char(a[i] + 1);
		M.clear();
		M[t] = 0; 
		ans1 = dfs1(s);
		M.clear();
		M[t] = 0;
		ans2 = dfs2(s);
		cout << "Monty " << ans1 << " Carlos " << ans2 << endl;
	}
	return 0;
}

