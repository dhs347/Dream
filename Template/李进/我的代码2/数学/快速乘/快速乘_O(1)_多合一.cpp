ll mul(ll x,ll y,ll pp) {
	ll a=x>>20,b=x-(a<<20);
	ll c=y>>20,d=y-(c<<20);
	return ((((((a * c) << 20) + (a * d + b * c)) % pp) << 20) + b * d) % pp;
	//return x*y%pp;
	
	//return ((x*y-(ll)(((long double)x*y+0.5)/pp)*pp)%pp+pp)%pp;
}
