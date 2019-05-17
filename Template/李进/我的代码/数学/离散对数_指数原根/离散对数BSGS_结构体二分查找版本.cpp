struct re {
	ll x;
	int id;
	bool operator < (const re & b) const {
		if (x == b.x)
			return id > b.id;
		return x < b.x;
	}
	bool operator == (const re & b) const {
		return x == b.x;
	}
} rec[100100];
ll bsgs(ll a, ll b, ll p) {
	int i;
	a %= p;
	ll m = ceil(sqrt(p));
	ll tmp, ans = b % p;
	for (i = 0; i <= m; ++i) {
		rec[i].id = i;
		rec[i].x = ans;
		ans = ans * a % p;
	}
	sort(rec, rec+1+m);
	int top = -1;
	for (i = 0; i <= 1+m; ++i)
		if (i == 0 || !(rec[i] == rec[i-1])) {
			rec[++top] = rec[i];
		} else {
			rec[top].id = max(rec[top].id, rec[i].id);
		}
	tmp = qm(a, m, p);
	ans = 1;
	int j;
	re tmp1;
	for (i = 1; i <= m; ++i) {
		ans = ans * tmp % p;
		tmp1.id = m+2;
		tmp1.x = ans;
		j = lower_bound(rec, rec+top, tmp1) - rec;
		if (rec[j].x == ans)
			return i * m - rec[j].id;
	}
	return -1;
}