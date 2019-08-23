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
 int P;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 105, M = 32;
int C[N][N], pp[1005], pw2[N][N], f[M * 2][M][M][M], g[M * 2][M][M][M];
int T, n, m, len, ans, ww, w;

int main() {
    //FI(a);
    clock_t st = clock();
    ios::sync_with_stdio(0);
    cin.tie(0);
    //cout << setiosflags(ios::fixed);
    //cout << setprecision(2);
    cin >> T;
    rep(cas, 0, T) {
        cin >> n >> m >> P;
        C[0][0] = 1;
        rep(i, 1, 50) {
            C[i][0] = 1;
            rep(j, 1, i+1) {
                C[i][j] = add(C[i-1][j], C[i-1][j-1]);
            }
        }
        rep(i, 0, 50+1) {
            pw2[i][1] = (pw(i) - 1) % P;
            pw2[i][0] = 1;
            rep(j, 2, 51) pw2[i][j] = kpow(pw2[i][1], j); 
        }
        pp[0] = 1;
        rep(i, 1, 1000) pp[i] = mul(pp[i-1], 2);
        
        len = n + m;
        ans = 0;
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        f[0][1][0][1] = 1;
        rep(i, 1, len) {
            rep(j, 0, n+1)
                rep(k, 0, m+1) {
                    if (i & 1) w = j;else w = k;
                    if (i & 1) ww = m - k;else ww = n - j;
                    rep(l, 1, w+1) if (f[i-1][j][k][l]) {
                        if (i & 1) {
                            rep(cnt, 1, ww+1) {
                                int s1 = g[i-1][j][k][l], s2 = f[i-1][j][k][l];
                                int &t1 = g[i][j][k+cnt][cnt];
                                int &t2 = f[i][j][k+cnt][cnt]; 
                                int cc = mul(C[ww][cnt], pw2[l][cnt]);
                                t1 = add(t1, add(mul(s1, cc) , mul(i * cnt, mul(s2, cc))));
                                t2 = add(t2, mul(s2, cc));
                            }
                        }else {
                            rep(cnt, 1, ww+1) {
                                int s1 = g[i-1][j][k][l], s2 = f[i-1][j][k][l];
                                int &t1 = g[i][j+cnt][k][cnt];
                                int &t2 = f[i][j+cnt][k][cnt]; 
                                int cc = mul(C[ww][cnt], pw2[l][cnt]);
                                t1 = add(t1, mul(s1, cc));
                                t2 = add(t2, mul(s2, cc));
                            }
                        }
                    }
                }
            rep(j, 0, n+1)
                rep(k, 0, m+1) {
                    if (i & 1) w = k;else w = j;
                    rep(l, 1, w+1) ans = add(ans, mul(g[i][j][k][l], pp[(n - j) * (m - k)]));
                }
        }
        //de(ans); 
        //cout << ans << endl;
        cout << mul(ans, mul(kpow(m, P - 2), kpow(pp[n * m], P - 2))) << endl;
    }
    //clock_t ed = clock();
    //de(1.0 * (ed - st) / CLOCKS_PER_SEC);
    return 0;
}
