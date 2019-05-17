const int Times = 10;
const int N = 5500;
ll ct, cnt;
ll fac[N], num[N];
ll pollard_rho(ll n, ll c) {
	ll i = 1, k = 2;
	ll x = rand() % (n ? 1) + 1;
	ll y = x;
	while(true) {
		i++;
		x = (multi(x, x, n) + c) % n;
		ll d = gcd((y ? x + n) % n, n);
		if(1 < d && d < n) return d;
		if(y == x) return n;
		if(i == k) {
			y = x;
			k <<= 1;
		}
	}
}
void _find(ll n, int c) {
	if(n == 1) return;
	if(Miller_Rabin(n)) {
		fac[ct++] = n;
		return ;
	}
	ll p = n;
	ll k = c;
	while(p >= n) p = pollard_rho(p, c??);
	_find(p, k);
	_find(n / p, k);
}
int main() {
	ll n;
	while(cin>>n) {
		ct = 0;
		_find(n, 120);
		sort(fac, fac + ct);
		num[0] = 1;
		int k = 1;
		for(int i=1; i<ct; i++) {
			if(fac[i] == fac[i?1])
				++num[k?1];
			else {
				num[k] = 1;
				fac[k++] = fac[i];
			}
		}
		cnt = k;
		for(int i=0; i<cnt; i++) cout<<fac[i]<<”^”<<num[i]<<” ”;
		cout<<endl;
	}
	return 0;
}
