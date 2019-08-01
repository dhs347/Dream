#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1e6 + 7;

int x, xx, a, b, P, n;
char s[N];

int add(ll a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

struct Mat {
	int a[2][2];
	Mat() { rep(i, 0, 2) rep(j, 0, 2) a[i][j] = 0; }
	Mat(int x, int y, int i, int j) {
		a[0][0] = x, a[0][1] = y;
		a[1][0] = i, a[1][1] = j;
	}
	void set() {
		rep(i, 0, 2) a[i][i] = 1;
	}
	Mat operator * (const Mat &c) const {
		Mat r;
		rep(i, 0, 2) rep(j, 0, 2) rep(k, 0, 2) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
		return r;
	}
};

Mat kpow(Mat a, int k) {
	Mat r;
	r.set();
	while(k) {
		if(k & 1) r = r * a;
		a = a * a;
		k >>= 1;
	}
	return r;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> x >> xx >> a >> b >> (s + 1) >> P;
	n = 1e6;
	rep(i, 1, n + 1) s[i] = '9';
	per(i, 1, n + 1) if(s[i] > '0') {
		--s[i];
		rep(j, i + 1, n + 1) s[j] = '9';
		break;
	}
	Mat r; r.set();
	Mat A(a, b, 1, 0);
	per(i, 1, n + 1) {
		r = r * kpow(A, s[i] - '0');
		A = kpow(A, 10);
	}
	int ans = add(mul(r.a[0][0], xx), mul(r.a[0][1], x));
	cout << ans << endl;
	return 0;
}
