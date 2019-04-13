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
typedef long double db;
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

const int N = 300;
db s[N], ans[N], tmp[N], f[N][N];
int n, x;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	n = 128;
	s[0] = s[1] = 1;
	f[1][0] = 1;
	rep(i, 2, n+1) {
		rep(j, 0, i) {
			int k = i - 1 - j;
			s[i] += s[j] * s[k];
		}
		rep(j, 0, i) f[i][j+1] += s[i-1] * f[i-1][j] * 2;
		rep(j, 1, i-1) {
			db w = s[j] * s[i - 1 - j];
			rep(k, 0, j+1) 
				rep(l, 0, i - 1 - j + 1){
					f[i][(k + 1) ^ (l + 1)] += f[j][k] * f[i - 1 - j][l] * w;
				}
		}
		rep(j, 0, i+1) f[i][j] /= s[i];
	}
	cin >> n;
	ans[0] = 1;
	rep(i, 1, n+1) {
		cin >> x;
		rep(j, 0, 128+1) tmp[j] = 0;
		rep(j, 0, 128+1)
			rep(k, 0, 128+1) tmp[j ^ k] += ans[j] * f[x][k];
		rep(j, 0, 128+1) ans[j] = tmp[j];
	} 
	cout << 1 - ans[0]; 
	return 0;
}

