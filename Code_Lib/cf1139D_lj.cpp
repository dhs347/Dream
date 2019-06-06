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

const int N=1e5+5,P=1e9+7;
int m,mu[N]; ll ret=1,p,_m;

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,(x*=x)%=P) if (k&1) (ret*=x)%=P;
    return ret;
}

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

    cin>>m,mu[1]=1,_m=Pow(m,P-2);
    rep(i,1,m+1) for (int j=i+i; j<=m; j+=i) mu[j]-=mu[i];
    rep(k,2,m+1) p=m/k*_m%P,ret-=mu[k]*p%P*Pow(1-p,P-2)%P,ret%=P;
    if (ret<0) ret+=P;
    cout<<ret<<endl; 

	return 0;
}

