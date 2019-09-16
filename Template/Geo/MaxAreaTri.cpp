// O(n ^ 2)
void maxAreaTri(P *p, int n, P &a, P &b, P &c) {
	int i = 0, j = 1, k = 2;
	a = p[i], b = p[j], c = p[k];
	T res = area(a, b, c), cur = res, tmp;
	do {
		while(1) {
			while(cur <= (tmp = area(p[i], p[j], p[(k + 1) % n]))) (++k) %= n, cur = tmp;
			if(cur <= (tmp = area(p[i], p[(j + 1) % n], p[k]))) (++j) %= n, cur = tmp;
			else break;
		}
		if(cur > res) a = p[i], b = p[j], c = p[k], res = cur;
		(++i) %= n;
		if(i == j) (++j) %= n;
		if(j == k) (++k) %= n;
		cur = area(p[i], p[j], p[k]);
	} while(i);
}
