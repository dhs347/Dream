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

const int N = 101010;

int n;
int a[N], cnt[N][2], pre[N][2];

void solve() {
  cin >> n;
  rep(i, 3, n + 3) cin >> a[i], a[i] ^= a[i - 1];
  rep(i, 3, n + 3) a[i] ^= a[i - 1];
  rep(i, 1, n + 3) {
    rep(o, 0, 2) cnt[i][o] = cnt[i - 1][o], pre[i][o] = pre[i - 1][o];
    int c = (i & 1);
    cnt[i][c] += 1;
    pre[i][c] ^= a[i];
  }
  int q;
  cin >> q;
  while(q--) {
    int l, r;
    cin >> l >> r;
    r += 2;
    int ans = 0;
    rep(o, 0, 2) {
      if(!((cnt[r][o] - cnt[l - 1][o]) & 1)) {
      	ans ^= pre[r][o] ^ pre[l - 1][o];
      }
    }
    cout << ans << endl;
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
