//ȡģ״ѹ 
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

const int N = 1050;
int T, d;
string s;
int n, a[20], ans, cnt[20], jc[20], w, f[N][N], S;
ll x;
int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	jc[0] = 1;
	rep(i, 1, 10) jc[i] = jc[i-1] * i;
	rep(cas, 0, T) {
		cin >> s >> d;
		n = sz(s);
		rep(i, 0, n) a[i] = s[i] - '0', cnt[a[i]]++;
		w = 1;
		rep(i, 0, 10) w = w * jc[cnt[i]], cnt[i] = 0;
		rep(i, 0, S) rep(j, 0, d) f[i][j] = 0;
		f[0][0] = 1;
		S = pw(n);
		rep(i, 0, S) 
			rep(j, 0, d) if (f[i][j])
				rep(k, 0, n) if (!(pw(k) & i)) {
					int &x = f[pw(k) | i][(j * 10 + a[k]) % d];
					x += f[i][j];
				}
		cout << f[S-1][0] / w << endl;
	}
	return 0;
}


