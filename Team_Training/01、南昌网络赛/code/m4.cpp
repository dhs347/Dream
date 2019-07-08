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

const int N = 101010, M = 300;

string s, t;
int n, m;
int ne[N][M];

void solve() {
  int len = sz(t);
  int p = 0;
  rep(i, 0, len) {
    int c = t[i];
    if(~ne[p][c]) {
      p = ne[p][c];
    } else {
      cout << "NO" << endl;
      return ;
    }
  }
  cout << "YES" << endl;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> s;
  n = sz(s); s = ' ' + s;
  rep(i, 0, M) ne[n][i] = -1;
  for(int i = n - 1; ~i; --i) {
    rep(j, 0, M) ne[i][j] = ne[i + 1][j];
    ne[i][s[i + 1]] = i + 1;
  }
  cin >> m;
  while(m--) {
    cin >> t;
    solve();
  }
  return 0;
}
