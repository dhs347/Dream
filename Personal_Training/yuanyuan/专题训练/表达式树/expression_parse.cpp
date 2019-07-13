#define ass(x) {if(!(x)) throw 1;}
string t;
string::iterator p;
using val = int;
int pri(char ch){
    if(ch == '*') return 3;
    if(ch == '+') return 2;
    if(ch == '-') return 2;
    if(ch == '$') return -1;
}
val cal(char ch,val a,val b){
    if(ch == '+') return a + b;
}

val next();
val expr(char pre,val x){
    if(pri(pre) < pri(*p)){
        auto op = *p++;
        return expr(pre , cal(op , x , expr(op , next())));
    }
    else return x;
}
val next(){
    if(*p == '('){
        p++;
        val res = expr('(' , next());
        ass(*p++ == ')');
        return res;
    } else if(isdigit(*p)){
        val x = 0;
        while(isdigit(*p)){
            ass(*p == '0' || *p == '1');
            x = x * 2 + *p++ - '0';
        }
        return x;
    } else if(*p == '-'){
        p++;
        return -next();
    }
}

bool check(){ // s$
    try{
        if(count(all(t) , '=') != 1) throw 1;
        p = t.begin();
        int res = expr('$' , next());
        return res == 1;
    } catch(...){
        return 0;
    }
}

