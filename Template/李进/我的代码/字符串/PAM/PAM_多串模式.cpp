const int M=26;
struct PAM{
	int s[N],len[N],next[N][M],fail[N],cnt[N][11],dep[N],id[N],no[N],last,n,p,cur,now,str_cnt,d0; ll ans;
	inline int new_node(int _l) { mem(next[p],0); mem(cnt[p],0); dep[p]=0,len[p]=_l; return p++; }
	inline void Init() { new_node(p=0),new_node(s[0]=-1),fail[last=n=0]=1; str_cnt=0; d0=-1;}
	inline int get_fail(int x) { for (; s[n-len[x]-1]!=s[n]; x=fail[x]); return x; }
	inline void I(int c) { 
		if (c<0) { s[++n]=c; last=1; return; }
		c-='a',s[++n]=c,cur=get_fail(last);
		if (!next[cur][c]) {
			now=new_node(len[cur]+2);
			fail[now]=next[get_fail(fail[cur])][c];
			next[cur][c]=now;
			dep[now]=dep[fail[now]]+1; //...
		}
		last=next[cur][c],cnt[last][str_cnt]++; id[n]=last,no[last]=n; //...
	}
	inline void Insert(char s[],int op=0,int _n=0) { 
		if (str_cnt) I(--d0); if (!_n) _n=strlen(s); 
		if (!op) rep(i,0,_n-1) I(s[i]); else per(i,_n-1,0) I(s[i]); ++str_cnt; 
	}
	inline void count() { per(i,p-1,0) rep(j,0,str_cnt-1) cnt[fail[i]][j]+=cnt[i][j]; }
	inline ll Q(){ count(); /* ... */}
};
