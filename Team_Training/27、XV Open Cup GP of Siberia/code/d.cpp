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
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

//const int P = 1e9 + 7;
/*
int inv(int x) {
	return x == 1 ? x : P - ll(P / x) * inv(P % x) %P;
}*/

const int N = 1 << 21;
ll a[8][N], b[N];
int S, u, v, n, m, k;
string s;

void fwt(ll *a, int len, int o) {
//	int inv2 = inv(2);
	for(int k = 0; 1 << k < len; ++k) rep(i, 0, len) if(~i >> k & 1) {
		int j = i ^ (1 << k);
		ll x, y;
		x = a[i], y = a[i] + a[j];
		if(o == -1) y = a[j] - a[i];
		a[i] = x, a[j] = y;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	S = pw(n) - 1;
	rep(i, 0, m) {
		cin >> s;
		rep(j, 0, S+1) a[i][j] = s[j] - '0';
	}
	//rep(i, 0, m) rep(j, 0, S+1) cout << a[i][j] << " \n"[j == S];
	rep(i, 0, m) {
		fwt(a[i], S+1, 1);
	//	fwt(a[i], S+1, -1);	
	}
	rep(i, 0, k) {
		cin >> u >> v;
		rep(j, 0, S+1) b[j] = a[u][j] * a[v][j];
		fwt(b, S+1, -1);
		//rep(j, 0, S+1) cout << b[j] << " \n"[j == S];
		rep(j, 0, S+1) {
			cout << (b[j] ? '1' : '0');
		}
		cout << endl;
	}
	return 0;
}
