template<class FL,class CO>
struct MCMF{
    static const int N = 100000, M = 100000;
    static const CO minf = 1e9;
    int head[N],pre[N],to[M],nxt[M];
    bool vis[N]; int tot,s,t,n;
    FL cap[M],mflow; CO cost[M],dis[N],mcost;
    inline void init(int _n){ n=_n; mem(head,-1); tot=0; }
    inline void add(int u,int v,FL c,CO w,FL _c=0){
        to[tot]=v;cap[tot]=c;cost[tot]=w;nxt[tot]=head[u];head[u]=tot++;
        to[tot]=u;cap[tot]=_c;cost[tot]=-w;nxt[tot]=head[v];head[v]=tot++;
    }
    inline bool spfa(){
        rep(i,0,n) dis[i]=minf, vis[i]=false;
        queue<int> Q; Q.push(s); vis[s]=true; dis[s]=0;
        while(!Q.empty()){
            int u = Q.front(); Q.pop(); vis[u] = false;;
            for(int i = head[u]; i!=-1; i=nxt[i]){
                int v = to[i];
                if(cap[i]>0 && dis[u]+cost[i]<dis[v]){
                    dis[v]=dis[u]+cost[i]; pre[v]=i;
                    if(!vis[v]) vis[v] = true, Q.push(v);
                }
            }
        }
        return dis[t]!=minf;
    }
    inline pair<FL,CO> solve(int _s,int _t){
        s=_s;t=_t; mflow=mcost=0;
        while(spfa()){
            FL tmp=oo; int v;
            for(int i=t; i!=s; i=to[v^1]) tmp=min(tmp,cap[v=pre[i]]);
            for(int i=t; i!=s; i=to[v^1]) v=pre[i], cap[v]-=tmp, cap[v^1]+=tmp;
            mcost+=tmp*dis[t]; mflow+=tmp;
        }
        return mp(mflow,mcost);
    }
};
