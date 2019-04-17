// desc : bud a cartesion tree from a[0] .. a[n - 1]
// time : O(N)
// !!!! : return rt, a[n] will be rewrite
int ls[N], rs[N];
int cartesionTree(int a[], int n) {
	a[n] = INT_MAX;
	vi v(1, n);
	fill_n(ls, n, -1), fill_n(rs, n, -1);
	rep(i, 0, n) {
		while (a[v.back()] < a[i])
			ls[i] = v.back(), v.pop_back();
		v.pb(rs[v.back()] = i);
	}
	return v[1];
}
