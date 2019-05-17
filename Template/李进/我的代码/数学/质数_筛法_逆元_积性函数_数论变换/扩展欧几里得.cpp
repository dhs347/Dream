ll exgcd(ll a,ll b,ll &x,ll &y) {
	if (b == 0) { x = 1,y = 0; return a; }
	ll tmp = exgcd(b, a % b, y, x);
	y -= x * (a / b); 
	return tmp;
}
