template<class FL>
struct UDKF{
    static const int N = 500;
    static const int M = 250000;
    static const FL minf = 1e9;
    int head[N],p[N],d[N],gap[N],cur[N],to[M],ne[M];
    int es,s,t,n;
    bool vis[N];
    FL cap[M],flow[M],mflow;
    FL in[N],du;
    void init(int _n){
        n=_n;
        memset(head,-1,sizeof(head));
        memset(in,0,sizeof(in));
        es=0;du=0;
    }
    void add(int u,int v,FL up,FL down){
        to[es]=v;flow[es]=0;cap[es]=up-down;ne[es]=head[u];head[u]=es++;
        to[es]=u;flow[es]=0;cap[es]=0;ne[es]=head[v];head[v]=es++;
        in[u]-=down;in[v]+=down;
    }
    void build(int _s,int _t){
        s=_s;t=_t;
        for(int i=0;i<=n;i++){
            if(in[i]>0){
                du+=in[i];
                add(s,i,in[i],0);
            }
            if(in[i]<0){
                add(i,t,-in[i],0);
            }
        }
    }
    int solve(int _s,int _t){
        s=_s;t=_t;
        memset(gap,0,sizeof(gap));
        memset(d,0,sizeof(d));
        memcpy(cur, head, sizeof(head));
        int u=s;
        p[u]=-1;
        gap[0]=n;
        mflow=0;
        while(d[s]<n){
            if(u == t){
                int mi=minf;
                for(int i=p[u]; i!=-1; i=p[to[i^1]]){
                    if(mi>cap[i]-flow[i]){
                        mi=cap[i]-flow[i];
                    }
                }
                for(int i = p[u]; i!=-1; i=p[to[i^1]]){
                    flow[i]+=mi;
                    flow[i^1]-=mi;
                }
                u=s;
                mflow+=mi;
                continue;
            }
            bool ok=false;
            int v;
            for(int i=cur[u]; i!=-1; i=ne[i]){
                v=to[i];
                if(cap[i]-flow[i] && d[v]+1==d[u]){
                    ok=true;
                    cur[u]=p[v]=i;
                    break;
                }
            }
            if(ok){
                u=v;
                continue;
            }
            int mi=n-1;
            for(int i=head[u]; i!=-1; i=ne[i]){
                if(cap[i]-flow[i] && d[to[i]] < mi){
                    mi=d[to[i]];
                    cur[u]=i;
                }
            }
            gap[d[u]]--;
            if(!gap[d[u]])return mflow;
            d[u] = mi+1;
            gap[d[u]]++;
            if(u!=s) u=to[p[u]^1];
        }
        return mflow;
    }
};
