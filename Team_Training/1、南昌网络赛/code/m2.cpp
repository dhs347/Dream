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

/*
struct FI {
  static const int S = 1310720;
  int wpos;
  char wbuf[S];
  FI() :: wpos(0) {}
  inline int xchar() {
    static char buf[S];
    static int len = 0, pos = 0;
    if(pos == len) pos = 0, len = fread(buf, 1, S, stdin);
    if(pos == len) return -1;
    return buf[pos++];
  }
  inline void xstring(char * s) {
    int c = xchar();
    while(c <= 32) c = xchar();
    for(; c > 32; c = xchar())
  }
};
*/

const int N = 101010, M = 300;

char s[N], t[N];
int n, m;
int ne[N][M];

void solve() {
  int len = strlen(t);
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
  gets(s + 1);
  n = strlen(s + 1);
  rep(i, 0, M) ne[n][i] = -1;
  for(int i = n - 1; ~i; --i) {
    rep(j, 0, M) ne[i][j] = ne[i + 1][j];
    ne[i][s[i + 1]] = i + 1;
  }
  cin >> m;
  gets(t);
  while(m--) {
    gets(t);
    solve();
  }
  return 0;
}
