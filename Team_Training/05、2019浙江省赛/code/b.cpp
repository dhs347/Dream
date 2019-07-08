#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N=1e5+5;
int a[N],b[N],n,T,M; ll x,y,xx,yy,ans;
vi V[N];

ll work(int j,ll x,ll y) {
	ll t=y-a[j];
	if (t>M || t <= 0 || V[t].empty()) return 0;
	ll p=a[j]-t;
	if (!p) {
		if (x!=0) return 0;
		return lower_bound(all(V[a[j]]),j)-V[a[j]].begin()-1;
	}
	if (x%p) return 0;
	ll i=x/p+j;
	if (i<1 || i>=j || a[i]!=t) return 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	cin>>T;
	while (T--) {
		cin>>n>>x>>y; 
		xx=yy=0,ans=0,M=0;
		rep(i,1,n+1) cin>>a[i],V[a[i]].pb(i),M=max(M,a[i]),
			xx+=(ll)a[i]*i,yy+=(ll)a[i]*a[i]*i;
		yy-=y,xx-=x;
		yy=-yy,xx=-xx;
		if (xx==0) {
			if (yy!=0) {
				cout<<0<<endl;
				rep(i,1,n+1) V[a[i]].clear();
				continue;
			}
			ans=0;
			rep(i,1,M+1) {
				if (V[i].empty()) continue;
				ll tt=V[i].size();
				ans+=tt*(tt-1)/2;
			}
			cout<<ans<<endl;
			rep(i,1,n+1) V[a[i]].clear();
			continue;
		}
		if (yy%xx) {
			cout<<0<<endl;
			rep(i,1,n+1) V[a[i]].clear();
			continue;
		}
		y=yy/xx,x=xx;
		rep(j,1,n+1) ans+=work(j,x,y);
		cout<<ans<<endl;
		rep(i,1,n+1) V[a[i]].clear();
	}

	return 0;
}
