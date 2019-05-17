int inv[N];
void init_inv(int N,int _p){
	inv[1]=1; rep(i,2,N-1) inv[i]=(ll)(_p-_p/i)*inv[_p%i]%_p;
}
