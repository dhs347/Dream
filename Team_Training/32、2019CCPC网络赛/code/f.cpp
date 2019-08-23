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

const int N = 101010;

int n, m;
int a[N << 1], p[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin >> n >> m;
    rep(i, 1, n + 1) cin >> a[i + n], p[a[i + n]] = i + n;
    int pos = n;
    while(m--) {
        int x; cin >> x;
        int t = p[x];
        swap(a[t], a[pos]); p[x] = pos--;
    }
    vi vec;
    rep(i, 1, n + n + 1) if(a[i]) vec.pb(a[i]);
    rep(i, 0, n) cout << vec[i] << " ";
//    cout << setiosflags(ios::fixed);
//    cout << setprecision(3);
    return 0;
}
