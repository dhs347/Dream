const int M=26;
struct PAM{
	int s[N],len[N],next[N][M],fail[N],cnt[N],dep[N],id[N],no[N],last,n,p,cur,now; int df[N],slink[N],dp[N],res[N]; ll ans;
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
		last=next[cur][c],cnt[last]++; id[n]=last,no[last]=n; 
		df[last]=len[last]-len[fail[last]];
		slink[last]=(df[last]==df[fail[last]])?slink[fail[last]]:fail[last]; //...
	}
	inline void Insert(char s[],int op=0,int _n=0) { 
		if (!_n) _n=strlen(s);  if (!op) rep(i,0,_n-1) I(s[i]); else per(i,_n-1,0) I(s[i]); 
	}
	inline void count() { per(i,p-1,0) cnt[fail[i]]+=cnt[i]; }
	inline int Q() {
		rep(i,0,n+5) dp[i]=oo; dp[0]=0;
		rep(i,1,n) {
			for (int t=id[i]; len[t]>0; t=slink[t]) {
				res[t]=dp[i-len[slink[t]]-df[t]];
				if (df[t]==df[fail[t]]) res[t]=min(res[t],res[fail[t]]);
				dp[i]=min(dp[i],res[t]+1);
			}
		}
		return dp[n];
	}
}; 

/*

【题目】求给定串的最小回文切割段数
【注意】1.如果要求段的长度为奇数或偶数，在dp[]赋值语句前限制，请不要乱改自动机
        2.如果要求段数为奇数或偶数，dp和res开两维dp[i][0]表示段数为偶数的答案

*/