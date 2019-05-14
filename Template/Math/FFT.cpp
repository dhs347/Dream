const int M = 1<<16;
const db pi = acos(-1);

struct vir{
	db r, i;
	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
	void print() {printf("%lf %lf\n", r, i);}
} a[M*2], b[M*2], W[2][M*2];

vir operator +(const vir &a, const vir &b) {return vir(a.r + b.r, a.i + b.i);}
vir operator -(const vir &a, const vir &b) {return vir(a.r - b.r, a.i - b.i);}
vir operator *(const vir &a, const vir &b) {return vir(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}

struct FFT{
	int N, na, nb, rev[M*2];
	void fft(vir *a, int f){
		vir x, y;
		rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < N; i <<= 1)
			for (int j = 0, t = N/(i<<1); j < N; j += i<<1)
				for (int k = 0, l = 0; k < i; k++, l += t) 
					x = W[f][l] * a[j+k+i], y = a[j+k], a[j+k] = y+x, a[j+k+i] = y-x;
		if (f) rep(i, 0, N) a[i].r /= N;
	}
	void work(){
		rep(i, 0, N){
			int x = i, y = 0;
			for (int k = 1; k < N; x >>= 1, k <<= 1) (y<<=1)|=x&1;
			rev[i] = y;
		}
		rep(i, 0, N) {
			W[0][i] = vir(cos(2*pi*i/N), sin(2*pi*i/N));
			W[1][i] = vir(cos(2*pi*i/N), -sin(2*pi*i/N));
		}
	}	
	void doit(vir *a, vir *b, int na, int nb){
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = vir(0, 0);
		rep(i, nb, N) b[i] = vir(0, 0);
		work(), fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
		//rep(i, 0, N) a[i].print();
	}
} fft;



