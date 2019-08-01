#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

ll mulmod(ll a, ll b, ll p) {
    __int128 t = a;
    return t * b % p;
}

ll powmod(ll a, ll b, ll p) {
    a %= p;
    ll r = 1;
    while(b) {
        if(b & 1) r = mulmod(r, a, p);
        a = mulmod(a, a, p);
        b >>= 1;
    }
    return r;
}
int spp(ll n, int base) 
{
    ll n2 = n - 1, res;
    int s = 0;
    while(n2 % 2 == 0) n2 >>= 1, s++;
    res = powmod(base, n2, n);
    if((res == 1) || (res == n - 1)) return 1;
    s--;
    while(s >= 0) {
        res = mulmod(res, res, n);
        if(res == n - 1) return 1;
        s--;
    }
    return 0;
}
int isp(ll n) {
    static ll testNum[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    static ll lim[] = {4, 0, 1373653ll, 25326001ll, 25000000000ll, 2152302898747ll, 3474749660383ll, 341550071728321ll, 0, 0, 0, 0};
    if(n < 2 || n == 3215031751ll) return 0;
    for(int i = 0; i < 12; ++i) {
        if(n < lim[i]) return 1;
        if(spp(n, testNum[i]) == 0) return 0;
    }
    return 1;
}
int ansn; ll ans[1000];
ll func(ll x, ll n) {
    return (mulmod(x, x, n) + 1) % n;
}
ll pd(ll n) {
    ll i, x, y, p;
    if(!(n & 1)) return 2;
    if(isp(n)) return n;
    for(i = 1; i < 1000; ++i) {
        x = i; y = func(x, n); p = __gcd((y - x + n) % n, n) % n;

        while(p == 1) {
            x = func(x, n); y = func(func(y, n), n); p = __gcd((y - x + n) % n, n) % n;
        }
        if(p == 0 || p == n) continue;
        return p;
    }
}
void factor(ll n, int t) {
    ll x;
    x = pd(n);
    if(x == n) {
        rep(i, 0, t)
            ans[ansn++] = x; 
        return;
    }
    x= min(x, n / x);
    int cnt = 0;
    while (n % x == 0) n /= x, cnt++;
    factor(x, cnt * t);
    if (n > 1) factor(n, t);
    //factor(x, t+1);
    //factor(n / x, t+1);
}

void fac(ll n) {
    ll x;
    x = pd(n);
    if(x == n) {
        ans[ansn++] = x; 
        return;
    }
    x= min(x, n / x);
    fac(x);
}

int T;
ll n;
int cntp, p[20000], f[20000];

__int128 cal(ll x, int p) {
    __int128 r = x;
    rep(i, 1, p) r = r * x;
    return r;
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    cin >> T;
    //T = 1;
	int m = 10000;
    rep(i, 2, m+1) {
        if (!f[i]) p[++cntp] = i;
        for (int j = i + i; j <= m; j+= i) f[j] = 1;
    }
    rep(cas, 0, T) {
        ansn = 0;
        cin >> n;
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        int an = 100;
        rep(i, 1, cntp+1) if (n % p[i] == 0){
            int cnt = 0;
            while (n % p[i] == 0) cnt++, n/=p[i];
            an = min(an, cnt);
            if (an == 1) break;
            if (n == 1) break;
        }
        if (n > 1) {
            if (n <= m * m) an = 1;
            else {
            	bool ok = 0;
                per(i, 2, 5) {
                    if (an == 1) break;
                    ll x = round(powl(n, (long double)1.0 / i));
                    for (ll j = x; j <= x ; j ++) if (cal(j, i) == n) {
                        ok = 1;
                        an = min(an, i);
                        break;
                    }
                    if (ok) break;
                }
                if(!ok) an = 1;
            }
        }
        cout << an << endl;
    }
    return 0;
}
