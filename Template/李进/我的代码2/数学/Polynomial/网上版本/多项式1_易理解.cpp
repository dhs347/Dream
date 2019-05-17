void FFT(Complex *A,int n,int sgn)
{
    for (int i=1;i<n-1;++i)
    {
        int j=0;
        for (int t=1,k=i;t<n;t<<=1,j=((j<<1)|(k&1)),k>>=1);
        if (j>i) swap(A[i],A[j]);
    }
    for (int L=2;L<=n;L<<=1)
    {
        int L1=L>>1;
        for (int i=0;i<L1;++i)
        {
            Complex w=Complex(cos(sgn*PI*i/L1),sin(sgn*PI*i/L1));
            for (int j=i;j<n;j+=L)
            {
                int k=j+L1;
                Complex u=A[j],v=w*A[k];
                A[j]=u+v;A[k]=u-v;
            }
        }
    }
    if (sgn==-1) for (int i=0;i<n;++i) A[i]=A[i]/Complex(n,0.0);
}

void PolyRev(int n,Complex *A,Complex *B)
{
    static Complex tmp[MAXN*4];
    if (n==1) {B[0]=1.0/A[0];return;}
    PolyRev((n+1)>>1,A,B);
    int N=1;while (N<n<<1) N<<=1;
    for (int i=0;i<n;++i) tmp[i]=A[i];
    for (int i=n;i<N;++i) tmp[i]=0;
    FFT(N,tmp,1);FFT(N,B,1);
    for (int i=0;i<N;++i) B[i]=B[i]*(2.0-tmp[i]*B[i]);
    FFT(N,B,-1);
    for (int i=n;i<N;++i) B[i]=0;
}

void PolyDiv(int n,Complex *A,int m,Complex *B,Complex *D,Complex *R)
{
    static Complex A0[MAXN*4],B0[MAXN*4],B1[MAXN*4];
//D
    int N=1;while (N<n<<1) N<<=1;
    for (int i=0;i<N;++i) A0[i]=B0[i]=B1[i]=D[i]=R[i]=0.0;
    for (int i=0;i<n;++i) A0[n-i-1]=A[i];
    for (int i=0;i<m;++i) B0[m-i-1]=B[i];
    PolyRev(n-m+1,B0,B1);
    FFT(N,A0,1);FFT(N,B1,1);
    for (int i=0;i<N;++i) D[i]=A0[i]*B1[i];
    FFT(N,D,-1);
    for (int i=n-m+1;i<N;++i) D[i]=0.0;
    for (int i=0,j=n-m;i<j;++i,--j) swap(D[i],D[j]);
//R
    for (int i=0;i<m;++i) B0[i]=B[i];
    for (int i=0;i<n-m+1;++i) B1[i]=D[i];
    for (int i=n-m+1;i<N;++i) B1[i]=0.0;
    FFT(N,B0,1);FFT(N,B1,1);
    for (int i=0;i<N;++i) R[i]=B0[i]*B1[i];
    FFT(N,R,-1);
    for (int i=0;i<n;++i) R[i]=A[i]-R[i];
}

void PolyLn(int n,Complex *A,Complex *B)
{
    static Complex A0[MAXN*4],A1[MAXN*4];
    int N=1;while (N<n<<1) N<<=1;
    for (int i=0;i<N;++i) A0[i]=0.0,A1[i]=0.0;
    PolyRev(n,A,A0);
    for (int i=0;i<n-2;++i) A1[i]=A[i+1]*double(i+1);A1[n-1]=0.0;
    FFT(N,A0,1);FFT(N,A1,1);
    for (int i=0;i<N;++i) A0[i]*=A1[i];
    FFT(N,A0,-1);
    for (int i=0;i<n-2;++i) B[i+1]=A0[i]/double(i+1);B[0]=0.0;
    for (int i=n;i<N;++i) B[i]=0.0;
}

void PolyExp(int n,Complex *A,Complex *B)
{
    if (n==1) {B[0]=exp(A[0]);return;}
    static Complex A0[MAXN*4],B0[MAXN*4];
    PolyExp((n+1)>>1,A,B);
    int N=1;while (N<n<<1) N<<=1;
    for (int i=0;i<N;++i) B0[i]=0.0;
    PolyLn(n,B,B0);
    for (int i=0;i<n;++i) A0[i]=A[i];for (int i=n;i<N;++i) A0[i]=0.0;
    FFT(N,A0,1);FFT(N,B,1);FFT(N,B0,1);
    for (int i=0;i<N;++i) B[i]=B[i]*(1.0-B0[i]+A0[i]);
    FFT(N,B,-1);
    for (int i=n;i<N;++i) B[i]=0.0;
}

void PolyPow(int n,Complex *A,Complex *B,double k)
{
    static Complex A0[MAXN*4];
    PolyLn(n,A,A0);
    for (int i=0;i<n;++i) A0[i]*=k;
    PolyExp(n,A0,B);
}



