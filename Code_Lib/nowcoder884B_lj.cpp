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
#define mem(a,x) memset(a,x,sizeof(a))

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=400005;

struct SAM {
    static const int M=26; ll dp[N<<1],ans; set<int> SS[N<<1];
    int go[N<<1][M],pre[N<<1],step[N<<1],rr[N<<1],temp[N<<1],toop[N<<1],id[N<<1],dep[N<<1],str_cnt,cnt,S,T,n,p,q,nq;
    inline int h(int c) { return c-'a'; }
    inline int new_node(int _s,int c) { step[++cnt]=_s,pre[cnt]=dep[cnt]=0,rr[cnt]=c; /* */mem(go[cnt],0); return cnt; }
    inline void Init() { n=cnt=str_cnt=0,S=T=new_node(0,0); }
    inline void I(int c) {
        ++n,c=h(c),p=T,T=new_node(step[T]+1,c);
        for (; p && !go[p][c]; p=pre[p]) go[p][c]=T;
        if (!p) pre[T] = S; else {
            q=go[p][c];
            if (step[p]+1==step[q]) pre[T]=q; else {
                nq=new_node(step[p]+1,c);
                rep(j,0,M) go[nq][j] = go[q][j];
                for (; p && go[p][c] == q; p = pre[p]) go[p][c] = nq;
                pre[nq]=pre[q],pre[T]=pre[q]=nq;
            }
        }
        id[n]=T; SS[T].insert(str_cnt); //...
    }
    inline void Insert(const char s[],int _n=0,int op=0) {
        if (!_n) _n=strlen(s); ++str_cnt; T=S;
        if (!op) rep(i,0,_n) I(s[i]); else per(i,0,_n) I(s[i]);
    }
    inline void Go(int &p,int c) { while (p && !go[p][c]) p=pre[p]; if (p) p=go[p][c],ans+=dp[p]; }
    inline int Run(const char s[],int _n=0,int op=0) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op; ans=0;
        for (int i=p; i!=q; i+=op) if (pos) Go(pos,h(s[i])); else break; return pos;
    }
    inline int get_dep(int x) { return (!x || dep[x]) ? dep[x] : dep[x]=get_dep(pre[x])+1; }
    inline void Toop() {
        rep(i,0,n+1) temp[i]=0; rep(i,1,cnt+1) temp[get_dep(i)]++;
        rep(i,1,n+1) temp[i]+=temp[i-1]; per(i,1,cnt+1) toop[temp[dep[i]]--]=i;
    }
    inline ll Q() { 
        ll ans=0; rep(i,1,cnt+1) ans+=step[i]-step[pre[i]]; return ans;
    }//...
} T1;

const int M=26;
struct PAM{
	int s[N],len[N],next[N][M],fail[N],cnt[N],dep[N],id[N],no[N],last,n,p,cur,now; ll ans;
	inline int new_node(int _l) { mem(next[p],0); cnt[p]=dep[p]=0,len[p]=_l; return p++; }
	inline void Init() { new_node(p=0),new_node(s[0]=-1),fail[last=n=0]=1; }
	inline int get_fail(int x) { for (; s[n-len[x]-1]!=s[n]; x=fail[x]); return x; }
	inline void I(int c) { 
		c-='a',s[++n]=c,cur=get_fail(last);
		if (!next[cur][c]) {
			now=new_node(len[cur]+2);
			fail[now]=next[get_fail(fail[cur])][c];
			next[cur][c]=now;
			dep[now]=dep[fail[now]]+1; //...
		}
		last=next[cur][c],cnt[last]++; id[n]=last,no[last]=n; //...
	}
	inline void Insert(char s[],int op=0,int _n=0) { 
		if (!_n) _n=strlen(s);  if (!op) rep(i,0,_n) I(s[i]); else per(i,0,_n) I(s[i]); 
	}
	inline void count() { per(i,0,p) cnt[fail[i]]+=cnt[i]; }
	inline ll Q(){ return p-2; }
} T2;

char s[N]; ll p,q; int n;

int main() { 
//    file_put();

    scanf("%s",s),n=strlen(s);
    T1.Init(),T2.Init();
    T1.Insert(s,n),T1.Insert(s,n,1),T2.Insert(s);
    printf("%lld\n",T1.Q()+T2.Q()>>1);
    
	return 0;
}

