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

const int M=1<<15;
int k,n,p[25],V[25],x; double f[105][M+5];

int main() {
	//file_put();
    
    std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>k>>n;
	rep(i,1,n+1) {
	    cin>>p[i]>>x;
	    while (x) V[i]|=1<<x-1,cin>>x;
    }
	rep(i,1,k+1) rep(s,0,M) {
	    rep(x,1,n+1) {
	        double ret=f[i-1][s];
	        if ((s&V[x])==V[x]) ret=max(ret,f[i-1][s|1<<x-1]+p[x]);
	        f[i][s]+=1.0*ret/n;
        }
    }
	
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cout << f[k][0] << endl;
	
	return 0;
}

