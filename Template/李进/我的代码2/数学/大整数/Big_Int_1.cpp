struct BigInteger {
    static const int BASE=10000; //高进制
    static const int WIDTH=4; //高进制位数
    vector<int>s;
    BigInteger() {}
    BigInteger(long long num) { // 构造函数
        *this=num;
    }
    //赋值
    BigInteger operator = (long long num) {
        s.clear();
        do {
            s.push_back(num%BASE);
            num/=BASE;
        } while(num>0);
        return *this;
    }
    //+
    BigInteger operator + (BigInteger& b) {
        BigInteger c;
        c.s.resize(max(s.size(),b.s.size())+1);
        for(int i=0; i<c.s.size()-1; i++) {
            int tmp1,tmp2;
            if(i>=s.size())tmp1=0;
            else tmp1=s[i];
            if(i>=b.s.size())tmp2=0;
            else tmp2=b.s[i];
            c.s[i]=tmp1+tmp2;
        }
        for(int i=0; i<c.s.size()-1; i++) {
            c.s[i+1]+=c.s[i]/BASE;
            c.s[i]%=BASE;
        }
        while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
        return c;
    }
    void operator += (BigInteger& b) {
        *this=*this+b;
    }
};
ostream& operator << (ostream& output,const BigInteger& x) {
    output<<x.s.back();
    for(int i=x.s.size()-2; i>=0; i--) {
        char buf[20];
        sprintf(buf,"%04d",x.s[i]);
        for(int j=0; j<strlen(buf); j++)output<<buf[j];
    }
    return output;
}
