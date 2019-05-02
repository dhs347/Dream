#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9 + 7;
const int N = 5005;
int n, w, f[N][N], cnt[N];
string s;

int add(int a, int b) {
	return (a + b) % P;
} 

int mul(int a, int b) {
	return 1ll * a * b % P;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	n = sz(s);
	w = 1;
	per(i, 0, n) cnt[i] = cnt[i+1] + (s[i] == '<');
	per(i, 0, n) {
		f[i][i] = w;
		w = 0;
		rep(j, i+1, n) {
			if (s[i] == '<') f[i][j] = 0;
			else f[i][j] = mul(f[i+1][j], cnt[i] + 1 - (s[j] == '<'));
			if (s[j] == '<') w = add(w, f[i][j]);
		}
		if (s[i] == '<') w = add(w, f[i][i]);
	}
	rep(i, 0, n) {
		rep(j, i, n) {
			dd(f[i][j]);
		}
		cout << endl;
	}
	rep(i, 0, n) cout << f[0][i] << " \n"[i == n-1];
	return 0;
}
