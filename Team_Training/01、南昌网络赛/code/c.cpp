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

const int N = 1e7 + 7;
const int P1 = 1e9 + 7, P2 = 1e9 + 9;
map<pii, vi> M;
vi ans;
int f[N], g[N], ok, sum1, sum2, S, m, n, T;
string s;
ll num1, num2;
vi min(vi a, vi b) {
  rep(i, 0, min(sz(a), sz(b))) 
    if (a[i] < b[i]) return a;
    else if (b[i] < a[i]) return b;
  if (sz(a) < sz(b)) return a;else return b;
}

int main() {
freopen("a.in","r",stdin);
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> T;
  f[1] = f[2] = 1;
  g[1] = g[2] = 1;
  rep(i, 3, N) f[i] = f[i-1] + f[i-2], g[i] = g[i-1] + g[i-2], f[i] %= P1, g[i] %= P2;
  rep(cas, 0, T) {
    cin >> s;
    ans = vi();
    num1  = num2 = 0;
    rep(i, 0, sz(s)) {
      num1 = num1 * 10 + s[i] - '0';
      num2 = num2 * 10 + s[i] - '0';
      num1 %= P1;
      num2 %= P2;
    }
    m = 15;
    S = pw(m);
    M.clear();ok = 0;
    rep(i, 0, S) {
      sum1 = sum2 = 0;
      vi tmp;
      rep(j, 0, m) if (pw(j) & i) tmp.pb(j + 1 + m), sum1 += f[f[j+1+m]], sum2 += g[g[j+1+m]], sum1 %= P1, sum2 %= P2;
      pii t = mp(sum1, sum2);
      if (M.count(t)) M[t] = min(M[t], tmp);
      else M[t] = tmp;
    }
    S = pw(m);
    rep(i, 0, S) {
      sum1 = sum2 = 0;
      vi tmp;
      rep(j, 0, m) if (pw(j) & i) tmp.pb(j + 1), sum1 += f[f[j+1]], sum2 += g[g[j+1]], sum1 %= P1, sum2 %= P2;
      pii t = mp((num1 - sum1 + P1) % P1, (num2 - sum2 + P2) % P2);
      if (M.count(t)) {
			for (auto v : M[t]) tmp.pb(v);
			if (ok) ans = min(ans, tmp);
			else ans = tmp;
			ok = 1;
      }
    }
    if (ok) {
      rep(i, 0, sz(ans)) {
		cout << ans[i] << (i == sz(ans)-1 ? "\n" : " ");
      }
    }else cout << -1 << endl;
  }
  return 0;
}
