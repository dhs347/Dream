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
typedef vector<ll> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1e5+5;
int n,q,in[N]; vi a,V[N],E[N]; ll x,v[N],cnt[N],dp[N],ret=0;

void dfs(int x) {
	rep(i,0,sz(V[x])) {
		ll y=V[x][i],w=E[x][i];
		dp[y]+=dp[x]*w;
		if (!--in[y]) dfs(y);
	}
}

int main() {
//	file_put();
	
	scanf("%d%d",&n,&q),a.pb(0),a.pb(n);
	rep(i,1,q+1) {
		scanf("%lld",&x);
		while (x<=a.back()) a.pop_back();
		a.push_back(x);
	}
	q=a.size()-1;
	rep(i,1,q+1) {
		x=a[i];
		for (int t=i; t; ) {
			t=upper_bound(a.begin(),a.begin()+t,x)-a.begin()-1;
			if (!t) { v[i]=x; break; }
			V[i].pb(t),E[i].pb(x/a[t]),in[t]++,x%=a[t];
			if (!x) break;
		}
	}
	dp[q]=1,dfs(q);
	rep(i,1,q+1) cnt[v[i]]+=dp[i];
	per(i,1,n) cnt[i]+=cnt[i+1];
	rep(i,1,n+1) printf("%lld\n",cnt[i]);
	
	return 0;
}

