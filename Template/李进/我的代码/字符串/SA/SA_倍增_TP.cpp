struct TP{
	int l[N],r[N],ans[N][3],len[N],n,cnt; ll ans0;
	inline void Init(int _n) {
		cnt=n=_n; ans0=0; rep(i,0,n) l[i]=i-1,r[i]=i+1,len[i]=1; l[0]=n,r[n]=0;
	}
	inline void M(int x,int y) { len[x]+=len[y]; } //...
	inline void C(int x,int op) {  } //...
	inline void D(int x) {
		C(l[x],-1); C(x,-1); M(l[x],x); C(l[x],1);
		r[l[x]]=r[x]; l[r[x]]=l[x]; --cnt;
	}
}; 

struct SA{
	int t1[N],t2[N],cc[N],x[N],sa[N],R[N],H[N],h[N],n,m,cnt,str_cnt,num0; char *s; int num[1005],home[N]; TP T; int cpos,inx[N],temp[N],flow[N]; //ST T;
	inline bool cmp(int *y,int a,int b,int k){
		return y[a]==y[b] && (a+k>=n ? -1:y[a+k])==(b+k>=n ? -1:y[b+k]);
	}
	inline void init_sa() {
		int *x=t1,*y=t2;
		rep(i,0,m-1) cc[i]=0;
		rep(i,0,n-1) ++cc[x[i]=s[i]];
		rep(i,1,m-1) cc[i]+=cc[i-1];
		per(i,n-1,0) sa[--cc[x[i]]]=i;
		for(int k=1,p=0; k<=n; k<<=1,p=0){
			rep(i,n-k,n-1) y[p++]=i;
			rep(i,0,n-1) if(sa[i]>=k) y[p++]=sa[i]-k;
			rep(i,0,m-1) cc[i]=0;
			rep(i,0,n-1) ++cc[x[y[i]]];
			rep(i,1,m-1) cc[i]+=cc[i-1];
			per(i,n-1,0) sa[--cc[x[y[i]]]]=y[i];
			swap(x,y),m=1,x[sa[0]]=0;
			rep(i,1,n-1) x[sa[i]]=cmp(y,sa[i],sa[i-1],k) ? m-1:m++;
			if(m>=n) break;
		}
	}
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=s[n]=0;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	inline void Cut(int len){ while (cpos && H[inx[cpos]]>=len) T.D(inx[cpos--]); }
	inline bool check_len(int len) { return true; } //...
	inline ll Core(int k) {
		cpos=n-1; ll ans=0; T.Init(n);
		mem(temp,0); mem(flow,0); rep(i,1,n-1) temp[H[i]]++;
		rep(i,1,n) temp[i]+=temp[i-1];
		rep(i,1,n-1) {
			int t=H[i] ? temp[H[i]-1]+1 : 1;
			inx[t+(flow[t]++)]=i;
		}
		per(i,n,0) { Cut(i); if (check_len(i)) ans+=T.ans0; } return ans;
	}
	inline ll Q(int k){
		//...
	}
	inline void Insert(char _s[],int op=0,int _n=0){
		if (n) home[n]=0,s[n++]=str_cnt+' '; if (!_n) _n=strlen(_s); ++str_cnt;
		if (!op) rep(i,0,_n-1) home[n]=str_cnt,s[n++]=_s[i]; else
				 per(i,_n-1,0) home[n]=str_cnt,s[n++]=_s[i];
	}
	SA(){ s=new char[N]; }
	inline void Clear() { n=str_cnt=0; }
	inline void Init(char _s[]=NULL,int _n=0,int _m='z'+1005){
		if (_s!=NULL) s=_s,n=_n ? _n : strlen(s);  m=_m;
		init_sa(); init_H(); 
	}
};
