#define FI(n) FastIO::read(n)  

namespace FastIO {  
    const int SIZE = 1 << 16;  
    char buf[SIZE], obuf[SIZE], str[60];  
    int bi = SIZE, bn = SIZE, opt;  
    int read(char *s) {  
        while (bn) {  
            for (; bi < bn && buf[bi] <= ' '; bi++);  
            if (bi < bn) break;  
            bn = fread(buf, 1, SIZE, stdin); bi = 0;  
        }  
        int sn = 0;  
        while (bn) {  
            for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];  
            if (bi < bn) break;  
            bn = fread(buf, 1, SIZE, stdin); bi = 0;  
        }  
        s[sn] = 0; return sn;  
    }  
    bool read(int& x) {  
        int n = read(str), bf;  
        if (!n) return 0;  
        int i = 0; if (str[i] == '-') bf = -1, i++; else bf = 1;  
        for (x = 0; i < n; i++) x = x * 10 + str[i] - '0';  
        if (bf < 0) x = -x; return 1;  
    }  
}; 