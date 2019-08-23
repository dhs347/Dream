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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 3030;

char s[11][N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    s[1][0][0] = s[1][0][1] = s[1][1][1] = 'C';
    s[1][1][0] = 'P';
    rep(o, 2, 11) {
        int t = pw(o - 1) - 1;
        rep(i, 0, pw(o)) rep(j, 0, pw(o)) {
            s[o][i][j] = s[o - 1][i & t][j & t];
        }
        rep(i, pw(o - 1), pw(o)) rep(j, 0, pw(o - 1)) {
            auto &c = s[o][i][j];
            c = (c == 'P' ? 'C' : 'P'); 
        }
    }
    int T; cin >> T;
    while(T--) {
        int k; cin >> k;
        rep(i, 0, pw(k)) {
            rep(j, 0, pw(k)) cout << s[k][i][j]; cout << endl;
        }
    }
    return 0;
}
