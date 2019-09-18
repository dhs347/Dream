namespace Simpson {
	const db eps = 1e-10; // 精度感觉一般要多设1e-3左右
	inline db F(db x) { F(x) = (?) } 
	inline db simpson(db fa, db fb, db fc, db a, db c) {
		return (fa + 4 * fb + fc) * (c - a) / 6;
	}
	db asr(db a, db b, db c, db esp, db A, db fa, db fb, db fc) {
		db ab = (a + b) / 2, bc = (b + c) / 2;
		db fab = F(ab), fbc = F(bc);
		db L = simpson(fa, fab, fb, a, b), R = simpson(fb, fbc, fc, b, c);
		if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
		return asr(a, ab, b, esp / 2, L, fa, fab, fb) + asr(b, bc, c, esp / 2, R, fb, fbc, fc);
	} 
	//f(a, c)
	db asr(db a, db c, db eps) {
		db b = (a + c) / 2;
		db fa = F(a), fb = F(b), fc = F(c);
		return asr(a, b, c, eps, simpson(fa, fb, fc, a, c), fa, fb, fc);
	}
}
