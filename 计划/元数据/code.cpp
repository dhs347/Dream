# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define odd(x) ((x)&1)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define all(x) (x).begin(),(x).end()
#define mem(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for (int i=(a); i<=(b); ++i)
#define per(i,a,b) for (int i=(a); i>=(b); --i)
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int oo = /*2 * 1000 * 1000 * 1000*/0x3f3f3f3f;
const ll ooo=9223372036854775807ll; 
const int _cnt = 1000 * 1000 + 7;
const int _p = 1000 * 1000 * 1000 + 7;
const int N=100005; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int op=1;
const int M=100000,K=10,D=100;
typedef pair<string,double> psd;
vector<psd> A,B,C,ret; int m=0;
string s; double x,tt,ans=oo;

map<string,int> mm; int index=-1;
map<string,double> Dict;

double h(vector<psd> A,int K,int D) {
	mm.clear(); index=-1;
	double ret=0;
	int n=A.size(); 
	rep(i,0,n-1) {
		if (abs(A[i].sec-0.5)<=0.001) {
			if (index!=-1) if ((i-index)<=K) ret+=sqr((i-index)-K)*D;
			index=i;
		}
		double ex=Dict[A[i].fir];
		if (mm.count(A[i].fir)) {
			if (i-mm[A[i].fir]<=3) return +oo;
			ret+=sqr(abs(i-mm[A[i].fir]-ex))*8;
		}
		mm[A[i].fir]=i;
	} 
	return ret;
}

int main() {
    file_put();
    
    srand(time(0));
    while (cin>>s>>x) A.pb(mp(s,x)),m++;
    for (auto t:A) Dict[t.fir]=m/(t.sec+0.5);
    for (auto t:A) {
    	s=t.fir,x=t.sec;
    	while (x>=2) {
    		B.pb(mp(s,1));
    		x--;
		}
		B.pb(mp(s,x));
	}
	if (op) C=B; else C=A;
	rep(i,1,M) {
		random_shuffle(all(C));
		if ((tt=h(C,K,D))<ans) ans=tt,ret=C;
	}
	for (auto t:ret) printf("%s %.2lf\n\n",t.fir.c_str(),t.sec);
	debug(ans);
	
    return 0;
}

