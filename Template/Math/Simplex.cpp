const db EPS = 1e-8, DINF = 1e15;
struct Simplex {
	static const int M = 550;
	int n, m, B[M], N[M];
	db v, ans[M], b[M], c[M], A[M][M]; // 全幺模矩阵可以改整数 
	/* n - variables, m - equations
	*maxf(x)=cx
	*s.t.Ax<=b,x>=0 */
	void init(int _n, int _m) {
		n = _n, m = _m, v = 0;
		rep(i, 1, n + 1) N[i] = i;
		rep(i, 1, m + 1) B[i] = i + n;
	}
	inline int sgn(db x) { return (x > EPS) - (x < -EPS); }
	void pivot(int l, int e) {
		db tmp = A[l][e];
		b[l] /= tmp, A[l][e] = 1 / tmp;
		rep(i, 1, n + 1) if (i != e) A[l][i] /= tmp;
		rep(i, 1, m + 1) if (i != l && sgn(A[i][e])) {
			b[i] -= A[i][e] * b[l];
			rep(j, 1, n + 1) A[i][j] -= (j!=e) * A[i][e] * A[l][j];
			A[i][e] = - A[i][e] / tmp;
		}
		rep(i, 1, n + 1) c[i] -= (i!=e) * c[e] * A[l][i];
		v += b[l] * c[e]; c[e] *= -A[l][e]; swap(B[l], N[e]);
	}
	bool ini(){ // 随机化初始解 
    	while(1){
        	int l = -1, e = -1;
			rep(i, 1, m+1) if (sgn(b[i]) < 0 && (l == -1 || (rand() & 1))) l = i;
        	if(l == -1) break;
        	rep(j, 1, n+1) if (sgn(A[l][j]) < 0 && (e == -1 || (rand() & 1))) e = j;
        	if(e == -1) return 0;
        	pivot(l, e);
    	}
    	return 1;
	}
	db run() {
		//if (!ini()) return -DINF; // 无解  b < 0 need ini 
		rep(i, 1, n+1) ans[i] = 0; 
		while (1) {
			int r, l, e = -1;
			db delt = -DINF;
			rep(j, 1, n + 1) if (sgn(c[j]) > 0) { // 找非基变量 
				db tmp = DINF;
				rep(i, 1, m + 1) if (sgn(A[i][j]) > 0 && b[i] / A[i][j] < tmp) // 找基变量 
					r = i, tmp = b[i] / A[i][j];
				if (tmp == DINF) return DINF; // 无界 
				if (delt < tmp * c[j]) l = r, e = j, delt = tmp * c[j]; 
				break; 
				//贪心取最大 如果矩阵为全幺模或0很多可以加上break 因为转轴代价可能较小 
			}
			if (e == -1) break; // 找到最优解 
			pivot(l, e); 
		}
		rep(i, 1, m+1) if (B[i] <= n) ans[B[i]] = b[i];
		return v;
	}
} sp;
