const int Times = 10;
bool Miller_Rabin(ll n) {
	if(n == 2) return true;
	if(n < 2 || !(n & 1)) return false;
	ll m = n ? 1;
	int k = 0;
	while((m & 1) == 0) k++,m >>= 1;
	for(int i=0; i<Times; i++) {
		ll a = rand() % (n ? 1) + 1;
		ll x = quick_mod(a, m, n),y = 0;
		for(int j=0; j<k; j++) {
			y = multi(x, x, n);
			if(y == 1 && x != 1 && x != n ? 1) return false;
			x = y;
		}
		if(y != 1) return false;
	}
	return true;
}

//如果 p 是素数，且 0 < x < p，则方程的解 x2 ≡ 1(mod p) 为 1 或 p − 1。