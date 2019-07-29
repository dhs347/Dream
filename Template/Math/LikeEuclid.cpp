ll cal(ll a,ll b,ll c,ll n) { // sum_{i=0...n-1}floor((a*i+b)/c)
  if(n == 0) return 0;
  return (b/c)*n+(a/c)*n*(n-1)/2+(a%c?cal(c,(a*n+b)%c,a%c,(a%c*n+b%c)/c):0);
}
