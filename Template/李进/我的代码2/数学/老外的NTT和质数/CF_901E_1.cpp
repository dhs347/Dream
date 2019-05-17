#include <bits/stdc++.h>

using namespace std;

#define N (1 << 18)
#define NX 20000
#define INF 10000
typedef long long LL;

// Prime and Primitive Root
struct PRIME {
    static const int np = 50000;
    vector<int> primes;
    PRIME() {
        bool p[np + 1];
        memset(p, false, sizeof(p));
        primes.push_back(2);
        for (int i = 3; i <= np; i += 2)
            if (!p[i]) {
                primes.push_back(i);
                for (int j = i, k = i + i; j <= np; j += k)
                    p[j] = true;
            }
    }
    inline static int pmod(LL x, LL n) { return (x % n + n) % n; }
    static void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
        if (!b)
            d = a, x = 1, y = 0;
        else {
            exgcd(b, a % b, d, y, x);
            y -= x * (a / b);
        }
    }
    static LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
    static LL inv(LL a, LL n) {
        LL d, x, y;
        exgcd(a, n, d, x, y);
        return d == 1 ? pmod(x, n) : -1;
    }
    static LL sqrt(LL x) {
        LL a = x, b = x + 2;
        if (x == 0)
            return 0;
        while (b - a > 1)
            a = ((b = a) + x / a) >> 1;
        return a * a > x ? a - 1 : a;
    }
    static LL quick_multiply(LL x, LL y, LL p) {
        static LL T = 0, pp = 0, t = 0;
        if (pp != p) {
            pp = p, T = PRIME::sqrt(p), t = T * T - p;
            abs(t) > T && (T++, t = T * T - p);
        }
        LL a = (x %= p) / T, b = x % T, c = (y %= p) / T, d = y % T;
        LL e = a * c / T, f = a * c % T;
        LL v = ((a * d + b * c) % p + e * t) % p, g = v / T, h = v % T;
        LL r = (((f + g) * t % p + b * d) % p + h * T) % p;
        return r < 0 ? r + p : r;
    }
    static LL quick_power(LL n, LL i, LL p) {
        LL r = 1;
        for (n %= p; i; i >>= 1, n = quick_multiply(n, n, p))
            (i & 1) && (r = quick_multiply(r, n, p));
        return r;
    }
    static bool miller_rabin(LL a, LL n) {
        LL r = 0, s = n - 1;
        while (!(s & 1))
            s >>= 1, r++;
        LL x = quick_power(a, s, n);
        if (x == 1)
            return true;
        for (int j = 0; j < r; j++, x = quick_multiply(x, x, n))
            if (x == n - 1)
                return true;
        return false;
    }
    static LL pollard_rho(LL n) {
        for (LL c = 1, x, y, d;; c++) {
            for (x = y = 2;;) {
                x = quick_multiply(x, x, n), x = (x + c) % n;
                y = quick_multiply(y, y, n), y = (y + c) % n;
                y = quick_multiply(y, y, n), y = (y + c) % n;
                d = PRIME::gcd(abs(y - x), n);
                if (d == n)
                    break;
                else if (d > 1)
                    return d;
            }
        }
    }
    void factors(LL x, vector<pair<LL, int>> &pp) {
        bool large = (LL)np * np < x;
        for (auto g : primes)
            if (x % g == 0) {
                int cnt = 0;
                while (x % g == 0)
                    x /= g, cnt++;
                pp.push_back(make_pair(g, cnt));
                if (x == 1)
                    break;
            }
        if (x != 1) {
            if (!large || is_prime(x))
                pp.push_back(make_pair(x, 1));
            else {
                LL d = pollard_rho(x);
                vector<pair<LL, int>> px;
                factors(d, px), factors(x / d, px);
                sort(px.begin(), px.end());
                for (auto p : px) {
                    if (!pp.empty() && pp.back().first == p.first)
                        pp.back().second += p.second;
                    else
                        pp.push_back(p);
                }
            }
        }
    }
    LL euler(LL n) {
        vector<pair<LL, int>> pp;
        factors(n, pp);
        LL r = 1;
        for (auto &p : pp)
            r *= quick_power(p.first, p.second - 1, n) * (p.first - 1);
        return r;
    }
    bool is_prime(LL n) {
        static LL p4 = 3215031751LL, p7 = 341550071728321LL;
        for (int i = 0; i < 100; i++)
            if (n == primes[i])
                return true;
            else if (n % primes[i] == 0)
                return false;
        int k = n < p4 ? 4 : (n < p7 ? 7 : 12);
        for (int i = 0; i < k; i++)
            if (!miller_rabin(primes[i], n))
                return false;
        return true;
    }
    int primitive_root(LL p) {
        vector<pair<LL, int>> pp;
        LL phi = p - 1;
        if (p <= 4)
            return p - 1;
        else if (!is_prime(p)) {
            factors((p & 1) ? p : p / 2, pp);
            if (pp.size() != 1 || pp[0].first == 2)
                return -1;
            pp.clear(), phi = euler(p);
        }
        factors(phi, pp);
        for (int g = 2; g < p; g++) {
            bool ok = gcd(g, p) == 1;
            for (auto &x : pp)
                if (quick_power(g, phi / x.first, p) == 1) {
                    ok = false;
                    break;
                }
            if (ok)
                return g;
        }
        return -1;
    }
    void primitive_roots(LL p, vector<LL> &gg) {
        LL g = primitive_root(p);
        for (LL i = 1, q = g; i < p; i++, q = quick_multiply(q, g, p))
            if (gcd(p - 1, i) == 1)
                gg.push_back(q);
    }
};

// Number-Theoretic Transform (NTT) (mod p = k * 2^n + 1)
struct NTT {
    LL p, g;
    NTT() {}
    NTT(LL p, LL g) { this->p = p, this->g = g; }
    inline void init_primitive(LL ww[][N + 1], int n) const {
        assert((p - 1) % n == 0);
        LL gg = PRIME::quick_power(g, (p - 1) / n, p);
        ww[0][0] = ww[1][n] = 1;
        for (int i = 1; i < n; i++)
            ww[0][i] = PRIME::quick_multiply(ww[0][i - 1], gg, p);
        for (int i = n - 1; i >= 0; i--)
            ww[1][i] = PRIME::quick_multiply(ww[1][i + 1], gg, p);
    }
    inline void back_factor(LL *arr, int n) const {
        LL ninv = PRIME::quick_power(n, p - 2, p);
        for (int i = 0; i < n; i++)
            arr[i] = PRIME::quick_multiply(arr[i], ninv, p);
    }
    void FFT(LL *arr, int n, bool forth) const {
        static LL ww[2][N + 1];
        static int nw = 0;
        if (nw != n)
            nw = n, init_primitive(ww, n);
        for (int i = 1, j = n >> 1, k, l = j; i < n; j ^= k, i++) {
            if (i < j)
                swap(arr[i], arr[j]);
            for (k = l; k & j; j ^= k, k >>= 1)
                ;
        }
        LL *xx, *w, x, y;
        for (int i = 1; i < n; i <<= 1)
            for (int ii = i << 1, ni = n / ii, j = 0, k; j < n; j += ii)
                for (k = 0, xx = &arr[j], w = forth ? ww[0] : ww[1]; k < i;
                     k++, xx++, w += ni) {
                    x = *xx, y = PRIME::quick_multiply(xx[i], *w, p);
                    *xx = (x + y) % p, xx[i] = (x + p - y) % p;
                }
        if (!forth)
            back_factor(arr, n);
    }
    void bluestein(LL *arr, int n, bool forth) const {
        static LL ww[2][N + 1], arx[2][N];
        static int nw = 0, nn = 1;
        if (nw != n) {
            nw = n;
            init_primitive(ww, n);
            while (nn < (n << 1))
                nn <<= 1;
            for (int k = 0; k < 2; k++)
                for (int i = 0; i < nn; i++) {
                    int j = i - n, jj = ((j - (LL)j * j) / 2 % n + n) % n;
                    arx[k][i] = ww[k][jj];
                }
            FFT(arx[0], nn, true), FFT(arx[1], nn, true);
        }
        LL *w = forth ? ww[0] : ww[1];
        for (int i = 0; i < n; i++)
            arr[i] =
                PRIME::quick_multiply(arr[i], w[(LL)i * (i + 1) / 2 % n], p);
        memset(arr + n, 0, (nn - n) * sizeof(LL));
        FFT(arr, nn, true);
        multiply(arr, nn, arx[forth ? 0 : 1]);
        FFT(arr, nn, false);
        for (int i = 0; i < n; i++)
            arr[i] = PRIME::quick_multiply(arr[i + n],
                                           w[(LL)i * (i - 1) / 2 % n], p);
        memset(arr + n, 0, (nn - n) * sizeof(LL));
        if (!forth)
            back_factor(arr, n);
    }
    void DFT_brute_force(LL *arr, int n, bool forth) const {
        static LL ww[2][N + 1], arx[N];
        static int nw = 0;
        if (nw != n)
            nw = n, init_primitive(ww, n);
        memcpy(arx, arr, n * sizeof(LL));
        memset(arr, 0, n * sizeof(LL));
        LL *w = forth ? ww[0] : ww[1];
        for (int i = 0; i < n; i++)
            for (int k = 0, l = 0; k < n;
                 k++, l = l + i >= n ? l + i - n : l + i)
                arr[i] = (arr[i] + PRIME::quick_multiply(w[l], arx[k], p)) % p;
        if (!forth)
            back_factor(arr, n);
    }
    void multiply(LL *arr, int n, const LL *other) const {
        for (int i = 0; i < n; i++)
            arr[i] = PRIME::quick_multiply(arr[i], other[i], p);
    }
    void inverse(LL *arr, int n) const {
        for (int i = 0; i < n; i++)
            arr[i] = PRIME::quick_power(arr[i], p - 2, p);
    }
    void linear(LL *arr, int n, LL k, LL c) const {
        for (int i = 0; i < n; i++)
            arr[i] = (PRIME::quick_multiply(arr[i], k, p) + c + p) % p;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    LL n, nn = 1, pp, p, arb[N], trb[N], arc[N], trc[N], v;
    bool valid = true;
    PRIME prime;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arb[i], trb[(n - i) % n] = arb[i];
    for (int i = 0; i < n; i++)
        cin >> arc[i];
    for (int i = 0; i < n && valid; i++)
        v = arc[i] - arc[(i - 1 + n) % n], valid = !(v & 1), trc[i] = -(v >> 1);
    if (!valid) {
        cout << 0 << endl;
        return 0;
    }
    while (nn < (n << 1))
        nn <<= 1;
    pp = n * nn / PRIME::gcd(n, nn);
    for (p = pp + 1; p < NX || !prime.is_prime(p); p += pp)
        ;
    NTT ntt(p, prime.primitive_root(p));
    void (NTT::*dft)(LL *, int, bool) const =
        n > 1000 ? &NTT::bluestein : &NTT::DFT_brute_force;
    (ntt.*dft)(trb, n, true), (ntt.*dft)(trc, n, true);
    ntt.inverse(trb, n), ntt.multiply(trc, n, trb);
    (ntt.*dft)(trc, n, false);
    trc[0] = 0;
    for (int i = 1; i < n; i++) {
        trc[i] = (trc[i] + trc[i - 1]) % p;
        if (trc[i] > INF)
            trc[i] -= p;
    }
    LL xa = n, xb = 0, xc = -arc[0], xx, xx1, xx2, delta, sqd;
    vector<LL> xs;
    for (int i = 0; i < n; i++)
        xx = arb[i] - trc[i], xb += xx, xc += xx * xx;
    xb *= -2;
    if ((delta = xb * xb - 4 * xa * xc) >= 0) {
        sqd = PRIME::sqrt(delta);
        xx1 = -xb + sqd, xx2 = -xb - sqd;
        if (sqd * sqd == delta && xx1 % (2 * xa) == 0)
            xs.push_back(xx1 / (2 * xa));
        if (sqd * sqd == delta && delta != 0 && xx2 % (2 * xa) == 0)
            xs.push_back(xx2 / (2 * xa));
    }
    cout << xs.size() << endl;
    sort(xs.begin(), xs.end());
    for (auto x : xs) {
        cout << x;
        for (int i = 1; i < n; i++)
            cout << " " << trc[i] + x;
        cout << endl;
    }
    return 0;
}
