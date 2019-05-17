template<class FL,class CO>
struct MCMF{
    static const int N = 100000;
    static const int M = 100000;
    static const int minf = 1e9;
    int head[N],pre[N],to[M],ne[M];
    int es,s,t,n;
    bool vis[N];
    FL cap[M],mflow;
    CO cost[M],dis[N],mcost;
    void init(int _n){
        n=_n;
        memset(head,-1,sizeof(head));
        es=0;
    }
    void add(int u,int v,FL c,CO w){
        to[es]=v;cap[es]=c;cost[es]=w;ne[es]=head[u];head[u]=es++;
        to[es]=u;cap[es]=0;cost[es]=-w;ne[es]=head[v];head[v]=es++;
    }
    bool spfa(){
        for(int i=0;i<=n;i++){
            dis[i]=minf;
            vis[i]=false;
        }
        queue<int> Q;
        Q.push(s);
        vis[s]=true;
        dis[s]=0;
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();
            vis[u] = false;;
            for(int i = head[u]; i!=-1;i = ne[i]){
                int v = to[i];
                if(cap[i]>0 && dis[u] + cost[i] < dis[v]){
                    dis[v] = dis[u] + cost[i];
                    pre[v]=i;
                    if(!vis[v]){
                        vis[v] = true;
                        Q.push(v);
                    }
                }
            }
        }
        return dis[t]!=minf;
    }
    pair<FL,CO> solve(int _s,int _t){
        s=_s;t=_t;
        mflow=mcost=0;
        while(spfa()){
            FL tmp=minf;
            int v;
            for(int i=t;i!=s;i=to[v^1]){
                tmp=min(tmp,cap[v=pre[i]]);
            }
            for(int i=t;i!=s;i=to[v^1]){
                v=pre[i];
                cap[v]-=tmp;
                cap[v^1]+=tmp;
            }
            mcost+=tmp*dis[t];
            mflow+=tmp;
        }
        return make_pair(mflow,mcost);
    }
};
