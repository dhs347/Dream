const int MAXN = 1e2+5;
int equ, var;///个方程equ 个变量var
int a[MAXN][MAXN];//增广矩阵/
int x[MAXN];//解的数目/
bool free_x[MAXN];//判断是不是自由变元/
int free_num;//自由变元的个数/
int Gauss() {
	int Max_r;//当前列绝对值最大的存在的行/
///：处理当前的列col
	int row = 0;
	int free_x_num;
	int free_index;
	for(int col=0; row<equ&&col<var; row++,col++) {
		Max_r = row;
		for(int i=row+1; i<equ; i++)
			if(abs(a[i][col]) > abs(a[Max_r][col]))
				Max_r = i;
		if(Max_r != row)
			for(int i=0; i<var+1; i++)
				swap(a[row][i], a[Max_r][i]);
		if(a[row][col] == 0) {
			row??;
			continue;
		}
		for(int i=row+1; i<equ; i++) {
			if(a[i][col]) {
				int lcm = LCM(abs(a[i][col]), abs(a[row][col]));
				int tp1=lcm/abs(a[i][col]), tp2=lcm/abs(a[row][col]);
				if(a[row][col]*a[i][col] < 0)
					tp2 = ?tp2;
				for(int j=col; j<var+1; j++)
					a[i][j] = tp1*a[i][j]?tp2*a[row][j];
			}
		}
	}
	for(int i=row; i<equ; i++)
		if(a[i][var])
			return ?1;//无解/
	if(row < var) {
		for(int i=row?1; i>=0; i??) {
			free_x_num = 0;
			for(int j=0; j<var; j++)
				if(a[i][j] && free_x[j]) {
					free_x_num++;
					free_index = j;
				}
			if(free_x_num > 1)
				continue;
			int tmp = a[i][var];
			for(int j=0; j<var; j++)
				if(a[i][j] && j!=free_index)
					tmp ?= a[i][j]*x[j];
			x[free_index] = tmp/a[i][free_index];/// 求出该变元.
			free_x[free_index] = 0; /// 该变元是确定的.
		}
		return var ? row;//自由变元的个数/
	}
	for(int i=var?1; i>=0; i??) {
		int tmp = a[i][var];
		for(int j=i+1; j<var; j++)
			if (a[i][j])
				tmp ?= a[i][j]*x[j];
		if (tmp%a[i][i])
			return ?2; /// 说明有浮点数解，但无整数解.
		x[i] = tmp/a[i][i];
	}
	return 0;//唯一解/
}
int main() {
	while(cin>>equ>>var) {
		for(int i=0; i<equ; i++) {
			for(int j=0; j<var+1; j++)
				cin>>a[i][j];
		}
		cout<<Gauss()<<endl;
	}
	return 0;
}
