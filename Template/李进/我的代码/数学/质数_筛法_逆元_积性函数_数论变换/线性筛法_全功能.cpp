int p[N],prime[N],mu[N],phi[N],div_num[N],nxt[N],e[N],top;
void init_prime(){
	memset(p, 0, sizeof(p));
	top = 0; phi[1] = mu[1] = div_num[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!p[i]) {
			prime[++top] = i;
			mu[i] = -1;
			phi[i] = i-1;
			e[i] = 1;
			div_num[i] = 2;
			nxt[i] = top;
		}
		for (int j = 1; j <= top; ++j) {
			if (i * prime[j] > N) break;
			p[i * prime[j]] = 1;
			nxt[i * prime[j]] = j;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				div_num[i*prime[j]]=div_num[i]/(e[i]+1)*(e[i]+2);
				e[i*prime[j]]=e[i]+1;
				break;
			}
			phi[i * prime[j]] = phi[i] * phi[prime[j]];
			mu[i * prime[j]] = -mu[i];
			div_num[i*prime[j]]=div_num[i]*div_num[prime[j]];
			e[i*prime[j]] = 1;
		}
	}
}
//p[] 为是否为素数
//prime[] 为第几个素数 
//phi[] 为欧拉函数 
//mu[] 为莫比乌斯函数 
//div_num[] 为因子数 
//nxt[] 为最大的质因子的编号 
//e[] 为最大的质因子的幂次

//不需要的直接搜索，删除之
