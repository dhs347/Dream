int cur,rb_cnt=5000;
struct KDT {
    int n,root,rb_time; int ans,a,b;
    ll mx[N],add[N],cover[N],_mx[N],_add[N],_cover[N],x,y;
    struct P{
    	int mn[2],mx[2],d[2],lch,rch,id; ll key,_mx;
    	int& operator[](int x) { return d[x]; }
    	P(int x=0,int y=0,int h=0,int c=0,int _id=0) { d[0]=x,d[1]=y,key=h,_mx=c; id=_id; rep(i,0,1) mx[i]=mn[i]=d[i]; lch=rch=0; }
    	inline friend bool operator<(const P &x,const P &y) { return x[cur]<y[cur]; }
    	inline friend bool operator==(const P &x,const P &y) { return x[0]==y[0] && x[1]==y[1]; }
    	inline friend int dis(P x,P y) { return abs(x[0]-y[0])+abs(x[1]-y[1]); }
	} t[N],p[N],T;
    inline void Init(){ n=0; rb_time=rb_cnt; }
    inline bool check(int x,int y) { return x<=a && y>=b; }
    inline bool in(int x1,int y1,int x2,int y2){ return check(x1,y1) && check(x2,y2); }
    inline bool out(int x1,int y1,int x2,int y2){ !check(x1,y1) && !check(x1,y2) && !check(x2,y1) && !check(x2,y2); }
    inline void init_t(int k) { mx[k]=_mx[k]=t[k]._mx; add[k]=_add[k]=0; cover[k]=_cover[k]=-oo; }
	void insert(int &k,int now) {
		if (!k) { t[k=++n]=T; init_t(n); return; }
		if (T==t[k]) { t[k].key+=T.key; t[k]._mx=max(t[k]._mx,t[k].key); return; }
		if (T[now]<t[k][now]) insert(t[k].lch,now^1); else insert(t[k].rch,now^1); push_up(k);
	}
    inline void I(int x,int y,int id,int key=0,int c=0,int op=0) {
		if (!op) { p[++n]=P(x,y,key,c,id); init_t(n); return; }
		T=P(x,y,key,c,id); insert(root,0); if (n>=rb_time) ReBuild();
	}
    inline void push_up(int k) {
        int l=t[k].lch,r=t[k].rch;
        rep(i,0,1){
            t[k].mn[i]=t[k].mx[i]=t[k][i];
            if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
        //t[k].sum=t[l].sum+t[r].sum+t[k].key;
        mx[k]=t[k].key,_mx[k]=t[k]._mx;
		if (l) mx[k]=max(mx[k],mx[l]),_mx[k]=max(_mx[k],_mx[l]);
		if (r) mx[k]=max(mx[k],mx[r]),_mx[k]=max(_mx[k],_mx[r]);
    }
	inline void pd(int k,int f){
		_mx[k]=max(_mx[k],max(_cover[f],mx[k]+_add[f]));
		if (cover[k]==-oo) _add[k]=max(_add[k],add[k]+_add[f]);
		else _cover[k]=max(_cover[k],cover[k]+_add[f]);
		if (add[f]) {
			if (cover[k]!=-oo) cover[k]+=add[f]; else add[k]+=add[f];
			mx[k]+=add[f];
		}
		if (cover[f]!=-oo) mx[k]=cover[k]=cover[f],add[k]=0;
		_cover[k]=max(_cover[k],max(cover[k],_cover[f]));
		_add[k]=max(_add[k],add[k]);
		t[k].key+=_add[f]; t[k]._mx=max(t[k]._mx,t[k].key);
		if (_cover[f]==-oo) return ;
		t[k].key=_cover[f]; t[k]._mx=max(t[k]._mx,_cover[f]);
	}
	inline void push_down(int k) {
		pd(t[k].lch,k),pd(t[k].rch,k); add[k]=_add[k]=0; cover[k]=_cover[k]=-oo;
	}
    int B(int l,int r,int op) {
        if (l>r) return 0; cur=op; int mid=(l+r)/2;
        nth_element(p+l,p+mid,p+r+1); t[mid]=p[mid]; init_t(mid);
        t[mid].lch=B(l,mid-1,op^1),t[mid].rch=B(mid+1,r,op^1);
		push_up(mid); return mid;
    }
    inline void Build(){ root=B(1,n,0); }
	inline void ReBuild() { dfs_print(root); rep(i,1,n) p[i]=P(t[i][0],t[i][1],t[i].key,t[i].id,t[i]._mx); Build(); rb_time+=rb_cnt; }
    void Q(int k){
    	if (!k) return; if (t[k].lch || t[k].rch) push_down(k);
        if (out(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) return;
        if (in(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) { /*ans+=t[k].sum;*/ return ; }
        if (in(t[k][0],t[k][1],t[k][0],t[k][1])) ans+=t[k].key; Q(t[k].lch); Q(t[k].rch); push_up(k);
	}
	void U(int k){
		if (!k) return; if (t[k].lch || t[k].rch) push_down(k);
		if (in(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) {
			t[k].key+=x,t[k]._mx=max(t[k]._mx,t[k].key);
			mx[k]+=x,add[k]+=x,_add[k]+=x; _mx[k]=max(_mx[k],mx[k]); return ;
		}
		if (out(t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1])) {
			t[k].key=y,t[k]._mx=max(t[k]._mx,t[k].key);
			cover[k]=_cover[k]=mx[k]=y; _mx[k]=max(_mx[k],mx[k]); return ;
		}
		if (in(t[k][0],t[k][1],t[k][0],t[k][1])) t[k].key+=x; else t[k].key=y;
		t[k]._mx=max(t[k]._mx,t[k].key); U(t[k].lch); U(t[k].rch); push_up(k);
	}
	void dfs_print(int k,int op=0,ll ans[]=NULL){
		if (!k) return; if (t[k].lch || t[k].rch) push_down(k); if (op) { ans[t[k].id]=t[k]._mx; /*printf("ttt %d %d %d %d\n",k,t[k][0],t[k][1],t[k]._mx);*/ }
		dfs_print(t[k].lch,op,ans); dfs_print(t[k].rch,op,ans);
	}
	inline int Query(int _a,int _b) { a=_a,b=_b; ans=0; Q(root); return ans; }
	inline void Update(int _a,int _b,ll _x,ll _y) { a=_a,b=_b; x=_x,y=_y; U(root); }
};
