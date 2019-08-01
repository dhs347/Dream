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

const int N = 1e4 + 16;
int n, m, x[N], y[N], t[N], cnt[N], T, k, mid, p[N], sum;
vector<ll> w1[N], w2[N], dpl[3][N], dpr[3][N];
vector<pii> l[N], r[N];
vi V;
ll ans[N], f[N];

void upd(ll &x, ll y) { x = min(x, y);}

void ini() {
    V.clear(); 
    rep(i, 1, n+1) {
        cnt[i] = 0; l[i].clear(), r[i].clear();
        rep(j, 0, 3) dpl[j][i].clear(), dpr[j][i].clear();
        w1[i].clear(); w2[i].clear();
    }
}

int main() {
    //FI(a);FO(a);
    ios::sync_with_stdio(0);
    cin.tie(0);
    //cout << setiosflags(ios::fixed);
    //cout << setprecision(2);
    cin >> T;
    rep(cas, 0, T) {
        cin >> n >> m >> k;
        rep(i, 1, k+1) {
            cin >> x[i] >> y[i] >> t[i]; V.pb(x[i]);
        }
        V.pb(0); V.pb(1); sort(all(V));
        V.erase(unique(all(V)), V.end());
        n = sz(V) - 1; mid = (m + 1) / 2;
        rep(i, 1, k+1) {
            p[i] = lower_bound(all(V), x[i]) - V.begin();
            cnt[p[i]]++;
            if (p[i] == 1) {
                l[1].pb(mp(y[i], t[i]));
                continue;
            } 
            if (y[i] < mid) l[p[i]].pb(mp(mid - y[i], t[i]));
            else r[p[i]].pb(mp(y[i] - mid, t[i]));
        }
        rep(i, 1, n+1) {
            sort(all(l[i])), sort(all(r[i]));
            rep(j, 0, 3) {
                dpl[j][i].resize(sz(l[i]) + 1, pw(60)); dpl[j][i][0] = 0;
                dpr[j][i].resize(sz(r[i]) + 1, pw(60)); dpr[j][i][0] = 0;
            }
            if (i == 1) {
                dpl[2][1][0] = mid - 1;
                rep(j, 1, sz(l[i])+1) per(h, 1, j+1) {
                    upd(dpl[0][i][h], dpl[0][i][h-1] + l[i][j-1].se);  
                    upd(dpl[1][i][h], dpl[0][i][h-1] + l[i][j-1].se + l[i][j-1].fi - 1); 
                    upd(dpl[2][i][h], dpl[0][i][h-1] + l[i][j-1].se + l[i][j-1].fi - 1+ abs(l[i][j-1].fi - mid)); 
                }
                continue;
            }
            rep(j, 1, sz(l[i])+1) per(h, 1, j+1) {
                upd(dpl[0][i][h], dpl[0][i][h-1] + l[i][j-1].se);  
                upd(dpl[1][i][h], dpl[0][i][h-1] + l[i][j-1].se + l[i][j-1].fi); 
                upd(dpl[2][i][h], dpl[0][i][h-1] + l[i][j-1].se + 2 * l[i][j-1].fi); 
            }
            rep(j, 1, sz(r[i])+1) per(h, 1, j+1) {
                upd(dpr[0][i][h], dpr[0][i][h-1] + r[i][j-1].se);  
                upd(dpr[1][i][h], dpr[0][i][h-1] + r[i][j-1].se + r[i][j-1].fi); 
                upd(dpr[2][i][h], dpr[0][i][h-1] + r[i][j-1].se + 2 * r[i][j-1].fi); 
            }
        }
        //de(dpr[2][3][1]);
        rep(i, 1, n+1) {
            w1[i].resize(cnt[i] + 1, pw(60)); w1[i][0] = 0;
            w2[i].resize(cnt[i] + 1, pw(60)); w2[i][0] = 0;
            if (i == 1) {
                w2[i][0] = mid - 1;
                rep(j, 1, cnt[i]+1) upd(w1[i][j], dpl[1][i][j]), upd(w2[i][j], dpl[2][i][j]);
                continue;
            }
            rep(j, 0, sz(l[i])+1) rep(h, 0, sz(r[i])+1){
                upd(w1[i][j+h], min(dpl[1][i][j] + dpr[2][i][h], dpl[2][i][j] + dpr[1][i][h]));
                upd(w2[i][j+h], dpl[2][i][j] + dpr[2][i][h]);
            }
        }
        //de(w1[2][1]);
        sum = 0;f[0] = 0;
        rep(i, 1, max(k, n)+1) ans[i] = f[i] = pw(60); V[0] = 1;
        rep(i, 1, n+1) {
            sum += cnt[i];
            rep(j, 0, sum+1) f[j] += V[i] - V[i-1];
            per(j, 0, sum+1) rep(h, 0, min(j, cnt[i])+1) upd(ans[j], f[j-h] + w1[i][h]), upd(f[j], f[j-h] + w2[i][h]);
            //de(ans[1]);de(f[0]);
            if (i == 1) f[0] = mid - 1;
        }
        rep(i, 1, k+1) cout << ans[i] << " \n"[i == k];
        ini();
    }
    return 0;
}
