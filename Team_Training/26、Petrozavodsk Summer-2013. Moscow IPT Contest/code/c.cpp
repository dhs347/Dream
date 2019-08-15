#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
typedef vector<pii> vii;

ll t1, t2,  Q, P, V, U, p, u, a[10];
unordered_map<int, int> M;

vii get(int n) {
	vii tmp;
	for (int i = 2; i * i <= n; i ++) if (n % i == 0) {
		int cnt = 0;
		while (n % i == 0) {
			cnt++; n /= i;
		}
		tmp.pb(mp(i, cnt));
	}
	if (n > 1) tmp.pb(mp(n, 1));
	return tmp;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> P >> Q >> U >> V;
	ll x = Q * Q - P * P;
	ll y = V * V - U * U;
	if (x < 0 || y < 0) {
		cout << -1 << endl;
		return 0;
	}
	vii tmp1 = get(Q + P), tmp2 = get(Q - P);
	//p = solve(P, Q);
	p = 1; u = 1;
	for (auto u : tmp1) M[u.fi] += u.se;
	for (auto u : tmp2) M[u.fi] += u.se;
	t1 = 1;
	for (auto u : M) {
		rep(i, 0, u.se / 2) p = p * u.fi;
		if (u.se & 1) t1 = t1 * u.fi;
	}
	//for (auto u : M) dd(u.fi), de(u.se);
	M.clear();
	tmp1 = get(V + U), tmp2 = get(V - U);
	for (auto u : tmp1) M[u.fi] += u.se;
	for (auto u : tmp2) M[u.fi] += u.se;
	t2 = 1;
	for (auto v : M) {	
		rep(i, 0, v.se / 2) u = u * v.fi;
		if (v.se & 1) t2 = t2 * v.fi;
	}
	M.clear();
	if (t1 != t2) {
		cout << -1 << endl;
		return 0;
	}

	//dd(p), dd(u);
	a[0] = u * P + p * U;
	a[1] = Q * u;
	a[2] = p * V;
	sort(a, a+3);
	bool ok1 = 1, ok2 = 1;
	rep(i, 0, 3) {
		ok1 &= a[i] > 0;
		ok2 &= a[i] < 0;
	}
	if (!ok1 && !ok2) {
			cout << -1 << endl;
			return 0;
		}
	rep(i, 0, 3) a[i] = abs(a[i]); 
	ll d = __gcd(a[0], a[1]);
	d = __gcd(d, a[2]);
	rep(i, 0, 3) a[i] /= d;
	if (a[0] + a[1] > a[2]) {
		rep(i, 0, 3) cout << a[i] << " \n"[i == 2];
		return 0;
	}else {
		cout << -1;
		return 0;
	}
	return 0;
}
