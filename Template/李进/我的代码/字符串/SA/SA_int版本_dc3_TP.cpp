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
	int sa[4*N+5],R[N],H[N],h[N],n,m,cnt,str_cnt,num0; int *s; int num[1005],home[N]; TP T; int cpos,inx[N],temp[N],flow[N]; 
	#define F(x) ((x)/3+((x)%3==1?0:tb))
	#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
	int wa[4*N+5],wb[4*N+5],wv[4*N+5],ws[4*N+5];
	int c0(int *r,int a,int b) { return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2]; }
	int c12(int k,int *r,int a,int b) {
		if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
		else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
	}
	void sort(int *r,int *a,int *b,int n,int m) {
		int i; for(i=0; i<n; i++) wv[i]=r[a[i]];
		for(i=0; i<m; i++) ws[i]=0;
		for(i=0; i<n; i++) ws[wv[i]]++;
		for(i=1; i<m; i++) ws[i]+=ws[i-1];
		for(i=n-1; i>=0; i--) b[--ws[wv[i]]]=a[i];
	}
	void dc3(int *r,int *sa,int n,int m) {
		int i,j,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p; int *rn=r+n; r[n]=r[n+1]=0;
		for(i=0; i<n; i++) if(i%3!=0) wa[tbc++]=i;
		sort(r+2,wa,wb,tbc,m);
		sort(r+1,wb,wa,tbc,m);
		sort(r,wa,wb,tbc,m);
		for(p=1,rn[F(wb[0])]=0,i=1; i<tbc; i++)
			rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
		if(p<tbc) dc3(rn,san,tbc,p);
		else for(i=0; i<tbc; i++) san[rn[i]]=i;
		for(i=0; i<tbc; i++) if(san[i]<tb) wb[ta++]=san[i]*3;
		if(n%3==1) wb[ta++]=n-1;
		sort(r,wb,wa,ta,m);
		for(i=0; i<tbc; i++) wv[wb[i]=G(san[i])]=i;
		for(i=0,j=0,p=0; i<ta && j<tbc; p++)
			sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
		for(; i<ta; p++) sa[p]=wa[i++];
		for(; j<tbc; p++) sa[p]=wb[j++];
	}
	inline void init_sa(){ s[n]=0; dc3(s,sa,n+1,m); rep(i,0,n-1) sa[i]=sa[i+1]; }
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=0; s[n]=m-1;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	inline void Cut(int len){ while (cpos && H[inx[cpos]]>=len) T.D(inx[cpos--]); }
	inline bool check_len(int len) { return true; }//...
	inline ll Core() {
		cpos=n-1; ll ans=0; T.Init(n);
		mem(temp,0); mem(flow,0); rep(i,1,n-1) temp[H[i]]++;
		rep(i,1,n) temp[i]+=temp[i-1];
		rep(i,1,n-1) {
			int t=H[i] ? temp[H[i]-1]+1 : 1;
			inx[t+(flow[t]++)]=i;
		}
		per(i,n,0) { Cut(i); if (check_len(i)) ans+=T.ans0; } return ans;
	}
	inline void Q(){
		//...
	}
	inline void Insert(int _s[],int op,int _n){
		if (n) home[n]=0,s[n++]=505+str_cnt+1; ++str_cnt;
		if (!op) rep(i,0,_n-1) home[n]=str_cnt,s[n++]=_s[i]; else
				 per(i,_n-1,0) home[n]=str_cnt,s[n++]=_s[i];
	}
	SA(){ s=new int[4*N+5]; }
	inline void Clear() { n=str_cnt=0; }
	inline void Init(int _s[]=NULL,int _n=0,int _m=505+1005){
		if (_s!=NULL) s=_s,n=_n;  m=_m;
		init_sa(); init_H();
	}
};
