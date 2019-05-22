// 状压dp计数，状压dp要注意预处理转移，减少复杂度 
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
const int P = 1000003;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 20;
int T, n, k, m, f[60][1 << 15], S, now, ans, ok[60][200];
string s[N];

int get(int x) {
	int cnt = 0;
	while (x) {
		x = x & (x - 1);
		cnt++;
	}
	return cnt;
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k;
		rep(i, 0, n) cin >> s[i];
		m = sz(s[0]);
		S = pw(n);
		rep(i, 0, m+1) rep(j, 0, S) f[i][j] = 0;
		rep(i, 0, m+1) rep(j, 'a', 'z'+1) {
			ok[i][j] = 0;
			rep(t, 0, n) if (s[t][i] == '?' || s[t][i] == j) ok[i][j] |= pw(t); 
		}
		f[0][S-1] = 1;
		rep(i, 0, m)
			rep(j, 0, S) if (f[i][j]) {
				rep(l, 'a', 'z'+1) {
					//now = 0;
					//rep(t, 0, n) if ((pw(t) & j) && (s[t][i] == '?' || s[t][i] == l)) now |= pw(t);
					now = j & ok[i][l];
					f[i+1][now] = add(f[i+1][now], f[i][j]);
				}  
			}
		ans = 0;
		rep(i, 0, S) if (get(i) == k) ans = add(ans, f[m][i]);	
		cout << ans << endl;	
	}
	return 0;
}


