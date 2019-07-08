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
//#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

#define mem(a,x) memset(a,x,sizeof(a))

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

string ask() {
    cout<<"?"<<endl;
    string s;
    cin>>s;
    return s;
}

void print(const string &s,const string &t) {
    cout<<"! "<<s<<" "<<t<<endl;
}

const int N=105;
int n,k,q,num[105][2];
vector<string> v[2],V;
string ss,tt;

void Count(vector<string> V,int num[][2]) {
    rep(j,0,sz(V)) {
    	string t=V[j];
    	for (int i=0; i<sz(t); ++i) num[i][t[i]-'0']++;
	}
}

int dist(const string &s,const string &t) {
	int num=0;
	rep(i,0,n) num+=(s[i]!=t[i]);
	return num;
}

bool check(const string &p,const string &q) {
	for (int i=0; i<sz(V); i++) {
		string t=V[i];
		if (dist(p,t)!=k && dist(q,t)!=k) return 0;
	}
	return 1;
}

int main() {
	cin>>n>>k>>q;
	rep(ii,1,q+1) V.pb(ask());
	rep(ii,1,q+1) {
		string p=V[ii-1]; int no=0;
		int ans=dist(p,V[0]);
		for (int i=0; i<q; ++i) if (dist(V[i],p)>ans) 
			ans=dist(V[i],p),no=i; 
		v[0].clear();
		v[1].clear();
		string pp=p,qq=V[no];
		for (int i=0; i<sz(V); ++i) {
			if (dist(V[i],pp)<dist(V[i],qq)) v[0].pb(V[i]); else v[1].pb(V[i]);
		}
	    ss.resize(n),tt.resize(n);
	    mem(num,0),Count(v[0],num);
	    rep(i,0,n) ss[i]=(num[i][1]>=num[i][0])+'0';
	    mem(num,0),Count(v[1],num);
	    rep(i,0,n) tt[i]=(num[i][1]>=num[i][0])+'0';
	    if (ss>tt) swap(ss,tt);
	    if (check(ss,tt)) {
	    	print(ss,tt);
	    	return 0;
		}
	}
	
	return 0;
}

