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
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 9;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 6;
int a[N], len, n, m, f[1005][305][20], ans;
char s[N];

int get(int x) {
	if (x == 'A') return 0;
	if (x == 'G') return 1;
	if (x == 'C') return 2;
	if (x == 'T') return 3;
}

struct Trie{
    static const int N = 101010 , M = 4;
    int ne[N][M] , fail[N] , fa[N] , rt , L;
    void ini(){ fill_n(ne[fail[0] = N-1],M,0);L = 0;rt = newnode();}
    int newnode(){ fill_n(ne[L],M,0); return L++; }
    void add(char *s){
        int p = rt;
        for(int i=0;s[i];++i){
            int c = get(s[i]);// modify
            if(!ne[p][c]) ne[p][c] = newnode() , fa[L-1] = p;
            p = ne[p][c];
        }
        a[p] = max(a[p], len);
    }
    void Build(){
        vi v;v.pb(rt);
        rep(i,0,sz(v)){
            int c = v[i];
            rep(i,0,M) ne[c][i] ?
                v.pb(ne[c][i]) , fail[ne[c][i]] = ne[fail[c]][i] :
                ne[c][i] = ne[fail[c]][i];
        }
    }
} tr;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	tr.ini();
	rep(i, 1, m+1) {
		cin >> s;
		len = strlen(s);
		tr.add(s);
	}
	tr.Build();
	f[0][0][0] = 1;
	rep(i, 1, n+1) {
		rep(j, 0, tr.L)
			rep(l, 0, 4){
				int v = tr.ne[j][l], u = v, t = 0;
				while (u) {
					t = max(t, a[u]);
					u = tr.fail[u];
				}
				rep(k, 0, t) f[i][v][0] = add(f[i][v][0], f[i-1][j][k]);
				rep(k, t, 11) f[i][v][k+1] = add(f[i][v][k+1], f[i-1][j][k]); 
			}  
	}
	rep(j, 0, tr.L) ans = add(ans, f[n][j][0]);
	cout << ans;
	return 0;
}


