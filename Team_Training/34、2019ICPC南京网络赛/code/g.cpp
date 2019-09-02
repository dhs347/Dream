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
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef __int128 ll;

const int N = 2020;
const int inf = -400000;
int x[8];

/*
ll calc(ll a, ll b, ll c, ll d) { // xia jie
	d -= 1 - a;
	d -= 1 - b;
	d -= 1 - c;
	d--;
	if(d < 1) return 0;
	return d * (d - 1) / 2;
}*/

ll f(ll d) {
	if(d < 0) return 0;
	return (d + 4) * (d + 3) * (d + 2) * (d + 1) / 24;
}

ll W(ll l[], ll r[], ll d) {
	int S = pw(5); ll res = 0;
	rep(i, 0, S) { 
		int op = 1; ll t = d;
		rep(j, 0, 5) if (pw(j) & i) t -= r[j] - l[j] + 1, op *= -1; 
		res += f(t) * op;
	}
	return res;
//	return f(d) 
//	- f(d - a - 1) - f(d - b - 1) - f(d - c - 1) 
//	+ f(d - a - b - 2) + f(d - a - c - 2) 
//	+ f(d - b - c - 2) - f(d - a -b - c - 3);
}
// a + b + c = d
ll gao(ll l[], ll r[], ll d) {
	return W(l, r, d - l[0] - l[1] - l[2] - l[3] - l[4]);
}
ll doi(ll l[], ll r[]) {
	ll res = gao(l, r, 0);
	return res;
}
ll work() {
	ll res = 0;
	ll l1[] = {x[0], x[2], x[4], -x[7], inf}, r1[] = {x[1], x[3], x[5], -x[6], -1};
	res += doi(l1, r1);
	
	swap(l1[0], r1[0]); l1[0] *= -1, r1[0] *= -1;
	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;
	//rep(i, 0, 5) de((int)l1[i]), de((int)r1[i]);
	res += doi(l1, r1);
	swap(l1[0], r1[0]); l1[0] *= -1, r1[0] *= -1;
	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;
	
	swap(l1[2], r1[2]); l1[2] *= -1, r1[2] *= -1;
	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;
	res += doi(l1, r1);
	swap(l1[2], r1[2]); l1[2] *= -1, r1[2] *= -1;
	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;
	

	swap(l1[1], r1[1]); l1[1] *= -1, r1[1] *= -1;
	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;
	res += doi(l1, r1);
//	swap(l1[0], r1[0]); l1[1] *= -1, r1[1] *= -1;
//	swap(l1[3], r1[3]); l1[3] *= -1, r1[3] *= -1;

	return res;
}

void solve() {
	rep(i, 0, 8) cin >> x[i];
	rep(i, 0, 4) if (x[i*2] > x[i * 2 + 1]) {
		cout << 0 << endl;
		return;
	}
	ll ans = work() - 3ll * (x[1] - x[0] + 1) * (x[3] - x[2] + 1) * (x[5] - x[4] + 1) * (x[7] - x[6] + 1);
	long long an = ans;
	cout << an << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; while(T--) solve();
	return 0;
}
