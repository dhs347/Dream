namespace Vtree{
	const int N = ::N << 1;
	int tp[N], _, del[N], cntd, l[N], cntl;
	void solve(vi&v,LCARMQ&R){
		_ = cntd = 0; del[++cntd] = tp[_++] = v[0];
		rep(i, 1, sz(v)){
			int lca = R.lca(tp[_-1] , v[i]);
			cntl = 0; while(_ > 0 && R.dep[lca] < R.dep[tp[_-1]]) l[++cntl] = tp[--_];
			if(_ == 0 || lca != tp[_-1]) del[++cntd] = tp[_++] = lca;
			l[++cntl] = tp[_-1]; del[++cntd] = tp[_++] = v[i];
			rep(i, 2, cntl + 1) {
				int u = l[i], v = l[i - 1];
				// g[u].pb(v);
			}
		}
		per(i, 0, _ - 1) {
			int u = tp[i], v = tp[i + 1];
			// g[u].pb(v);
		}
		rep(i, 1, cntd + 1) {
			// del
		}
	}
}
