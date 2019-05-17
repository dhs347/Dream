int rev; //方向调节变量,0表示求最大,k个元素小根堆 
struct Heap{
	struct node{ ll d,id; };
	priority_queue <node> PQ;
	friend bool operator < (const node &a,const node &b) {
		return (a.d>b.d || a.d==b.d && a.id<b.id);
	}
	void Init(int k){
		while (!PQ.empty()) PQ.pop();
		rep(i,1,k) PQ.push(node{-1,0});
	}
	void I(ll d,ll id) { node tt=node{d,id}; if ((tt<PQ.top())) PQ.pop(),PQ.push(tt); }
};

int cur;
struct KDT {
    int ans,n,root; Heap H;
    struct P{
    	ll mn[2],mx[2],d[2],key; int lch,rch;//key有时表编号 
    	ll& operator[](int x) { return d[x]; }
    	P(ll x=0,ll y=0,ll h=0) { d[0]=x,d[1]=y,key=h; rep(i,0,1) mx[i]=mn[i]=d[i]; lch=rch=0; }
    	friend bool operator<(P x,P y) { return x[cur]<y[cur]; }
    	friend ll dis(P x,P y) { return sqr(x[0]-y[0])+sqr(x[1]-y[1]); }  
	} t[N],p[N],T;
    inline void Init(){ n=0; }
	void insert(int &k,int now) {
		if (!k) { t[k=++n]=T; return; }
		if (T[now]<t[k][now]) insert(t[k].lch,now^1); else insert(t[k].rch,now^1); push_up(k); 
	}
    inline void I(ll x,ll y,ll key,int op=0) { 
		if (!op) { p[++n]=P(x,y,key); return; } T=P(x,y,key),insert(root,0);
	}
    inline void push_up(int k) {
        int l=t[k].lch,r=t[k].rch;
        rep(i,0,1){
            t[k].mn[i]=t[k].mx[i]=t[k][i];
            if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]),t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
    }
    int B(int l,int r,int op) { 
        if (l>r) return 0; cur=op; int mid=(l+r)/2;  
        nth_element(p+l,p+mid,p+r+1); t[mid]=p[mid];
        t[mid].lch=B(l,mid-1,op^1),t[mid].rch=B(mid+1,r,op^1);
		push_up(mid); return mid;
    }
    inline void Build(){ root=B(1,n,0); }
    ll getmn(P x) {
        ll ans=0;
        rep(i,0,1) ans+=sqr(max(T[i]-x.mx[i],0)+max(x.mn[i]-T[i],0));  
        return ans;
    }
    ll getmx(P x){
        ll ans=0;
        rep(i,0,1) ans+=max(sqr(T[i]-x.mn[i]),sqr(T[i]-x.mx[i]));
        return ans;
    }
    void Q_max(int k) {
        H.I(dis(t[k],T),t[k].key);  // ...前面加if带限制
        int l=t[k].lch,r=t[k].rch; ll dl=-ooo,dr=-ooo;
        if (l) dl=getmx(t[l]); if (r) dr=getmx(t[r]);
        if (dl>dr) { if (dl>H.PQ.top().d) Q_max(l); if (dr>H.PQ.top().d) Q_max(r); }
              else { if (dr>H.PQ.top().d) Q_max(r); if (dl>H.PQ.top().d) Q_max(l); }
    }
    void Q_min(int k){
        /*if (dis(t[k],T)) */ H.I(dis(t[k],T),t[k].key); // ...
        int l=t[k].lch,r=t[k].rch; ll dl=ooo,dr=ooo;
        if (l) dl=getmn(t[l]); if (r) dr=getmn(t[r]);
        if (dl<dr) { if (dl<H.PQ.top().d) Q_min(l); if (dr<H.PQ.top().d) Q_min(r); } 
              else { if (dr<H.PQ.top().d) Q_min(r); if (dl<H.PQ.top().d) Q_min(l); }
    }
    inline ll Query(int op,ll x,ll y,int k) { // op=0为最大值
        T[0]=x,T[1]=y; T.lch=T.rch=0;  rev=2*op-1,H.Init(k);
        if (!op) Q_max(root); else Q_min(root); 
        return H.PQ.top().id;
    }
};
//千万注意当前点（重合点），在不在计算范围之内
