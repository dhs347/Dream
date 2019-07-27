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
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int P=1e9+7;

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

int linear_recurrence(ll n, int m, vi a, vi c) {
	if (n<m) return (a[n]+P)%P;
	vector<ll> v(m, 0), u(m<<1, 0);
	v[0] = 1;
	for(ll x = 0, W = n ? 1ll<<(63 - __builtin_clzll(n)) : 0; W; W >>= 1, x <<= 1) {
		fill(all(u), 0);
		int b = !!(n & W); if(b) x++;
		if(x < m) u[x] = 1;
		else {
			rep(i, 0, m) rep(j, 0, m) (u[i + b + j] += v[i] * v[j]) %= P;
			per(i, m, 2*m) rep(j, 0, m) (u[i - m + j] += c[j] * u[i]) %= P;
		}
		copy(u.begin(), u.begin() + m, v.begin());
	}
	ll ans = 0;
	rep(i, 0, m) (ans += v[i] * a[i]) %= P;
	return (ans+P)%P;
}

//const int N=10005;
int T; ll k,n;
vi a,c;

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%lld%lld",&k,&n);
        if (n==-1) printf("%lld\n",Pow(k+1,P-2)*2%P); else {
            a.clear(),c.clear();
            a.resize(k,0),c.resize(k,0);
            a[0]=1; ll kk=Pow(k,P-2);
            rep(i,1,k) {
                rep(j,max(i-k,0ll),i) a[i]+=a[j],a[i]%=P;
                a[i]=a[i]*kk%P;
            }
            rep(i,0,k) c[i]=kk;
            int ret=linear_recurrence(n,k,a,c);
            printf("%d\n",ret);
        }
    }
    
	return 0;
}

