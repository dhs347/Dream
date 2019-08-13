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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1<<11;
int cnt,n,x,C,inf=1000,m,tot=0,le[100005],L=0,NOT[100005]; char s[N]; vi G[100005],E[100005];
struct ed{
	int x,y,w;
} EE[100005];

void link(int x,int y,int w) {
	G[x].pb(y),E[x].pb(w);
	EE[++tot]={x,y,w};
}

int Not(int x) {
	if (NOT[x]) return NOT[x];
	++cnt; link(x,cnt,-inf);
	link(C,cnt,inf>>1);
	return NOT[x]=cnt;
}

int Or(vi V) {
	//if (V.empty()) return;
	++cnt;
	for (auto x:V) link(x,cnt,inf);
	link(C,cnt,-inf/2);
	return cnt;
}

int And(vi V) {
	vi E;
	for (auto x: V) E.pb(Not(x));
	return Not(Or(E));
}

int B(int x) {
	vi V;
	for (int j=n-1,k=1; j>=0; --j,++k) {
		if (x>>j&1) V.pb(k); else V.pb(Not(k));
	}
	return And(V);
}

void init() {
	++cnt; link(1,cnt,inf);
	C=++cnt; link(cnt-1,cnt,inf);
}

void dfs(int x) {
	if (le[x]) return;
	le[x]=1;
	for (auto y: G[x]) {
		if (!le[y]) dfs(y);
		le[x]=max(le[x],le[y]+1);
	}
	L=max(L,le[x]);
}

int main() {
//	file_put();
	
	scanf("%d%s",&n,s),m=strlen(s),cnt=n;
	init();
	vi V;
	rep(i,0,m) {
		if (s[i]=='1') 
		V.pb(B(i));
	}
	Or(V); 
	rep(i,1,cnt+1) dfs(i);
	rep(i,1,n+1) le[i]=L;
	printf("%d %d\n",L,cnt);
	rep(i,1,cnt+1) printf("%d%c",L+1-le[i]," \n"[i==cnt]);
	printf("%d\n",tot);
	rep(i,1,tot+1) printf("%d %d %d\n",EE[i].x,EE[i].y,EE[i].w);
	//assert(L<=25); assert(cnt<=10000); assert(tot<=30000);
	
	return 0;
}

