#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

void link(int x,int y,int id,int n) {
	x%=n,y%=n;
	while (x<=0) x+=n;
	while (y<=0) y+=n;
	cout<<id+x<<" "<<id+y<<endl;
}

bool check(int n,int k) {
	return k<=n-1 && (!((n&1) && (k&1)));
}

void build(int n,int k,int id) {
	if (k&1) rep(i,1,n/2+1) link(i,i+n/2,id,n);
	rep(t,1,n+1) rep(i,1,k/2+1) link(t,t+i,id,n); //link(t,t-i,id,n);
}

void build(int m,int n,int a,int b){
	int t=0;
	rep(i,1,m+1)
		rep(j,1,a+1) cout<<i<<" "<<m+((++t)-1)%n+1<<endl;
}

int a,b,c,d;

int main() {
	freopen("kids.in", "r", stdin);
	freopen("kids.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	cin>>a>>b>>c>>d;
	int g=__gcd(b,c);
	int n=b/g,m=c/g;
	rep(i,1,1e6) {
		int mm=m*i,nn=n*i;
		if (nn>=b && mm>=c && check(mm,a) && check(nn,d)) {
			cout<<mm<<" "<<nn<<endl;
			build(mm,a,0),build(nn,d,mm);
			build(mm,nn,b,c);
			return 0;
		}
	}

	return 0;
}
