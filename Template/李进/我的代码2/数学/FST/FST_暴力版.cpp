//n=(1<<k)-1;

void FST(int *a,int *f){
	mem(f,0);
	for (int i=0;i<=n;i++){
		for (int j=i;;j=(j-1)&i){
			f[i]+=a[j]*a[i^j];
			if (j==0) break;
		}
		f[i]%=_p;
	}
}

//注：快速子集变换
