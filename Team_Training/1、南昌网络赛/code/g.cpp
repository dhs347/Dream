#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
typedef unsigned int uint;

const int N = 1e7 + 7;

unsigned int n, M, f[N], g[N], h[N], phi[N], u[N], p[N], ans;
int T;

void prime(int n) {
  u[1] = phi[1] = 1; h[1] = 1;
  rep(i, 2, n+1) {
    if (!f[i]) {
      p[++M] = i;
      f[i] = g[i] = i;
      phi[i] = i-1;
      u[i] = -1;
    }
    for (int j = 1, k; j <= M && p[j] <= f[i] && i * p[j] <= n; j++) {
      f[k = i * p[j]] = p[j];
      if (p[j] < f[i]) {
	g[k] = p[j];
	phi[k] = phi[i] * phi[p[j]];
	u[k] = u[i] * u[p[j]];
      }else {
	g[k] = g[i] * p[j];
	phi[k] = phi[i] * p[j];
	u[k] = 0;
      }
    }
  }
  rep(i, 2, n+1) if (i == g[i]) {
    uint t = g[i] / f[i];
    h[i] = phi[g[i]] - phi[t];
  }else h[i] = h[i / g[i]] * h[g[i]];
  rep(i, 1, n+1) h[i] = h[i-1] + h[i] * i * i * i;
}

uint calc(uint n) {
  unsigned long long x = 1ull * n * (n + 1) / 2;
  if (x % 3 == 0) x = x / 3 * (2 * n + 1);
  else x *= (2 * n + 1) / 3;
  return n * (1ull * n * (n + 1) / 2) * x;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  prime(1e7);
  cin >> T;
  rep(cas, 0, T) {
    cin >> n;
    ans = 0;
    for(uint l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      ans += (h[r] - h[l-1]) * calc(n / l);
    }
    cout << ans % pw(30) << endl;
  }
  return 0;
}
