int cur;
struct KDT {
    int ans,n,root;
    struct P{
    	int mn[2],mx[2],d[2],lch,rch;
    	int& operator[](int x) { return d[x]; }
    	friend bool operator<(P x,P y) { return x[cur]<y[cur]; }
    	friend int dis(P x,P y) { return abs(x[0]-y[0])+abs(x[1]-y[1]); }  
	} t[N],p[N],T;
    inline void Init(){ n=0; }
	void insert(int k,int now) {
		if (T[now]>=t[k][now]){
            if (t[k].rch) insert(t[k].rch,now^1); else{
                t[k].rch=++n;t[n]=T;  
                rep(i,0,1) t[n].mx[i]=t[n].mn[i]=t[n][i];  
            }
        } else {
        if (t[k].lch) insert(t[k].lch,now^1); else {  
            t[k].lch=++n;t[n]=T;  
            rep(i,0,1) t[n].mx[i]=t[n].mn[i]=t[n][i];  
        } }
        push_up(k);
	}
    inline void I(int x,int y,int op=0) { 
		if (!op) { p[++n][0]=x,p[n][1]=y; return; }
		T[0]=x,T[1]=y; insert(root,T.lch=T.rch=0);
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
        cur=op; int mid=(l+r)/2;  
        nth_element(p+l,p+mid,p+r+1);
        t[mid]=p[mid];
        rep(i,0,1) t[mid].mx[i]=t[mid].mn[i]=t[mid][i];
        if (l<mid) t[mid].lch=B(l,mid-1,op^1);
        if (r>mid) t[mid].rch=B(mid+1,r,op^1);
        push_up(mid); return mid;
    }
    inline void Build(){ root=B(1,n,0); }
    int getmn(P x) {
        int ans=0;
        rep(i,0,1) ans+=max(T[i]-x.mx[i],0)+max(x.mn[i]-T[i],0);  
        return ans;
    }
    int getmx(P x){
        int ans=0;
        rep(i,0,1) ans+=max(abs(T[i]-x.mn[i]),abs(T[i]-x.mx[i]));
        return ans;
    }
    void Q_max(int k) {
        ans=max(ans,dis(t[k],T));  // ...
        int l=t[k].lch,r=t[k].rch,dl=-oo,dr=-oo;
        if (l) dl=getmx(t[l]); if (r) dr=getmx(t[r]);
        if (dl>dr) { if (dl>ans) Q_max(l); if (dr>ans) Q_max(r); }
              else { if (dr>ans) Q_max(r); if (dl>ans) Q_max(l); }
    }
    void Q_min(int k){
        /*if (dis(t[k],T)) */ ans=min(ans,dis(t[k],T)); // ...
        int l=t[k].lch,r=t[k].rch,dl=oo,dr=oo;
        if (l) dl=getmn(t[l]); if (r) dr=getmn(t[r]);
        if (dl<dr) { if (dl<ans) Q_min(l); if (dr<ans) Q_min(r); } 
              else { if (dr<ans) Q_min(r); if (dl<ans) Q_min(l); }
    }
    inline int Query(int op,int x,int y) { // op=0为最大值
        T[0]=x,T[1]=y; T.lch=T.rch=0; 
        if (!op) ans=-oo,Q_max(root); else ans=oo,Q_min(root); 
        return ans;
    }
};
//千万注意当前点（重合点），在不在计算范围之内