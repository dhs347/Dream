// fill f -1 
ll f[];// 自顶向下限制
ll dfs(int pos, ..., bool lim){
	if(pos == -1) return ?;// ...
	if(!lim && ~f[...]) return f[...];
	ll res = 0;
	int up = lim ? dig[pos] : 9;//...
	rep(i,0,up+1) {
		if(..) res += dfs(pos - 1, ..., lim & (i == up));
	}
	if(!lim) f[]=res;
	return res;
}
ll solve(ll x){
	int pos=0;
	while(x) dig[pos++] = x % 10 , x /= 10;
	return dfs(pos-1, ... , 1);
}
