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
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5e5 + 7;
ll R, S;
int n, v[N], T;
namespace ST {
    const int N = ::N, M = 19;
    int lg2[N];
    pii st[N][M];
    void bud(int n, int a[]) {
        assert((1 << M) > n);
        lg2[0] = -1; rep(i, 1, n + 1) lg2[i] = lg2[i >> 1] + 1;
        rep(i, 0, n) st[i][0] = mp(a[i], i);
        rep(j, 1, M) rep(i, 0, n) {
            if (i + (1 << j) > n) break;
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    int qry(int l, int r) {
        if (l > r) swap(l, r);
        int lv = lg2[r - l + 1];
        return max(st[l][lv], st[r - (1 << lv) + 1][lv]).se;
    }
}

ll solve(ll l, ll r, ll st, ll ed) {
	if (st + R * (r - l + 1) < ed) return 0;
	if (l > r) return 0;
	if (l == r) return v[l] * (st + R - ed);
	int p = ST :: qry(l, r);
	ll res = 0, mid, now;
	mid = max(ed - (r - p + 1) * R, 0ll);
	if ((p - l) * R + st >= S) res += solve(l, p-1, st, S), now = S;
	else now = (p - l) * R + st;
	res += (now - mid) * v[p];
	if (mid + R + (r - p) * R > ed) res += solve(p+1, r, mid + R, ed);
	return res;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> S >> R >> n;
		R = min(R, S);
		rep(i, 0, n) cin >> v[i];
		ST :: bud(n, v);
		cout << solve(0, n-1, S, R) << endl;
	}
	return 0;
}


