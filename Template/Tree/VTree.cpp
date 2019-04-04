namespace Vtree{// some nodes remain
    const int N = 101010;
    int tp[N] , _;
    vi g[N];// nodes sorted in dfs order
    void solve(vi&v,LCARMQ&R){
        _ = 0;
        vi del;del.pb(tp[_++] = v[0]);
        rep(i,1,sz(v)){
            int lca = R.lca(tp[_-1] , v[i]);
            vi l;while(_ > 0 && R.dep[lca] < R.dep[tp[_-1]]) l.pb(tp[--_]);
            if(_ == 0 || lca != tp[_-1]) del.pb(tp[_++] = lca);
            l.pb(tp[_-1]);del.pb(tp[_++] = v[i]);
            rep(i,1,sz(l)) g[l[i]].pb(l[i-1]);
        }
        rep(i,0,_-1) g[tp[i]].pb(tp[i+1]);
        // root = tp[0]
        // dfs()
        for(auto t : del){
            // Cal()
            g[t].clear();
        }
    }
}

