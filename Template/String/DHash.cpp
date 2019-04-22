inline int upd(int a, int b, int P) {
  if((a += b) >= P) a -= P;
  return a < 0 ? a + P : a;
}
inline int mul(int a, int b, int P) { return 1ll * a * b % P; }
struct DHash {
  static const int P = 1e9 + 7, Q = 1e9 + 9;
  int a, b;
  DHash() { a = b = 0; }
  DHash(int a, int b) : a(a), b(b) {}
  inline DHash operator + (const DHash &c) const { return DHash(upd(a, c.a, P), upd(b, c.b, Q)); }
  inline DHash operator - (const DHash &c) const { return DHash(upd(a, -c.a, P), upd(b, -c.b, Q)); }
  inline DHash operator * (const int c) const { return DHash(mul(a, c, P), mul(b, c, Q)); }
};
