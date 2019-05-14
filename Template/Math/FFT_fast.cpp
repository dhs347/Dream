const int N = 1 << 21;
const double pi=acos(-1.0);
struct vir{
    double a,b;
    vir(double r=0.0,double i=0.0) {a=r,b=i;}
    vir operator +(const vir &o) const{return vir(a+o.a,b+o.b);}
    vir operator -(const vir &o) const{return vir(a-o.a,b-o.b);}
    vir operator *(const vir &o) const{return vir(a*o.a-b*o.b,b*o.a+a*o.b);}
    vir operator *(const double &o) const{return vir(a*o,b*o);}
    vir operator !() const{return vir(a,-b);}
} x[N|1], y[N|1], z[N|1], w[N|1];

int K;

void fft(vir x[],int k,int v){
    for(int i=0,j=0; i<k; i++){
        if(i>j)swap(x[i],x[j]);
        for(int l=k>>1; (j^=l)<l; l>>=1);
    }
    w[0] = vir(1, 0);
    for(int i=2; i<=k; i<<=1){
        vir g = vir(cos(2*pi/i), (v ? -1 : 1) * sin(2*pi/i));
        for(int j=(i>>1); j>=0; j-=2) w[j] = w[j>>1];
        for(int j=1; j<i>>1; j+=2) w[j] = w[j-1] * g;
        for(int j=0; j<k; j+=i){
            vir *a = x+j, *b = a+(i>>1);
            for(int l=0; l<i>>1; l++){
                vir o = b[l] * w[l];
                b[l] = a[l] - o;
                a[l] = a[l] + o;
            }
        }
    }
    if (v) for(int i=0; i<k; i++) x[i] = vir(x[i].a/k,x[i].b/k);
}

void doit(int *a, int *b, int na, int nb) { 
	for(K = 1; K <= na+nb>>1; K <<= 1);
	rep(i, 0, K) x[i] = y[i] = vir(0, 0);
	for(int i=0; i<=na; i++) (i&1 ? x[i>>1].b : x[i>>1].a) = a[i];
    for(int i=0; i<=nb; i++) (i&1 ? y[i>>1].b : y[i>>1].a) = b[i];
	fft(x, K, 0);
    fft(y, K, 0);
    rep(i, 0, K){
        int j = K-1 & K-i;
        vir tmp = (i&K>>1) ? vir(1, 0) - w[i^K>>1] : w[i] + vir(1, 0); 
        z[i] =(x[i]*y[i]*4 - (x[i] - !x[j])*(y[i] - !y[j])*tmp)*0.25;
    }
    fft(z, K, 1);
    rep(i, 0, na+nb+1) a[i] = i&1 ? z[i>>1].b + 0.1 : z[i>>1].a + 0.1;
}
