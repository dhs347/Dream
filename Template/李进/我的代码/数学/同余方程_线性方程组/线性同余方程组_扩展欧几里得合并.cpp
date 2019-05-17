int n;
ll ans, a1, a2, a3, r1, r2, r3, x, y, tmp;
int main() {
	while (~scanf(”%d”, &n)) {
		--n;
		scanf(”%lld%lld”, &a1, &r1);
		ans = (r1 % a1 + a1) % a1;
		while (n--) {
			scanf(”%lld%lld”, &a2, &r2);
			if (ans == ?1)
				continue;
			tmp = exgcd(a1, a2, x, y);
			if ((r1 - r2) % tmp != 0) {
				ans = -1;
				continue;
			}
			x = x * (r2 - r1) / tmp;
			x = (x % a2 + a2) % a2;
			r1 = r1 + a1 * x;
			a1 = a1 * a2 / tmp;
			ans = (r1 % a1 + a1) % a1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
