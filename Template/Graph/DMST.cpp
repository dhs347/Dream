// id starts from 0
// can handle multi edge, self ring
struct edge {int u, v, d, U, V;bitset<1005> b;};
struct DMST{
	static const int N = ::N , M = N * N , inf = 2e9;
	edge e[M];int n, m, vis[N], pre[N], id[N], index[N], Pre[N];
	bitset<1005> fang;
	int in[N];
	void ini(int n) {this->n = n, m = 0;}
	void addedge(int u, int v, int d) {e[m] = edge({u,v,d,u,v}); e[m].reset();e[m].b[m] = 1;m++;}
	int run(int root){
		int ans = 0;
		while(1){
			rep(i, 0, n) in[i] = inf;
			rep(i, 0, m){
				int u = e[i].u ,v = e[i].v;
				if(e[i].d < in[v] && u != v){
					in[v] = e[i].d, pre[v] = u; index[v] = i;
				}
			}
			rep(i, 0, n) {
				if(i == root) continue; 
				if(in[i] == inf) return -1;
				fang ^= e[index[i]].b;
			}
			int cnt = 0;in[root] = 0;
			memset(id, -1, sizeof(*id)*n);
			memset(vis, -1, sizeof(*vis)*n);
			rep(i, 0, n){
				ans += in[i]; int v = i;
				int t = index[i];
				while(vis[v] != i && id[v] == -1 && v!=root){
					vis[v] = i;v = pre[v];
				}
				if(v != root && id[v] == -1) {
					for(int u=pre[v];u != v;u = pre[u]) id[u] = cnt;
					id[v] = cnt++;
				}
			}
			if(cnt == 0) break;
			rep(i, 0, n) if(id[i] == -1) id[i] = cnt++;
			rep(i, 0, m) {
				int v=e[i].v;
				e[i].u = id[e[i].u]; e[i].v = id[e[i].v];
				if(e[i].u != e[i].v) {e[i].d -= in[v];e[i].b ^= e[index[v]].b;}
			}
			n = cnt; root = id[root];
		}
		return ans;
	}
} dmst;
