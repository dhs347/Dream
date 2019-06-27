namespace GaussDB{
	static const int N = 505;
	db a[N][N], x[N]; //增广矩阵和解集
	int free[N], fnum, k, col, p; // 一组合法自由变元 
	const db eps = 1e-14;
	
	void genx() {
		int pre = var; fnum = 0;
		per(i, 0, k) {
			rep(j, 0, var) if (fabs(a[i][j]) > eps) { p = j; break; }
			rep(j, 0, i) if (fabs(a[j][p]) > eps) {
				db t = a[j][p] / a[i][p];
					rep(l, p, var+1) a[j][l] -= a[i][l] * t;
			}
			rep(j, p+1, pre) free[fnum++] = j, x[j] = (?); pre = p; 
			x[p] = a[i][var];
			rep(j, p+1, var) x[p] -= a[i][j] * x[j];
			x[p] /= a[i][p];
		}
		rep(j, 0, pre) free[fnum++] = j;
	}
	
	int Gauss(int equ, int var){
		for(k = col = 0; k < equ && col < var; ++k, ++col){
			p = k; rep(i, k+1, equ) if(fabs(a[i][col]) > fabs(a[p][col])) p = i;
			if (p != k) rep(j, col, var+1) swap(a[p][j], a[k][j]);
			if(fabs(a[k][col]) < eps) {k--; continue;}
			rep(i, k+1, equ){
				if (fabs(a[i][col]) < eps) continue;
				db t = a[i][col] / a[k][col];
				rep(j, col, var+1) a[i][j] -= a[k][j] * t;
			}
		}
		rep(i, k, equ) if (fabs(a[i][var]) > eps) return -1;//无解
		if(k < var){
			// genx();
			return var - k;//自由变元个数
		}
		per(i, 0, var) {
			db t = a[i][var];
			rep(j, i+1, var) if (fabs(a[i][j]) > eps) t -= x[j] * a[i][j];
			x[i] = t / a[i][i];
		}
		return 0;
	}
}
