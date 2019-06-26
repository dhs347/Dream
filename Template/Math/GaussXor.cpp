//对 2 取模的 01 方程组
namespace Gauss{
	static const int N = 2e3 + 10;
	//有 equ 个方程， var 个变元。增广矩阵行数为 equ ,列数为 [0..var]
	bitset<N> a[N]; //增广矩阵 modif
	int x[N]; //解集
	int p, col, k; // k 为增广矩阵的秩
	int free[N], fnum; //一组合法自由变元（多解枚举自由变元可以使用）
	//返回值为 -1 表示无解，为 0 是唯一解，否则返回自由变元个数
	void genx(int msk) {
		rep(i, 0, fnum) x[free[i]] = (msk >> i) & 1;
		per(i, 0, k) {
			rep(j, 0, var) if(a[i][j]) { p = j; break; }	
			x[p] = a[i][var];
			rep(j, p+1, var) x[p] ^= (a[i][j] && x[j]);
		}
	}
	
	int Gauss(int equ, int var){
		fnum = 0;
		for(k = 0, col = 0; k < equ && col < var; k++, col++){
			p = k; rep(i, k, equ) if (a[i][col]) {p = i; break;}
			if (p != k) swap(a[k], a[p]);
			if (!a[k][col]){
				k--; free[fnum++] = col;//这个是自由变元
				continue;
			}
			rep(i, 0, equ) if (i != k && a[i][col]) a[i] ^= a[k];
		}
		rep(i, col, var) free[fnum++] = i;
		rep(i, k, equ) if (a[i][var]) return -1;
		if(k < var) {
			// genx();
			/*
			
			return var - k;//自由变元个数
		} 
		//唯一解，回代
		per(i, 0, var){
			x[i] = a[i][var];
			rep(j, i+1, var) x[i] ^= (a[i][j] && x[j]);
		}
		return 0;
	}
}
