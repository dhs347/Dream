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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----
const int N = 1e5 + 7;
ll n, m, A, B, a[N], s[N], f[N];
int r, l[N];
int main(){
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> A >> B; 
	if (A < B) swap(A, B);
	rep(i, 1, n+1) cin >> a[i];
	a[n+1] = a[n] + A; a[0] = a[1] - A;
	n++;
	rep(i, 1, n+1) {
		if (a[i] >= a[i-1] + B) l[i] = l[i-1];
		else if (a[i] >= a[i-2] + B) l[i] = i - 1;
		else l[i] = i;
	}
	r = 0;f[0] = s[0] = 1;
	rep(i, 1, n+1) {
		while (r + 1 < i && a[r + 1] + A <= a[i]) r++;
		if (r >= l[i-1]) {
			if (l[i-1] > 0) f[i] = ((s[r] - s[l[i-1] - 1]) % P + P) % P;
			else f[i] = s[r];
			
		}
		s[i] = (s[i-1] + f[i]) % P;
	}
	cout << f[n] << endl;
	return 0; 
}


