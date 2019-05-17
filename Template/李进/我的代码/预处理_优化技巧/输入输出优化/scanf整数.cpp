inline bool scan_d(int &num){
    char in;bool IsN=false;  
    in=getchar();  
    if(in==EOF) return false;  
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();  
    if(in=='-'){ IsN=true;num=0;}  
		else num=in-'0';  
    while(in=getchar(),in>='0'&&in<='9') num*=10,num+=in-'0';  
    if(IsN) num=-num; return true;  
}
