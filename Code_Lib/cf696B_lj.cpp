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

const int N=1e5+5;
int n,p[N],siz[N],dep[N],x; vi V[N];

void dfs(int x,int f) {
    dep[x]=dep[f]+1,siz[x]=1;
    for (auto y: V[x]) dfs(y,x),siz[x]+=siz[y]; 
}

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n;
	rep(i,2,n+1) cin>>x,V[x].pb(i);
	dfs(1,0);
    
    cout << setiosflags(ios::fixed);
	cout << setprecision(12);
	rep(i,1,n+1) cout<<((double)(n-siz[i]+dep[i]+1)/2)<<" ";
    cout<<endl; 
	
    return 0;
}

