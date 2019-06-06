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

const int N=2005,P=1e9+7;
int n,h,a[N],f[N][N];

int main() {
	//file_put();
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>h;
	rep(i,1,n+1) {
		cin>>a[i],a[i]=h-a[i];
		if (a[i]<0) return !puts("0");
	}
	f[0][0]=1;
	rep(i,0,n+1) rep(j,0,i+1) {
		if (a[i+1]==j+1) (f[i+1][j+1]+=f[i][j])%=P,(f[i+1][j]+=(ll)(j+1)*f[i][j])%=P; else
		if (a[i+1]==j) (f[i+1][j]+=f[i][j])%=P,j?(f[i+1][j-1]+=(ll)j*f[i][j]%P)%=P:0;
	}
	cout<<f[n][0]<<endl;
	
//	cout << setiosflags(ios::fixed);
//	cout << setprecision(3);

	return 0;
}
