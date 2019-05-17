ll Mul_Mod(ll a, ll b, ll base) {
	ll ans = 0; a %= base,b %= base;
	for (ll now=b; a; a>>=1) {
		ans=(ans + now * (a&1)) %base;
		now=(now<<1) %base;
	}
	return ans;
}
