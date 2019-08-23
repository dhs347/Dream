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


const int N = 1e6 + 7;
int n, M, f[N], g[N], phi[N], fs[N], p[N]; // f[n] 为 n 的最小质因子， g[n]=f[n]^k ， phi[n] 为欧拉函数， u[n] 为莫比乌斯函数， h[n] 为一般积性函数 

void prime(int n) {
    phi[1]=1; // 1 的时候特判 
    rep(i, 2, n+1) {
        if (!f[i]) {
            p[++M]=i;
            f[i] = g[i] = i;
            phi[i] = i - 1;
        }// 质数的时候特判 
        for (int j = 1, k; j <= M && p[j] <= f[i] && i * p[j] <= n; j++){
            f[k = i * p[j]] = p[j];
            if (p[j] < f[i]) {
                g[k] = p[j];
                phi[k] = phi[i] * phi[p[j]];        
            }else {
                g[k] = g[i] * p[j];
                phi[k] = phi[i] * p[j];
            }
        }
    }
    rep(i, 1, n+1) fs[i] = mul(phi[i], i), fs[i] = add(fs[i], fs[i-1]); 
}

int inv6, inv2;
int cal(int x) {return mul(mul(x, 1 + x), inv2);}

unordered_map<int, int> S;
int F(int n) {
    if (n <= 1e6) return fs[n];
    if (S.count(n)) return S[n];
    int res = mul(2 * n + 1, mul(n, n+1)); res = mul(res, inv6);
    for (int i = 2, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res = add(res, -mul(F(n / i), add(cal(j), -cal(i-1))));
    }
    return S[n] = res;
}

int T, a, b;

int main() {
    //FI(a);
    ios::sync_with_stdio(0);
    cin.tie(0);
    //cout << setiosflags(ios::fixed);
    //cout << setprecision(2);
    cin >> T; inv6 = kpow(6, P - 2); inv2 = kpow(2, P - 2);
    prime(1e6 + 1); 
    rep(cas, 0, T) {
        cin >> n >> a >> b;
        cout << mul(add(F(n), -1), inv2)  << endl;
    }
    return 0;
}
