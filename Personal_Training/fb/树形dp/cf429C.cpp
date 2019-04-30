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

const int N = 30;
bool vis[N];
int n, x;
vi t, v;


bool check(vi v, int x) {
	if (x < 0) return 0;
	rep(i, 0, n+1) vis[i] = 0;
	vis[0] = 1;
	for (auto t : v)  per(i, 0, n+1) if (i - t >= 0) vis[i] |= vis[i - t];else break;
	return vis[x]; 
}

vi solve(vi v, int x) {
	int y = x - 1, cnt = 0; vi res;
	per(i, 0, sz(v)) {
		vi t;
		rep(j, 0, i) t.pb(v[j]);
		if ((cnt > 0 || y != v[i]) && check(t, y - v[i])) y -= v[i], cnt++;
		else res.pb(v[i]);
	}
	if (y != 0) {
		cout << "NO";
		exit(0);
	}
	res.pb(x);
	return res;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> x;
		if (x == 1) v.pb(1);
		else t.pb(x);
	} 
	sort(all(t));
	for (auto x : t) {
		sort(all(v));
		//for (auto y : v) dd(y);
		//cout<< endl;
		v = solve(v, x);
	}
	if (sz(v) == 1) cout << "YES" << endl;else cout << "NO";
	return 0;
}


