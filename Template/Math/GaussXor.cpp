//对 2 取模的 01 方程组
namespace Gauss{
	static const int N = 2e3 + 10;
	//有 equ 个方程， var 个变元。增广矩阵行数为 equ ,列数为 [0..var]
	bitset<N> a[N]; //增广矩阵 modif
	bool ok[N]; // 标记变元是否确定 
	int x[N]; //解集
	int free[N], free_num; //一组合法自由变元（多解枚举自由变元可以使用）
	//返回值为 -1 表示无解，为 0 是唯一解，否则返回自由变元个数
	int Gauss(int equ, int var){
		int p, col, k; // k 为增广矩阵的秩
		fill_n(ok, var, 0); free_num = 0;
		fill_n(x, var, 0);
		for(k = 0, col = 0; k < equ && col < var; k++, col++){
			p = k; rep(i, k, equ) if (a[i][col]) {p = i; break;}
			if (p != k) swap(a[k], a[p]);
			if (!a[k][col]){
				k--; free[free_num++] = col;//这个是自由变元
				continue;
			}
			rep(i, 0, equ) if (i != k && a[i][col]) a[i] ^= a[k];
		}
		rep(i, col, var) free[free_num++] = i;
		rep(i, k, equ) if (a[i][var]) return -1;
		if(k < var) {
			/*per(i, 0, k) {
				int num = 0;
				rep(j, 0, var) if(a[i][j]) {
					if (!num) p = j; num++;
				}
				if(num > 1) continue;
				ok[p] = 1; x[p] = a[i][var];
			}*/
			return var - k;//自由变元个数
		} 
		//唯一解，回代
		per(i, 0, var){
			bool t = a[i][var];
			rep(j, i+1, var) t ^= (a[i][j] && x[j]);
			x[i] = t;
		}
		return 0;
	}
}
