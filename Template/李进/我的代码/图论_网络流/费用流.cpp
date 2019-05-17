const int max_node = 100000;
const int max_edge = 100000;

// 建第 i 条边时, 2*i为正向边, 2*i^1为反向边, 反向边的 cap 为 0, cost 为负值
// 无向图两条边的 cap 和 cost 相同
struct Edge{
    int to, cap, cost;
    int ne;
}ed[max_edge*2];
int head[max_node];
int es;

void addedge(int from,int to,int cap,int cost){
    ed[es].to = to;
    ed[es].cap = cap;
    ed[es].cost = cost;
    ed[es].ne = head[from];
    head[from] = es++;
}

int S,T;

struct zkw_wkz{
    int flow,cost;
    int D[max_node],V[max_node];

    int aug(int x,int fl){
        V[x]=1;
        if(x==T) return cost+=-D[S]*fl, flow+=fl, fl;
        int p,y,tp;
        for(p=head[x];p!=-1;p=ed[p].ne)
        if(ed[p].cap && !V[y=ed[p].to] && D[x]+ed[p].cost-D[y]==0)
            if(tp=aug(y,min(fl,ed[p].cap))) return ed[p].cap-=tp, ed[p^1].cap+=tp, tp;
        return 0;
    }

    bool mdf(){
        if(V[T]==1) return 1;
        int i,x,y,z=INF;
        for(i=0;i<es;i++)
            if(ed[i].cap&&V[x=ed[i^1].to]&&!V[y=ed[i].to]) z=min(z,D[x]+ed[i].cost-D[y]);
        if(z==INF) return 0;
        for(i=0;i<=T;i++) if(V[i]) D[i]-=z;
        return 1;
    }

    int solve(){
        flow=0, cost=0;
        memset(D,0,sizeof D);
        do memset(V,0,sizeof V),aug(S,INF); while(mdf());
        return cost;
    }
}zkw;