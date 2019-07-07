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

const int N=1e6+5;
char aa[N],bb[N],cc[N],gg[N]; int p,a,b,c,g;

int mul(int x,int y) {
	return (ll)x*y%p;
}

int put(char s[],int p) {
	int ret=0,n=strlen(s);
//	de(n);
	rep(i,0,n) {
		assert(s[i]>='0' && s[i]<='9');
		ret=((ll)ret*10+s[i]-'0')%p;
	}
	assert(ret>=0);
	return ret; 
}

int Pow(int x,int k) {
//	assert(k>=0);
	int ret=1;
	for (; k; k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
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


BSGS BB;

int main() {
//	file_put();
	
	scanf("%s",aa);
	scanf("%s",bb);
	scanf("%s",cc);
	scanf("%s",gg);
	scanf("%d",&p);
	
	a=put(aa,p-1);
	b=put(bb,p-1);
	c=put(cc,p);
	g=put(gg,p);
//	assert(a>=0);
//	if (a<0) return 0;
	a=Pow(g,a),b=Pow(g,b);
	if (b==0) {
		if (c==0) return 0*printf("1\n");
		return 0*printf("no solution\n");
	}
	b=mul(Pow(b,p-2),c);
	int n=BB.bsgs(a,b,p);
	if (n==-1) return 0*printf("no solution\n");
	assert(n>0);
	printf("%d\n",n);
	
	return 0;
}

