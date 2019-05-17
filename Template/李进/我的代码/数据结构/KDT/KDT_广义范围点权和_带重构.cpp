int cur,rb_cnt=5000;
struct KDT {
    int n,root,rb_time; int ans,a,b,c,d;
    struct P{
    	int mn[2],mx[2],d[2],lch,rch,key; int sum;
    	int& operator[](int x) { return d[x]; }
    	P(int x=0,int y=0,int h=0) { d[0]=x,d[1]=y,sum=key=h; rep(i,0,1) mx[i]=mn[i]=d[i]; lch=rch=0; }
    	inline friend bool operator<(P x,P y) { return x[cur]<y[cur]; }
    	inline friend bool operator==(P x,P y) { return x[0]==y[0] && x[1]==y[1]; }
    	inline friend int dis(P x,P y) { return abs(x[0]-y[0])+abs(x[1]-y[1]); }
	} t[N],p[N],T;
    inline void Init(){ n=0; rb_time=rb_cnt; }
    inline bool in(int x1,int y1,int x2,int y2){ return a<=x1 && x2<=c && b<=y1 && y2<=d; }
    inline bool out(int x1,int y1,int x2,int y2){ return x1>c || x2<a || y1>d || y2<b; }
	void insert(int &k,int now) {
		if (!k) { t[k=++n]=T; return; }
		if (T==t[k]) { t[k].key+=T.key,t[k].sum+=T.key; return; }
		if (T[now]<t[k][now]) insert(t[k].lch,now^1); else insert(t[k].rch,now^1); push_up(k); 
	}
    inline void I(int x,int y,int h,int op=0) { 
		if (!op) { p[++n]=P(x,y,h); return; } 
		T=P(x,y,h); insert(root,0); if (n>=rb_time) ReBuild();
	}
    inline void push_up(int k) {
        int l=t[k].lch,r=t[k].rch;
        rep(i,0,1){
            t[k].mn[i]=t[k].mx[i]=t[k][i];
            if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
        t[k].sum=t[l].sum+t[r].sum+t[k].key;
    }
    int B(int l,int r,int op) { 
        if (l>r) return 0; cur=op; int mid=(l+r)/2;  
        nth_element(p+l,p+mid,p+r+1); t[mid]=p[mid];
        t[mid].lch=B(l,mid-1,op^1),t[mid].rch=B(mid+1,r,op^1);
		push_up(mid); return mid;
    }
    inline void Build(){ root=B(1,n,0); }
	inline void ReBuild() { rep(i,1,n) p[i]=P(t[i][0],t[i][1],t[i].key); Build(); rb_time+=rb_cnt; }
    void Q(int k){
        if (!k || out(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) return;
        if (in(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) { ans+=t[k].sum; return ; }
        if (in(t[k][0],t[k][1],t[k][0],t[k][1])) ans+=t[k].key; Q(t[k].lch); Q(t[k].rch); 
	}
	inline int Query(int _a,int _b,int _c,int _d) { a=_a,b=_b,c=_c,d=_d; ans=0; Q(root); return ans; }
};
