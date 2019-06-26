namespace GaussInt{
	static const int N = ::N, P = 1e9 + 7;
	int a[N][N], x[N]; //增广矩阵和解集
	int free[N], fnum, k, col, p; // 一组合法自由变元 
	int add(int a, int b) {if ((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
	int mul(int a, int b) {return 1ll * a * b % P;}
	int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
	
	void genx() {
		int pre = var; fnum = 0;
		per(i, 0, k) {
			rep(j, 0, var) if (a[i][j]) { p = j; break; }
			rep(j, 0, i) if (a[j][p]) {
				int t = a[j][p];
				rep(l, p, var+1) a[j][l] = add(a[j][l], -mul(a[i][l], t));
			}
			rep(j, p+1, pre) free[fnum++] = j, x[j] = (?); pre = p; 
			x[p] = a[i][var];
			rep(j, p+1, var) x[p] = add(x[p], -mul(a[i][j], x[j]));
		}
		rep(j, 0, pre) free[fnum++] = j;
	}
	
	int Gauss(int equ, int var){
		for(k = col = 0; k < equ && col < var; ++k, ++col){
			p = k; rep(i, k, equ) if (a[i][col]) {p = i; break;}
			if (p != k) rep(j, col, var+1) swap(a[p][j], a[k][j]);
			if(!a[k][col]) {k--; continue;}
			int inv = kpow(a[k][col], P - 2);
			rep(i, col, var+1) a[k][i] = mul(a[k][i], inv);
			rep(i, k+1, equ) if (a[i][col]) {
				int t = a[i][col];
				rep(j, col, var+1) a[i][j] = add(a[i][j], -mul(a[k][j], t));
			}
		}
		rep(i, k, equ) if (a[i][var]) return -1;//无解
		if(k < var){
			//genx();
			return var - k;//自由变元个数
		}
		per(i, 0, var) {
			int t = a[i][var];
			rep(j, i+1, var) if (a[i][j]) t = add(t, -mul(a[i][j], x[j]));
			x[i] = t;
		}
		return 0;
	}
}
