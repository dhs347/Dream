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

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fi<<" , "<<(x).se<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1e5+5;
int n,p[N],tot=0; ll a[N]; bool check[N];

void init(int N) {
    rep(i,2,N+1)
        if (!check[i]) {
            p[++tot]=i;
            for (int j=i+i; j<=N; j+=i) check[j]=1;
        }
//    debug_arr(p,tot);
}

unordered_map<ll,ll> U,num,D; ll ans=0;

bool bat(ll x) {
    ll y=1,yy=1; ll &xx=U[x];
    for (int i=1; i<=tot && (ll)p[i]<=x; ++i)
        if (x%p[i]==0) {
            int t=0;
            while (x%p[i]==0) x=x/p[i],t++;
            t%=3;
            rep(j,0,t) y*=p[i];
            t=3-t,t%=3;
            rep(j,0,t) yy*=p[i];
        }
    if (x>1) {
		y*=x;
		ll tt=sqrt(x);
		if (tt*tt==x) yy*=tt; else yy*=x*x;
//        ans+=2;
//        xx=-1;
//        return 1;
    }
    xx=y;
    D[y]=yy,D[yy]=y;
    return 0;
}

int main() {
//    file_put();
    
    init(3000);
    scanf("%d",&n);
    rep(i,1,n+1) {
        scanf("%lld",&a[i]);
        if (!U.count(a[i])) bat(a[i]);
        if (U[a[i]]>0) num[U[a[i]]]++;
    }
    for (auto x:num)
        if (x.fi==1) ans+=2; else
        if (num.count(D[x.fi])) ans+=max(x.se,num[D[x.fi]]); else 
            ans+=2*x.se;
    printf("%lld\n",ans>>1);
//    debug_map(num);
//    debug_map(U);
    
	return 0;
}


