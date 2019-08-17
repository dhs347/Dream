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

const int N=505;
int n,a[N*N],x[N],b[N*N],L,R,num[N];

void batL(int p,int x,int k) {
	for (; L<=p && k; ++L) if (!a[L]) a[L]=x,--k;
	if (k) {
		printf("No\n");
		exit(0);
	}
}

void batR(int p,int x,int k) {
	for (; R>=p && k; --R) if (!a[R]) a[R]=x,--k;
	if (k) {
		printf("No\n");
		exit(0);
	}
}

int main() {
//	file_put();
	
	scanf("%d",&n),R=n*n,L=1;
	rep(i,1,n+1) scanf("%d",&x[i]),a[x[i]]=b[x[i]]=i;
	rep(i,1,n*n+1) {
		if (!b[i]) continue;
		batL(i-1,b[i],b[i]-1);
	}
	per(i,1,n*n+1) {
		if (!b[i]) continue;
		batR(i+1,b[i],n-b[i]);
	}
	printf("Yes\n");
	rep(i,1,n*n+1) printf("%d%c",a[i]," \n"[i==n*n]);
	rep(i,1,n*n+1) {
		num[a[i]]++;
		if (b[i]) {
			assert(a[i]==b[i]);
			assert(num[a[i]]=b[i]);
		}
	}
	rep(i,1,n+1) assert(num[i]==n);
	
	return 0;
}

