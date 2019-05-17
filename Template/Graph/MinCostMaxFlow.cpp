 // [0,n) , init!! , inf modify
template<class U,class V>
struct MCMF{
    static const int N = 204 , M = 101010;
    int h[N] , ing[N] , pre[N] , to[M] , ne[M] , e , s , t , n;
    U cap[M];V dis[N] , cost[M];
    void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
    bool spfa(){
        queue<int> Q;
        fill(dis,dis+n,inf);
        ing[s] = true , dis[s] = 0;
        Q.push(s);
        while(!Q.empty()){
            int c = Q.front();Q.pop();ing[c] = false;
            for(int k=h[c];~k;k=ne[k]){
                int v = to[k];
                if(cap[k] <= 0) continue;
                if(dis[c] + cost[k] < dis[v]){
                    dis[v] = dis[c] + cost[k];
                    pre[v] = k;
                    if(!ing[v]) Q.push(v) , ing[v] = true;
                }
            }
        }
        return dis[t] != inf;
    }
    U flow;V mincost;
    pair<U,V> run(int _s,int _t){
        s = _s , t = _t;
        flow = mincost = 0;
        while(spfa()){
            U pl = inf;int p , k;
            for(p=t;p!=s;p=to[k^1]) pl = min(pl , cap[k=pre[p]]);
            for(p=t;p!=s;p=to[k^1]){
                k = pre[p];
                cap[k] -= pl;
                cap[k^1] += pl;
            }
            mincost += pl * dis[t];
            flow += pl;
        }
        return make_pair(flow , mincost);
    }
};
