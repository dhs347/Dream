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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 8;
int n, f[N], fa[N];
char s[N];
priority_queue<pii> q;
int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

struct Trie{
    static const int N = 101010 , M = 26;
    int ne[N][M] , fail[N] , fa[N] , rt , L, ans = 0, cnt[N], d[N];
    void ini(){ fill_n(ne[fail[0] = N-1],M,0);L = 0;rt = newnode();}
    int newnode(){ fill_n(ne[L],M,0); return L++; }
    void add(char *s){
        int p = rt;
        for(int i=0;s[i];++i){
            int c = s[i] - 'a';// modify
            if(!ne[p][c]) ne[p][c] = newnode() , fa[L-1] = p;
            p = ne[p][c];
        }
        cnt[p]++;
    }
    void dfs(int u) {
    	if (u) q.push(mp(d[u], u));
		rep(i, 0, 26) {
			if (!ne[u][i]) continue;
			int v = ne[u][i];
			d[v] = d[u] + 1;fa[v] = u;
			dfs(v);
		}
	}
    int solve() {
		dfs(0);
		rep(i, 0, L) f[i] = i;
		while(!q.empty()) {
			int x = q.top().se; q.pop();
			if (cnt[x]) {
				//dd(x), dd(get(fa[get(x)]));
				int p, y = x;
				while (cnt[p = get(fa[get(x)])]) {
					f[get(x)] = p;
					x = p;
				}
				//dd(p);
				if (p) cnt[y] = 0, cnt[p] = 1;
				//de(d[x]);
			}
		}
		rep(i, 1, L) if (cnt[i]) ans += d[i];
		return ans;
	}
} tr;



int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	tr.ini();
	rep(i, 1, n+1) {
		cin >> s;
		tr.add(s); 
	}
	cout << tr.solve();
	return 0;
}


