const int N = 1e6 + 7;
int n, M, f[N], g[N], h[N], phi[N], u[N], p[N]; // f[n] 为 n 的最小质因子， g[n]=f[n]^k ， phi[n] 为欧拉函数， u[n] 为莫比乌斯函数， h[n] 为一般积性函数 

void prime(int n) {
	u[1]=phi[1]=1,h[1]=(0); // 1 的时候特判 
	rep(i, 2, n+1) {
		if (!f[i]) {
			p[++M]=i;
			f[i] = g[i] = i;
			phi[i] = i - 1;
			u[i] = -1;
			h[i] = (0);
		}// 质数的时候特判 
		for (int j = 1, k; j <= M && p[j] <= f[i] && i * p[j] <= n; j++){
			f[k = i * p[j]] = p[j];
			if (p[j] < f[i]) {
				g[k] = p[j];
				phi[k] = phi[i] * phi[p[j]];
				u[k] = u[i] * u[p[j]];
				h[k] = h[i] * h[p[j]];			
			}else {
				g[k] = g[i] * p[j];
				phi[k] = phi[i] * p[j];
				u[k] = 0;
				h[k] = h[i / g[i]] * (0);
			} /* 质数次幂特判 */
			//phi[i*p[j]]=phi[i]*(p[j]<f[i]?phi[p[j]]:p[j]);
			//u[i*p[j]]=u[i]*(p[j]<f[i]?u[p[j]]:0);
		}
		/*phi[i*j]=phi[i]*phi[j] (gcd(i,j)=1)
				   phi[i]*j (j|i)
		  u[i*j]=u[i]*u[j] (gcd(i,j)=1)
		         0 (j|i)
		*/
	}
}

