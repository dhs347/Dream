template<class FL>
struct MF{
    static const int N = 100000, M = 100000;
    static const FL minf = 1e9;
    int head[N],p[N],d[N],gap[N],cur[N],to[M],nxt[M];
    bool vis[N]; int tot,s,t,n,u;
    FL cap[M],flow[M],mflow;
    inline void init(int _n){ n=_n; mem(head,-1); tot=0; }
    inline void add(int u,int v,FL c,FL _c=0){
        to[tot]=v;flow[tot]=0;cap[tot]=c;nxt[tot]=head[u];head[u]=tot++;
        to[tot]=u;flow[tot]=0;cap[tot]=_c;nxt[tot]=head[v];head[v]=tot++;
    }
    inline FL solve(int s,int t){
        mem(gap,0); mem(d,0); memcpy(cur, head, sizeof(head));
        p[u=s]=-1; gap[mflow=0]=n;
        while(d[s]<n){
            if(u == t){
                FL mi=minf;
                for(int i=p[u]; i!=-1; i=p[to[i^1]]) mi=min(mi,cap[i]-flow[i]);
                for(int i=p[u]; i!=-1; i=p[to[i^1]]) flow[i]+=mi,flow[i^1]-=mi;
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
            gap[d[u]]--; gap[d[u]=mi+1]++;
            if(!gap[d[u]])return mflow;
            if(u!=s) u=to[p[u]^1];
        }
        return mflow;
    }
};
