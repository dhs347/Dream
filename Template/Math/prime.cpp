// time : O(n)
// low[] : optional
const int N = 1e6 + 6;
int low[N],cntp,p[N];
bool isp[N];
 
void getprime() {
	fill_n(isp + 2, N - 2, 1);
	rep(i, 2, N) {
		if (isp[i]) p[cntp++]=i;
		for (int j=0;j<cntp&&p[j]*i<N;j++){
			//low[p[j] * i] = p[j];
			isp[p[j] * i] = 0;
			if (i % p[j] == 0) break;
		}
	}
}

// 优化版欧拉筛法 bitset 需要 O2 
const int N = 3e7 + 6;
const int M = 2e6 + 6;
//int low[N],
bitset<N / 3 + 1> isp;
int cntp,p[M];
 
void getprime(int N) {
	cntp = 2;p[0] = 2;p[1] = 3;
	for (int i = 5, k = 1; i <= N; (k & 1) ? i+=2 : i+=4 , k++){
		if (!isp[k]) {
			p[cntp++]=i;
			// low[i] = i;
		}
		for (int j = 2; j < cntp && p[j] * i <= N; j++) {
			//low[p[j] * i] = p[j];
			isp[p[j] * i / 3] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

// 优化埃氏筛法  空间最小 可以不存质数 
const int N = 3e8 + 6;
const int M = 2e7 + 6;
int cntp,p[M];
bitset<N / 3 + 1> bit;

void getprime(int n){
	int i, j;
	cntp = 2; p[0] = 2; p[1] = 3;
	for(i = 5, j = 1; i * i <= n; (j & 1) ? i += 2 : i += 4 , j++) {
		if(bit[j] == 0) {
			p[cntp++]=i;
			for(int j = i * i; j <= n ; j += i) 
				if(j % 2 != 0 && j % 3 != 0) bit[j / 3] = 1;
		}
	}
	for( ; i <= n; (j&1) ? i+=2 : i+=4 , j++) if(bit[j] == 0) p[cntp++]=i;
}

