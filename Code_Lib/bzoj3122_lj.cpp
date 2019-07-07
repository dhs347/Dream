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

ll kpow(ll a, ll b, ll P) {
    ll r = 1;
    for (; b; b>>=1, a = a * a % P) if (b & 1) r = r * a % P;
    return r; 
}

void ex_gcd(int a, int b, int &x, int &y){
	b ? (ex_gcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}

inline int Inv(int a, int P) {
	int x, y; ex_gcd(a, P, x, y);
	return x < 0 ? x + P : x;
}

struct BSGS{
    map<ll, int> M;
    ll bsgs(ll x, ll z, ll P) {
    	if(x % P == 0) return -1;
    	ll res = z % P, sa, t = 1, sq = sqrt(P); M.clear();
    	rep(i, 0, sq+1) { if (M.count(t)) break; M[t] = i, t = t * x % P; }
    	t = P / sq, sa = Inv(kpow(x, sq, P), P);
    	rep(i, 0, t+1) if (M.count(res)) 
            return i * sq + M[res]; else res = res * sa % P;
    	return -1;
    }
    ll ex_bsgs(ll x, ll z, ll P) { //x^y==z(mod P)
    	ll t = 1 % P, w = 1, ans, c = 0; z %= P;
    	rep(i, 0, 51) { if (t == z) return i; t = t * x % P; }
    	for(t = __gcd(x, P); t != 1; t = __gcd(x, P)){
    		if (z % t) return -1;
    		z /= t, P /= t, w = w * x / t % P, c++;
    		if (z == w) return c;
    	}
    	z = z * Inv(w, P) % P, ans = bsgs(x, z, P);
    	return ans + (ans != -1) * c;
    }
};

ll p,a,b,x1,t,n; int T; BSGS B;

ll Pow(ll x,ll k) {
	ll ret=1;
	for (; k; k>>=1,x=x*x%p) if (k&1) ret=ret*x%p;
	return ret;
}

int main() {
//	file_put(); 
	
	scanf("%d",&T);
//	de(B.ex_bsgs(0,0,1));
	while (T--) {
		scanf("%lld%lld%lld%lld%lld",&p,&a,&b,&x1,&t);
		if (t==x1) {
			printf("1\n");
			continue;
		}
		if (a==0) {
			if (t==b) printf("2\n"); else printf("-1\n");
			continue;
		}
		if (a==1) {
			if (b==0) {
				printf("%d\n",-1);
				continue;
			};
			n=(t-x1)*Pow(b,p-2)%p+1;
			n%=p,n=(n+p-1)%p+1;
		} else {
			ll x0=b*Pow(1-a,p-2)%p;
			if (x0<0) x0+=p;
			if (x1==x0) {
				printf("%d\n",-1);
				continue;
			}
			ll tmp=(t-x0)*Pow(x1-x0,p-2)%p;
			if (tmp<0) tmp+=p;
			B.M.clear();
			n=B.bsgs(a,tmp,p);
			if (n==-1) {
				printf("-1\n");
				continue;
			}
			n++;
		}
		printf("%lld\n",n);
	}
	
	return 0;
}
