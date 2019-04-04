# VTree

start time: 2019/4/2 15:15

end time: 2019/4/3 10:35

## 参考资料

[SDOI2011]消耗战 

[HNOI2014]世界树 

[zzq's blog](https://www.cnblogs.com/zzqsblog/p/5560645.html)

2014年 线段树在一类分治问题上的应用 ——徐寅展

## 模板

```c++
 // N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
    static const int N = 101010 << 1;
    int a[20][N] , lft[N] , dep[N] , lg[N] , L;
    int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
    void add(int x){ a[0][L++] = x;}
    void dfs(int c,int fa,const vi g[]){
        lft[c]=L;add(c);
        for(auto t : g[c]) if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
    }
    void Build(const vi g[]){
        L = 0;dfs(1,0,g);
        rep(i,2,L) lg[i]=lg[i>>1]+1;
        rep(i,1,20){
            int lim = L+1-(1<<i);
            rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
        }
    }
    int lca(int x,int y){
        x = lft[x] , y = lft[y];
        if(x > y) swap(x , y);
        int i = lg[y-x+1];
        return rmin(a[i][x] , a[i][y+1-(1<<i)]);
    }
};
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
```

