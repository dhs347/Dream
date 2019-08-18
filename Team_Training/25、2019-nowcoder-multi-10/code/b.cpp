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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1000;
ll a[N], T, n, k;
string s[3];
string get(ll n, ll k, ll len) {
	string r;
	//de(n), de(k), de(len);
	if (n == 1 || n == 2) {
		rep(i, k, min(k + len - 1, a[n])+1) {
			//de(i);
			r += s[n][i - 1]; 
		}
		return r;
	}
	if (k <= a[n-2]) {
		r += get(n - 2, k, min(len, a[n-2] - k + 1));
		if (k + len - 1 > a[n - 2]) 
		r += get(n - 1, 1, k + len - 1 - a[n - 2]);
	}else {
		r += get(n - 1, k - a[n - 2], len);
	}
	return r;
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	cin >> T;
	a[1] = 6; 
	a[2] = 7;
	s[1] = "COFFEE";
	s[2] = "CHICKEN";

	rep(i, 3, 61) a[i] = a[i-2] + a[i-1];
	//return 0;
	rep(cas, 0, T) {
		cin >> n >> k;
		n = min(n, 60ll);
		cout << get(n, k, 10) << endl;
	}
	return 0;
}
