struct TwoSat {
    static const int N = ::N << 1;
    int dfn[N], low[N], id[N], st[N], _st, _, cc;
    vi g[N];
    int mark[N], n;
    void init(int _n) { per(i, 0, (n = _n << 1)) g[i].clear(); }
    int  new_node( ) { rep(i, 0, 2) g[n++].clear(); return n >> 1; }
    /// optionals begin
    void addedge(int a, int va, int b, int vb) { // va 选了 vb 必选  
		a = a << 1 | va; b = b << 1 | vb;
        g[a].pb(b); g[b ^ 1].pb(a ^ 1);
	}
    void add_set(int a, int va) { a = a << 1 | va; g[a ^ 1].pb(a); } // va 必选   
    
    void add_then(int a, int va, int b, int vb) { // va 和 vb 不能同时取
    	addedge(a, va, b, vb ^ 1); 
    }
    void add_or (int a, int va, int b, int vb) { // va 和 vb 不能同时不取 
    	addedge(a, va ^ 1, b, vb);
    }
    void add_xor(int a, int va, int b, int vb) { // va 和 vb 同时取或同时不取
        addedge(a, va, b, vb);
        addedge(b, vb, a, va);
    }
    // 需要 sz(vu) 个额外的 dp 变量
    void add_at_most_one(vector<pii> vu) {
        int pre = -1;
        rep(i, 0, sz(vu)) {
            int a = vu[i].fi, va = vu[i].se;
            int dpi = new_node();
            add_then(a, va, dpi, 1);
            if (i) {
                add_then(pre, 1, dpi, 1);
                add_then(pre, 1, a, va ^ 1);
            }
            pre = dpi;
        }
    }
    // optionals end

    void dfs(int c, vi g[]){
        dfn[c] = low[c] = ++cc;
        st[_st++] = c;
        for(auto t : g[c])
            if(!dfn[t])
                dfs(t, g), low[c] = min(low[c], low[t]);
            else if(!id[t])
                low[c] = min(low[c], dfn[t]);
        if(low[c] == dfn[c]){
            ++_;
            do{id[st[--_st]]=_;}while(st[_st] != c);
        }
    }
    void find(){
        fill_n(dfn,n,cc=0);
        fill_n(low,n,_st=0);
        fill_n(id,n,_=0);
        rep(i,0,n) if(!dfn[i]) dfs(i, g);
        rep(i,0,n) --id[i];
        return;
    }
    bool solve() { // 构造任意解 
        find();
        for (int i = 0; i < n; i += 2) {
            if (id[i] == id[i + 1]) return 0;
            mark[i >> 1] = (id[i] > id[i + 1]);
        }
        return 1;
    }
}  ts;
