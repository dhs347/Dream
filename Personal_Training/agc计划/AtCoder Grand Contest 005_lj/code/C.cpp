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

const int N=105; 
int n,a[N],L,R; map<int,int> M;

int main() {
//	file_put();
	
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",&a[i]),M[a[i]]++;
	R=M.rbegin()->fi,L=(R+1)/2;
	per(i,L+1,R+1) {
		M[i]-=2;
		if (M[i]<0) return 0*printf("Impossible\n");
	}
	M[L]-=(R&1)+1;
	if (M[L]) return 0*printf("Impossible\n");
	rep(i,1,n+1) if (a[i]<L) return 0*printf("Impossible\n");
	printf("Possible\n"); 
	
	return 0;
}

