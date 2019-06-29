#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N=2e6+5;
int x,y,n; double p[N][2];

int get(int k) {
	return k<=x?0:1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	cin>>x>>y;
	n=x+y;
	//rep(i,1,n+1) p[i][0]=p[i][1]=1;
	per(i,1,n+1) p[i][get(i)]=1;
	//per(i,1,n+1) if (i*2>n) p[i][get(i)^1]=0;
	per(i,1,n+1) {
		rep(j,0,2) //rep(c,0,2){
			p[i/2][j]=0.5*p[i][j]+0.5*p[i/2][j];
			//p[i/2][c]=0.5*p[i][j]+0.5*p[i/2][c];
		//}
	}
	cout<<setiosflags(ios::fixed);
	cout<<setprecision(12);
	cout<<p[1][1]<<endl;
	
	return 0;
}
