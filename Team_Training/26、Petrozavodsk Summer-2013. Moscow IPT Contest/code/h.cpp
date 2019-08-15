#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
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
#define lb(x) (x & (-x))
#define FI(a) freopen(#a".in","r", stdin) 
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int N = 100005, L=505, S = L + 70;
ll n, ss[N], num[L+5], LL;
int tot=0, id[S+5], ret[N]; 
ll dp[L+5][120+5][80+5];

//inline int F(int t,int c) { return id[ss[t]*c]; }

/*
11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112111111111111111111111111111111111111111111111111111111111111111111111111111111111111111211111111111111111111111111111111111111111112111111111111111111111111111111111111111111111111111111111112111111111111111211111111111111111211111111111111111111111111111211111111111111111111111112111111111111111112111

*/

const ll inf = 1e18 + 7;

int main() {
	//FI(a);
	scanf("%lld",&n);
	for (ll a=1; a<=S; a*=2) for (ll b=1; b*a<=S; b*=3)
		for (ll c=1; a*b*c<=S; c*=5) for (ll d=1; a*b*c*d<=S; d*=7)
			ss[++tot]=a*b*c*d,id[ss[tot]]=tot; 
	dp[0][1][0]=1;
	rep(i, 0, L+1) {
		int m = 60;
		rep(t, 1, tot+1) rep(c,1,10) {
			int p = id[ss[t] * c];
			if(p == 0) break;
			rep(s, 0, m+1) {
				dp[i+1][p][s + c - 1] += dp[i][t][s];
				dp[i+1][p][s + c - 1] = min(dp[i+1][p][s + c - 1], inf);
			} 
		}
	}
	rep(i,0,L+1) rep(t,1,tot+1) if (ss[t] - i >= 0 && ss[t] - i <= 80) {
		num[i]+=dp[i][t][ss[t]-i];
		num[i] = min(num[i], inf);
	}
	rep(i, 1, L+1) if (n>num[i]) n-=num[i]; else { LL=i; break; }
	for (int i=1,tt=1,s=0; i<=LL; tt*=ret[i],s+=ret[i],i++) {
		rep(c,1,10) {
			ll ans=0;
			rep(j,1,tot+1) {
				int _t = ss[j], _s = _t * tt * c - s - c;
				if (_s<0 || _s>S) continue;
				if (_s - (LL - i) >= 0 && _s - (LL - i) <= 80) {
					ans+=dp[LL-i][j][_s - (LL - i)];
					ans = min(ans, inf);
				}
			}
			if (n>ans) n-=ans; else { ret[i]=c; break; }
		}
	} 
	rep(i, 1, LL+1) printf("%d", ret[i]);
	printf("\n"); 
	return 0;
}

