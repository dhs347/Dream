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

const int N=100005;
char s[N],t[N];

int bat(char s[],int n){
	int ret=0;
	rep(i,0,n) ret+=(s[i]-'0')%3;
	return ret%3;
}

int T,n,m;
int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);

	scanf("%d",&T);
	while (T--) {
		scanf("%s%s",s,t),n=strlen(s),m=strlen(t);
		int a=bat(s,n),b=bat(t,m);
		a--; if (a<0) a+=3;
		if (a!=1) a=0;
		if (b!=1) b=0;
		int ret=b^a;
		printf("%d\n",ret);
	}

	return 0;
}
