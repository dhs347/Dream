template<class FL>
struct UDKF{
    static const int N = 500, M = 250000;
    static const FL minf = 1e9;
    int head[N],p[N],d[N],gap[N],cur[N],to[M],nxt[M];
    int es,s,t,n,u; bool vis[N];
    FL cap[M],flow[M],mflow; FL in[N],du;
    inline void init(int _n){ n=_n; mem(head,-1); mem(in,0); es=0,du=0; }
    inline void add(int u,int v,FL up,FL down){
        to[es]=v; flow[es]=0; cap[es]=up-down; nxt[es]=head[u]; head[u]=es++;
        to[es]=u; flow[es]=0; cap[es]=0; nxt[es]=head[v]; head[v]=es++;
        in[u]-=down; in[v]+=down;
    }
    inline void build(int _s,int _t){
        s=_s;t=_t;
        for(int i=0;i<=n;i++){
            if(in[i]>0) du+=in[i], add(s,i,in[i],0);
            if(in[i]<0) add(i,t,-in[i],0); 
        }
    }
    inline pair<FL,bool> solve(int _s,int _t){
        s=_s;t=_t; mem(gap,0); mem(d,0);
        memcpy(cur, head, sizeof(head));
        p[u=s]=-1; gap[mflow=0]=n;
        while(d[s]<n){
            if(u == t){
                int mi=minf;
                for(int i=p[u]; i!=-1; i=p[to[i^1]]) mi=min(mi,cap[i]-flow[i]);
                for(int i = p[u]; i!=-1; i=p[to[i^1]]) flow[i]+=mi, flow[i^1]-=mi;
                u=s; mflow+=mi; continue;
            }
            bool ok=false; int v;
            for(int i=cur[u]; i!=-1; i=nxt[i]){
                v=to[i];
                if(cap[i]-flow[i] && d[v]+1==d[u]){
                    ok=true; cur[u]=p[v]=i; break;
                }
            }
            if(ok){ u=v; continue; }
            int mi=n-1;
            for(int i=head[u]; i!=-1; i=nxt[i])
                if(cap[i]-flow[i] && d[to[i]] < mi)
                    mi=d[to[i]], cur[u]=i;
            gap[d[u]]--; gap[d[u] = mi+1]++;
            if(!gap[d[u]])return mflow;
            if(u!=s) u=to[p[u]^1];
        }
        return mp(mflow,mflow==du);
    }
};
