struct Treap{
    int ch[N<<1][2],sz[N<<1],key[N<<1],val[N<<1],lazy[N<<1],cnt,a,b,c,d;
	inline void Init() { mem(ch,0),mem(sz,0),mem(val,0),mem(lazy,0); cnt=0; }
	inline int new_node(int v) { ++cnt,key[cnt]=rand()*70000+rand(),val[cnt]=v,sz[cnt]=1; return cnt; }
    inline int push_up(int x){ sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1; }
    inline void push_down(int x){
    	if (!lazy[x]) return;
    	for (int i=0;i<=1;++i) val[ch[x][i]]+=lazy[x],lazy[ch[x][i]]+=lazy[x];
        lazy[x]=0,push_up(x);
    }
    int Merge(int &pos,int x,int y){
        if (!x||!y) return pos=x+y;
        push_down(x),push_down(y);
        if (key[x]>key[y]) pos=x,Merge(ch[x][1],ch[x][1],y);
        else pos=y,Merge(ch[y][0],x,ch[y][0]);
        push_up(pos); return pos;
    }
    void Cut(int x,int &t0,int &t1,int s,int op=0){
        if (!x) { t0=t1=0; return; }
        push_down(x);
        if (op?sz[ch[x][0]]+1<=s:val[x]<s) t0=x,Cut(ch[x][1],ch[x][1],t1,op?s-sz[ch[x][0]]-1:s,op);
        else t1=x,Cut(ch[x][0],t0,ch[x][0],s,op);
        push_up(x);
    }
	inline void extract(int x,int l,int r,int &L,int &M,int &R,int op=0) {
		if (!op) Cut(x,L,M,l),Cut(M,M,R,r); else Cut(x,L,M,l-1,1),Cut(M,M,R,r-l,1);
	}
	int Del(int &x,int l,int r,int op=0) {
		extract(x,l,r,a,b,c,op); return Merge(x,a,c);
	}
	int Update(int &x,int l,int r,int num,int op=0) {
		extract(x,l,r,a,b,c,op); if (b) val[b]+=num,lazy[b]+=num; return Merge(x,a,Merge(b,b,c));
	}
	int Insert(int &x,int pos,int t,int op=0) {
		Cut(x,a,b,pos,op); return Merge(x,a,Merge(b,t,b));
	}
};
